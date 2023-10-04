#pragma once

#include <QGraphicsView>

class FlightsView : public QGraphicsView
{
	Q_OBJECT

public:
	FlightsView(QWidget* parent = nullptr);

signals:
	void viewRectChanged(QRectF& rect);

public slots:
	void onSliderMoved(int value);
	void onSliderReleased();

public:
	void resizeEvent(QResizeEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};

