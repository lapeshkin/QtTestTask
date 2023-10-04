#include <QRandomGenerator>
#include "FlightsManager.h"
#include "Settings.h"

FlightsManager::FlightsManager(QObject* parent)
	: QObject(parent)
{
	smallMapScene = nullptr;
	mainScene	  = nullptr;
	init(nullptr, nullptr, 0);
}

FlightsManager::FlightsManager(QGraphicsScene* pMainScene, QGraphicsScene* pSmallMapScene, int numFlights, QObject* parent)
	: QObject(parent)
{
	smallMapScene = nullptr;
	mainScene	  = nullptr;
	init(pMainScene, pSmallMapScene, numFlights);
}

FlightsManager::~FlightsManager()
{
	clear();
}

// delete all of the flights
void FlightsManager::clear()
{
	for (Flight* pFlight : flights)
	{
		if (pFlight)
		{
			if (Settings::get().showDebugInfo)
			{
				qDebug() << "Deleting: " << pFlight;
			}
			delete pFlight;
		}
	}

	flights.clear();
}

void FlightsManager::init(QGraphicsScene* pMainScene, QGraphicsScene* pSmallMapScene, int numFlights)
{
	clear();

	mainScene	  = pMainScene;
	smallMapScene = pSmallMapScene;

	for (int n = 0; n < numFlights; n++)
	{
		Flight* pFlight = new Flight(this, n + 1, "");

		setRandomFlightParams(pFlight);

		// create graphics items for main scene and small map
		QGraphicsPixmapItem* pMainSceneItem = mainScene->addPixmap(pFlight->getPlaneImage());
		QGraphicsEllipseItem* pSmallMapItem = smallMapScene->addEllipse(pFlight->getSmallMapRect(), QPen(pFlight->getPlaneColor()), QBrush(pFlight->getPlaneColor()));
		// set graphics items for current flight so that it can redraw them
		pFlight->setGraphicsItems(pMainSceneItem, pSmallMapItem);
		// add a flight to map with item in main scene as a key
		flights.insert(pMainSceneItem, pFlight);
	}
}

void FlightsManager::setSmallMapScene(QGraphicsScene* pScene)
{
	smallMapScene = pScene;
}

void FlightsManager::setVisibleArea(const QRectF& rect)
{
	visibleArea = rect;
}

// start the timer if it's is not started yet
void FlightsManager::run()
{
	// in case of restarting graphic scene no need to run timer one more time
	if (timer.isActive()) return;

	connect(&timer, SIGNAL(timeout()), this, SLOT(timerTick()));
	timer.start(50);
}

// stop the timer if it's is active
void FlightsManager::stop()
{
	if (!timer.isActive()) return;

	disconnect(&timer, SIGNAL(timeout()), this, SLOT(timerTick()));
	timer.stop();
}

// set random flight parameters for the new flight
void FlightsManager::setRandomFlightParams(Flight* pFlight)
{
	QRandomGenerator* rg = QRandomGenerator::global();

	// set random flight parameters
	int x    = rg->bounded(1, Settings::get().modelWidth);
	int y    = rg->bounded(1, Settings::get().modelHeight);
	int vel  = rg->bounded(1, 4);
	int dir  = rg->bounded(0, 360);
	pFlight->setFlightParams(x, y, vel, dir);

	// set random color for the plane
	int colR = rg->bounded(0, 200);
	int colG = rg->bounded(0, 200);
	int colB = rg->bounded(0, 200);
	pFlight->setPlaneColor(QColor(colR, colG, colB));

	// set random name of the flight
	QString cities[11] = { "Paris", "New York", "London", "Warsaw", "Berlin", "Tokio", "Gdansk", "Milan", "Rome", "Oslo", "Madrid" };
	int depart = rg->bounded(0, 10);
	int dest   = rg->bounded(0, 10);
	// if the departure and destination cities are the same, then change the destination city
	if (depart == dest) dest++;

	QString flightName = QString("Flight: %1 - %2").arg(cities[depart]).arg(cities[dest]);
	pFlight->setName(flightName);

	if (Settings::get().showDebugInfo)
	{
		qDebug() << pFlight;
	}
}

void FlightsManager::timerTick()
{
	calcCoordinates();
	findVisible();
}

// calculate new coordinates for every flight
void FlightsManager::calcCoordinates()
{
	for (Flight* flight : flights)
	{
		flight->calcCoordinates();
	}
}

// find visible flights list and if it changed emit visibleListChanged signal to main window
void FlightsManager::findVisible()
{
	QList<QGraphicsItem*> visibleItems = mainScene->items(visibleArea);
	QMap<QGraphicsItem*, Flight*>	visibleNow;
	for (QGraphicsItem* item : visibleItems)
	{
		if (flights.find(item) != flights.end())
			visibleNow.insert(item, flights[item]);
	}

	if (visibleNow != visibleFlights)
	{
		visibleFlights = visibleNow;
		emit visibleListChanged(visibleFlights);
	}
}


