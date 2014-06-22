/*
				 ___  __  __ ______  ____  ___
				/ _ \|  \/  |  ____|/ ___|/ _ \
	 		   | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro Vázquez

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef QOMGLEAF_H
#define QOMGLEAF_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QString>
#include <QIcon>
#include <QMouseEvent>
#include <QPoint>
#include "Omega.h"

class QOmgLeaf : public QTreeWidgetItem
{
public:
    //? Default Constructor
    QOmgLeaf(QTreeWidget* ap_parent, Omega::LeafType a_type, QString a_name, QIcon a_icon);
    QOmgLeaf(QTreeWidgetItem* ap_parent, Omega::LeafType a_type, QString a_name, QIcon a_icon);
    void ShowPopUp( QPoint point );

    Omega::LeafType GetLeafType();

    QString GetLeafName();

private:

    //? The type of leaf
    Omega::LeafType _type;

    //? The name of leaf
    QString entity_name;

    //? The icon of the leaf
    QIcon icon;

    QPoint dragStartPosition;

};

#endif // QOMGLEAF_H
