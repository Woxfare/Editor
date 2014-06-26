#include "QOmgTree.h"
#include "QOmgLeaf.h"

QOmgTree::QOmgTree(QWidget* ap_parent) : QTreeWidget( ap_parent )
{
}

void
QOmgTree::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::RightButton )
    {
        QOmgLeaf* leaf = (QOmgLeaf*)itemAt(event->pos());

        if(leaf)
            leaf->ShowPopUp(QCursor::pos());
    }

    QTreeWidget::mousePressEvent(event);
}
