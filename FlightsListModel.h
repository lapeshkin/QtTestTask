#pragma once
#include <QAbstractListModel>
#include <QStandardItemModel>
#include "Flight.h"

class FlightsListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FlightsListModel(QObject* parent = nullptr);
    QVariant data(const QModelIndex& index, int nRole) const;
    int     rowCount(const QModelIndex& parent = QModelIndex()) const;
    bool    setData(const QModelIndex& index, const QVariant& value, int nRole);
    // clears the list and sets new items from the list, triggering only one signal to redraw the list.
    void    setDataFromList(const QList<Flight*>& list);
    // delete all elements and set a signal to redraw list
    void    clear();
    // returns a string in HTML format with flight information 
    QString getInfoString(Flight* flight) const;

private:
    QList<Flight*>   flightsList;
};

