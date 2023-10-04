#pragma once

#include <QStyledItemDelegate>

class FlightInfoDelegate : public QStyledItemDelegate
{
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

