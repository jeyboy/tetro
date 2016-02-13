#ifndef TEXT_ITEM
#define TEXT_ITEM

#include "qgraphicsitem.h"
#include <qstringbuilder.h>

class TextItem : public QGraphicsSimpleTextItem {
    QString base_text;
public:
    TextItem(const QString & base_text, const QString & text, QGraphicsItem * parent = 0) : QGraphicsSimpleTextItem(parent), base_text(base_text) {
        setText(text);
    }

    void setText(const QString & text) {
        QGraphicsSimpleTextItem::setText(base_text % text);
    }
};

#endif // TEXT_ITEM
