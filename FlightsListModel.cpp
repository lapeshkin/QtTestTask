#include "FlightsListModel.h"

FlightsListModel::FlightsListModel(QObject* parent)
    : QAbstractListModel(parent) 
{
}

QVariant FlightsListModel::data(const QModelIndex& index, int nRole) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
        ? getInfoString(flightsList.at(index.row()))
        : QVariant();
}

int FlightsListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return flightsList.size();
}

bool FlightsListModel::setData(const QModelIndex& index, const QVariant& value, int nRole)
{
    if (index.isValid())
    {

        flightsList.replace(index.row(), value.value<Flight*>());
        emit dataChanged(index, index);
        return true;
    }
    return false;

}

void FlightsListModel::clear()
{
    flightsList.clear();

    QModelIndex emptyIndex = index(1, 0);
    emit dataChanged(emptyIndex, emptyIndex);

}

// clears the list and sets new items from the list, triggering only one signal to redraw the list.
void FlightsListModel::setDataFromList(const QList<Flight*>& list)
{
    clear();

    flightsList = list;

    emit dataChanged(index(0, 0), index(flightsList.size()-1, 0));
}

// returns a string in HTML format with flight information 
QString FlightsListModel::getInfoString(Flight* flight) const
{
    QColor c = flight->getPlaneColor();
    QString res = QString("<style>.col{color:rgb(%1,%2,%3);margin:2px;}.red{color:red;}</style><H2 class='col'>%4</H2><H3 class='col'>ID: <span class='red'>%5</span></H3>").arg(c.red()).arg(c.green()).arg(c.blue()).arg(flight->getName()).arg(flight->getID());
    return res;
}



