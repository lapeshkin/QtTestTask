#include <QResizeEvent>
#include <QAbstractSlider>
#include "Settings.h"
#include "FlightsView.h"

FlightsView::FlightsView(QWidget* parent) 
	: QGraphicsView(parent) 
{
	//setMouseTracking(true);
	connect((QAbstractSlider*)horizontalScrollBar(), &QAbstractSlider::sliderMoved, this, &FlightsView::onSliderMoved);
	connect((QAbstractSlider*)verticalScrollBar(), &QAbstractSlider::sliderMoved, this, &FlightsView::onSliderMoved);
	connect((QAbstractSlider*)horizontalScrollBar(), &QAbstractSlider::sliderReleased, this, &FlightsView::onSliderReleased);
	connect((QAbstractSlider*)verticalScrollBar(), &QAbstractSlider::sliderReleased, this, &FlightsView::onSliderReleased);
}

void FlightsView::resizeEvent(QResizeEvent* event)
{
	QSize oldSize = event->oldSize();
	QSize newSize = event->size();

	if (Settings::get().showDebugInfo)
	{
		QString str;
		str.sprintf("OldSize(%d, %d), NewSize(%d, %d)", oldSize.width(), oldSize.height(), newSize.width(), newSize.height());
		qDebug(qUtf8Printable(str));
	}

	// ignore this event if it occurs for the first time on window created
	if (oldSize.width() == -1 && oldSize.height() == -1) return;

	QRectF rect = mapToScene(QRect(0, 0, newSize.width() - 1, newSize.height() - 1)).boundingRect();
	emit viewRectChanged(rect);
}

void FlightsView::mouseMoveEvent(QMouseEvent* event)
{
	return;

	if (Settings::get().showDebugInfo)
	{
		int x = event->x();
		int y = event->y();

		QPointF scenePos = mapToScene(event->pos());
		qreal x2 = scenePos.x();
		qreal y2 = scenePos.y();

		QRect geomRect = viewport()->geometry();
		QRectF rect = mapToScene(geomRect).boundingRect();

		QString str;
		str.sprintf("Mouse (%i:%i), Scene (%f:%f), GeomRect(%i, %i, %i, %i), SceneRect(%f, %f, %f, %f)", x, y, x2, y2, geomRect.x(), geomRect.y(), geomRect.width(), geomRect.height(), rect.x(), rect.y(), rect.width(), rect.height());

		qDebug(qUtf8Printable(str));
	}
}

void FlightsView::onSliderMoved(int value)
{
	//QRect geomRect = viewport()->geometry();
	//QRectF rect = mapToScene(geomRect).boundingRect();

	//QString str;
	//str.sprintf("GeomRect(%i, %i, %i, %i), SceneRect(%f, %f, %f, %f)", geomRect.x(), geomRect.y(), geomRect.width(), geomRect.height(), rect.x(), rect.y(), rect.width(), rect.height());
	//qDebug(qUtf8Printable(str));

	//emit viewRectChanged(rect);

	QRectF rect = mapToScene(viewport()->geometry()).boundingRect();
	emit viewRectChanged(rect);
}

void FlightsView::onSliderReleased()
{
	//QRect geomRect = viewport()->geometry();
	//QRectF rect = mapToScene(geomRect).boundingRect();

	//QString str;
	//str.sprintf("GeomRect(%i, %i, %i, %i), SceneRect(%f, %f, %f, %f)", geomRect.x(), geomRect.y(), geomRect.width(), geomRect.height(), rect.x(), rect.y(), rect.width(), rect.height());
	//qDebug(qUtf8Printable(str));

	//emit viewRectChanged(rect);

	QRectF rect = mapToScene(viewport()->geometry()).boundingRect();
	emit viewRectChanged(rect);
}

