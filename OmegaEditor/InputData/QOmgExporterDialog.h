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

#ifndef QOMGEXPORTERDIALOG_H
#define QOMGEXPORTERDIALOG_H

#include <QDialog>
#include "Omega.h"
#include <set>

class QOmgListWidgetItem;

namespace Ui {
class QOmgExporterDialog;
}

class QOmgExporterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QOmgExporterDialog(QWidget *parent = 0);
    ~QOmgExporterDialog();

private:
    Ui::QOmgExporterDialog *ui;
    std::set<Omega::EntityType> set_entities;

    bool validate( void );

    void fillListOfEntities( void );

    void configureButtons( void );

    void updateListOfEntities( void );

    QList<QOmgListWidgetItem*> getSelectedEntities( void );

    void exportEntities( void );

    void saveEntitiesInFile( Omega::EntityVector avEntities );

signals:
    void HideInputData();
private slots:
    void on_pbExport_clicked();
    void on_pbCancel_clicked();
    void on_pb_clicked();
};

#endif // QOMGEXPORTERDIALOG_H
