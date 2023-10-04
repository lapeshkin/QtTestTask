#include <QApplication>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include "FlightInfoDelegate.h"


void FlightInfoDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem tempOption = option;
    initStyleOption(&tempOption, index);

    QStyle* style = tempOption.widget ? tempOption.widget->style() : QApplication::style();

    QTextDocument doc;
    doc.setHtml(tempOption.text);

    /// Painting item without text
    tempOption.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &tempOption, painter);

    QAbstractTextDocumentLayout::PaintContext ctx;

    // Highlighting text if item is selected
    if (tempOption.state & QStyle::State_Selected)
        ctx.palette.setColor(QPalette::Text, tempOption.palette.color(QPalette::Active, QPalette::HighlightedText));

    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &tempOption);
    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize FlightInfoDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem tempOption = option;
    initStyleOption(&tempOption, index);

    tempOption.backgroundBrush.setColor(Qt::yellow);

    QTextDocument doc;
    doc.setHtml(tempOption.text);
    doc.setTextWidth(tempOption.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}
