#include <QListView>
#include <QSettings>
#include <QMessageBox>
#include "QtTestTask.h"
#include "FlightsListModel.h"
#include "SettingsDialog.h"
#include "Settings.h"

QtTestTask::QtTestTask(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    mainScene       = nullptr;
    smallMapScene   = nullptr;

    restoreSettings();

    initInterface();

    mainScene = new QGraphicsScene(this);
    smallMapScene = new QGraphicsScene(this);

    init();

    // pressed ok in settings dialog
    QObject::connect(&settingsDialog, &SettingsDialog::settingsChanged, this, &QtTestTask::onSettingsChanged);
    // flight manager detects changes in visible flights list
    QObject::connect(&flightsManager, &FlightsManager::visibleListChanged, this, &QtTestTask::updateVisibleList);
    // visible area of main view has changed
    QObject::connect(&mainView, &FlightsView::viewRectChanged, this, &QtTestTask::changeVisibleArea);

}

QtTestTask::~QtTestTask()
{
}

void QtTestTask::initInterface()
{
    ui.viewAreaLayout->addWidget(&mainView);

    ui.verticalLayout->addWidget(&smallMapView);
    smallMapView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    smallMapView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    smallMapView.sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    smallMapView.sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
    smallMapView.setMinimumSize(Settings::get().sidePaneWidth, Settings::get().sidePaneWidth);
    smallMapView.setMaximumSize(Settings::get().sidePaneWidth, Settings::get().sidePaneWidth);

    listView.setModel(&model);
    listView.sizePolicy().setHorizontalPolicy(QSizePolicy::Fixed);
    listView.setMinimumSize(Settings::get().sidePaneWidth, 0);
    listView.setMaximumSize(Settings::get().sidePaneWidth, QWIDGETSIZE_MAX);
    ui.verticalLayout->addWidget(&listView);
    listView.setItemDelegate(&flightInfoDelegate);
}

// sets initial scene size, creates flights, initialize small map view and scene
void QtTestTask::init()
{
    mainScene->setSceneRect(QRectF(0, 0, Settings::get().modelWidth, Settings::get().modelHeight));
    mainScene->addRect(QRectF(0, 0, Settings::get().modelWidth, Settings::get().modelHeight));
    mainView.setScene(mainScene);

    flightsManager.init(mainScene, smallMapScene, Settings::get().numFlights);

    smallMapView.setScene(smallMapScene);
    smallMapScene->addRect(QRectF(0, 0, Settings::get().modelWidth, Settings::get().modelHeight));
    visibleAreaBorder = smallMapScene->addRect(QRectF(0, 0, Settings::get().modelWidth, Settings::get().modelHeight), QPen(QBrush(Qt::red), 2));
}

void QtTestTask::start()
{
    // set correct visible area rect after showing main window
    mainView.onSliderReleased();

    // after main window became visible set fitInView
    smallMapView.fitInView(QRectF(1, 1, Settings::get().modelWidth - 1, Settings::get().modelHeight - 1), Qt::KeepAspectRatio);

    // start the timer
    flightsManager.run();
}

// clean mainScene and smallMapScene and delete all items
void QtTestTask::clear()
{
    QList<QGraphicsItem*> allItems = mainScene->items();
    for (QGraphicsItem* item : allItems)
        mainScene->removeItem(item);

    delete mainScene;
    mainScene = nullptr;

    allItems = smallMapScene->items();
    for (QGraphicsItem* item : allItems)
        smallMapScene->removeItem(item);

    delete smallMapScene;
    smallMapScene = nullptr;
}


void QtTestTask::updateVisibleList(QMap<QGraphicsItem*, Flight*> newList)
{
    QList<Flight*> list;
    for (Flight* item : newList)
        list.append(item);

    model.setDataFromList(list);
}

void QtTestTask::openSettingsDialog()
{
    settingsDialog.show();
}

// settings have changed in settings dialog
// restarting the process
void QtTestTask::onSettingsChanged()
{
    // stop the timer in flightsManager
    flightsManager.stop();

    // clean the model of the side list
    model.clear();

    // delete all the flights
    flightsManager.clear();

    // clean mainScene and smallMapScene an delete all items
    clear();

    // craete new scenes
    mainScene = new QGraphicsScene(this);
    smallMapScene = new QGraphicsScene(this);

    // create new flights
    init();

    //QMessageBox msgBox;
    //msgBox.critical(nullptr, "Debug", "Still alive (init)");

    // start the timer
    start();
}

void QtTestTask::changeVisibleArea(QRectF& rect)
{
    flightsManager.setVisibleArea(rect);

    // redraw visible area border in small map
    visibleAreaBorder->setRect(rect);

    //QString str;
    //str.sprintf("visibleArea(%f, %f, %f, %f)", rect.x(), rect.y(), rect.width(), rect.height());
    //qDebug(qUtf8Printable(str));
}


void QtTestTask::closeEvent(QCloseEvent* event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void QtTestTask::saveSettings()
{
    //QSettings settings("QtTestTask", "QtTestTask");
    //settings.setValue("NumFlights", Settings::get().numFlights);
    //settings.setValue("ModelWidth", Settings::get().modelWidth);
    //settings.setValue("ModelHeight", Settings::get().modelHeight);
    //settings.setValue("geometry", saveGeometry());
    //settings.setValue("windowState", saveState());
}

void QtTestTask::restoreSettings()
{
    QSettings settings("QtTestTask", "QtTestTask");
    Settings::get().numFlights = settings.value("NumFlights", Settings::get().numFlights).toInt();
    Settings::get().modelWidth = settings.value("ModelWidth", Settings::get().modelWidth).toInt();
    Settings::get().modelHeight = settings.value("ModelHeight", Settings::get().modelHeight).toInt();
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

