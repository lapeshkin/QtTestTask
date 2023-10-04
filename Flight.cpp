#include <QTextStream>
#include <QDebugStateSaver>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QRandomGenerator>
#include "FlightsManager.h"
#include "Flight.h"
#include "Settings.h"

Flight::Flight(QObject* parent) 
	: QObject(parent)
{
	init();
}

Flight::Flight(FlightsManager* pManager, int flightID, QString flightName)
{
	init();

	manager = pManager;
	id   = flightID;
	name = flightName;
}

Flight::~Flight()
{

}

// initialization with default values
void Flight::init()
{
	id   = 0;
	name = "";
	mainSceneItem = nullptr;
	manager = nullptr;

	planeImage.load(Settings::get().planeImageRes);
	setFlightParams(0, 0, 0, 0);

}

// set initial coordinates, velocity and direction values
void Flight::setFlightParams(qreal x, qreal y, int vel, int dir)
{
	coord_x		= x;
	coord_y		= y;
	velocity	= vel;
	direction	= dir;
}

void Flight::setName(const QString& flightName)
{
	name = flightName;
}

// set the color of the plane
void Flight::setPlaneColor(const QColor& color)
{
	planeColor = color;

	// Convert the pixmap to QImage
	QImage tmp = planeImage.toImage();
	QColor tempColor = planeColor;

	// Loop all the pixels
	for (int y = 0; y < tmp.height(); y++)
	{
		for (int x = 0; x < tmp.width(); x++)
		{
			// Read the alpha value each pixel, keeping the RGB values of your color
			tempColor.setAlpha(tmp.pixelColor(x, y).alpha());

			// Apply the pixel color
			tmp.setPixelColor(x, y, tempColor);
		}
	}

	// Get the coloured pixmap
	planeImage = QPixmap::fromImage(tmp);

}


QRectF Flight::getRect() const
{
	return QRectF(coord_x - (getWidth() / 2), coord_y - getHeight() / 2, getWidth(), getHeight());
}

QRectF Flight::getSmallMapRect() const
{
	qreal sizeX = Settings::get().modelWidth * Settings::get().smallMapPlaneSize / Settings::get().sidePaneWidth;
	qreal sizeY = Settings::get().modelHeight * Settings::get().smallMapPlaneSize / Settings::get().sidePaneWidth;
	return QRectF(coord_x + (getWidth()/2) - (sizeX/2), coord_y + (getHeight()/2) - (sizeY/2), sizeX, sizeY);
}

// calculates new coordinates depending on the speed and direction of flight
void Flight::calcCoordinates()
{
	coord_x -= velocity * qSin(qDegreesToRadians((float)direction));
	coord_y += velocity * qCos(qDegreesToRadians((float)direction));

	bool changeDirection = false;

	if (coord_x > Settings::get().modelWidth - getWidth())
	{
		coord_x = Settings::get().modelWidth - getWidth() - 1;
		changeDirection = true;
	}
	if (coord_x < 0)
	{
		coord_x = 1;
		changeDirection = true;
	}
	if (coord_y > Settings::get().modelHeight - getHeight())
	{
		coord_y = Settings::get().modelHeight - getHeight() - 1;
		changeDirection = true;
	}
	if (coord_y < 0)
	{
		coord_y = 1;
		changeDirection = true;
	}

	if (changeDirection)
	{
		direction += QRandomGenerator::global()->bounded(45, 90);
		if (direction > 360) direction -= 360;

		// rotate the plane image because the direction has changed
		rotatePlane();
	}

	//pGraphicsItem->setRect(getRect());
	mainSceneItem->setOffset(coord_x, coord_y);
	smallMapItem->setRect(getSmallMapRect());
}

void Flight::setGraphicsItems(QGraphicsPixmapItem* pItem, QGraphicsEllipseItem* pSmallMapItem)
{
	mainSceneItem = pItem;
	smallMapItem  = pSmallMapItem;

	// set initial plane direction
	rotatePlane();
}

void Flight::rotatePlane()
{
	if (!mainSceneItem) return;

	QMatrix rm;
	rm.rotate(direction);
	mainSceneItem->setPixmap(planeImage.transformed(rm));
}


// implementation qDebug output of class Flight
QString Flight::toString() const
{
	QString s;
	QTextStream out(&s);

	out << "Flight(id: " << id << ", name: " << name 
		<< ", (" << coord_x << ", " << coord_y << "), " 
		<< "vel: " << velocity << ", direction : " << direction;
	return s;
}

QDebug operator<<(QDebug debug, const Flight& flight)
{
	QDebugStateSaver saver(debug);
	debug.nospace() << flight.toString();
	return debug;
}

QDebug operator<<(QDebug debug, const Flight* flight)
{
	QDebugStateSaver saver(debug);
	debug.nospace() << *flight;
	return debug;
}