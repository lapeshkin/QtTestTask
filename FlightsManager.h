#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "Flight.h"

class FlightsManager : public QObject
{
	Q_OBJECT

public:
	FlightsManager(QObject* parent = nullptr);
	FlightsManager(QGraphicsScene* pMainScene, QGraphicsScene* pSmallMapScene, int numFlights, QObject* parent = nullptr);
	~FlightsManager();

	void init(QGraphicsScene* pMainScene, QGraphicsScene* pSmallMapScene, int numFlights);

	// start the timer if it's is not started yet
	void run();
	// stop the timer if it's is active
	void stop();
	// delete all of the flights
	void clear();

	void setSmallMapScene(QGraphicsScene* pScene);
	void setVisibleArea(const QRectF& rect);

signals:
	void visibleListChanged(QMap<QGraphicsItem*, Flight*> newList);

private slots:
	// a slot where messages from the timer are received
	void timerTick();

private:
	// set random flight parameters for the new flight
	void setRandomFlightParams(Flight* pFlight);
	// calculate new coordinates for every flight
	void calcCoordinates();
	// find visible flights list and if it changed emit visibleListChanged signal to main window
	void findVisible();

private:
	// map of flights with graphics items in main scene as a keys
	QMap<QGraphicsItem*, Flight*>	flights;
	// map of flights within visible area
	QMap<QGraphicsItem*, Flight*>	visibleFlights;
	// main scene and small map scene
	QGraphicsScene*		mainScene;
	QGraphicsScene*		smallMapScene;
	// timer
	QTimer				timer;
	// visible area rect
	QRectF				visibleArea;

};

