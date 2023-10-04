#pragma once

#include <QDebugStateSaver>
#include <QGraphicsPixmapItem>

class FlightsManager;

class Flight : public QObject
{
	Q_OBJECT

public:
	Flight(QObject* parent = nullptr);
	Flight(FlightsManager* pManager, int flightID, QString flightName);
	~Flight();

	// set initial coordinates, velocity and direction values
	void	setFlightParams(qreal x, qreal y, int vel, int dir);
	// set name of the flight
	void	setName(const QString& flightName);
	// set the color of the plane
	void	setPlaneColor(const QColor& color);

	// calculates new coordinates depending on the speed and direction of flight
	void	calcCoordinates();

	int		getID() const { return id; }
	QString	getName() const { return name; }
	qreal	getX() const { return coord_x; }
	qreal	getY() const { return coord_y; }
	int		getVelocity() const { return velocity; }
	int		getWidth() const { return planeImage.width(); }
	int		getHeight() const { return planeImage.height(); }
	QColor	getPlaneColor() const { return planeColor;  }
	QPixmap& getPlaneImage() { return planeImage; }
	QRectF	getRect() const;
	QRectF	getSmallMapRect() const;
	void	setGraphicsItems(QGraphicsPixmapItem* pItem, QGraphicsEllipseItem* pSmallMapItem);

	QString toString() const;

private:
	// initialization with default values
	void	init();

	// rotate the plane image according to the direction
	void	rotatePlane();

private:
	int		id;
	QString	name;
	qreal	coord_x;
	qreal	coord_y;
	int		velocity;
	int		direction;

	FlightsManager* manager;

	// pointer to PixmapItem in main QGraphicsScene object
	QGraphicsPixmapItem*  mainSceneItem;
	// pointer to EllipseItem in small map QGraphicsScene object
	QGraphicsEllipseItem* smallMapItem;

	// plane image loaded from resource
	QPixmap	planeImage;

	// color of a plane
	QColor	planeColor;
};

//Q_DECLARE_METATYPE(Flight)

QDebug operator<<(QDebug debug, const Flight& flight);
QDebug operator<<(QDebug debug, const Flight* flight);