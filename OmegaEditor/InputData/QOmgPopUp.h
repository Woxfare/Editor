/*
				 ___  __  __ ______  ____  ___
				/ _ \|  \/  |  ____|/ ___|/ _ \
	 		   | | | |      | |__  | |   | | | |
               | | | | |\/| |  __| | |  _| |_| |
               | |_| | |  | | |____| |_| |  _  |
                \___/|_|  |_|______|\____|_| |_|

	Copyright (c) 2014 Fernando Perera & Alejandro V�zquez

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

#ifndef QOMGPOPUP_H
#define QOMGPOPUP_H

#include <QWidget>
#include "Omega.h"
#include <QPoint>
#include <QAction>

namespace Ui {
class QOmgPopUp;
}

class QOmgPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit QOmgPopUp(QWidget *parent = 0);
    ~QOmgPopUp();

    void ShowPopUp(bool a_exist, Omega::LeafType a_type, QString a_name, QPoint a_pos);

private slots:
    void on_New_clicked();

    void on_Edit_clicked();

    void on_Delete_clicked();

    void DeleteFolder( QString a_name );

private:
    Ui::QOmgPopUp *ui;

    Omega::LeafType _type;
    QString _name;

    QAction *actionNew;
    QAction *actionEdit;
    QAction *actionDelete;
};

#endif // QOMGPOPUP_H
