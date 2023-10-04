#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListView>
#include "FlightsManager.h"
#include "FlightsListModel.h"
#include "FlightsView.h"
#include "SmallMapView.h"
#include "FlightInfoDelegate.h"
#include "SettingsDialog.h"
#include "ui_QtTestTask.h"

class QtTestTask : public QMainWindow
{
    Q_OBJECT

public:
    QtTestTask(QWidget *parent = nullptr);
    ~QtTestTask();

    // set initial scene size, create flights, initialize small map view and scene
    void init();
    // after the main window has appeared, start the timer
    void start();
    // clean mainScene and smallMapScene and delete all items
    void clear();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initInterface();
    void saveSettings();
    void restoreSettings();

public slots:
    // visible flights list has changed, update side list
    void    updateVisibleList(QMap<QGraphicsItem*, Flight*> newList);
    void    openSettingsDialog();
    void    onSettingsChanged();
    void    changeVisibleArea(QRectF& rect);


private:
    Ui::QtTestTaskClass ui;

    FlightsManager      flightsManager;

    // main scene members
    QGraphicsScene*     mainScene;
    FlightsView         mainView;

    // small map memmbers
    QGraphicsScene*     smallMapScene;
    SmallMapView        smallMapView;
    QGraphicsRectItem*  visibleAreaBorder;

    // side list view members
    QListView           listView;
    FlightsListModel    model;
    FlightInfoDelegate  flightInfoDelegate;

    SettingsDialog      settingsDialog;
};
