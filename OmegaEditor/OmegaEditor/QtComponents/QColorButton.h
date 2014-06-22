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

#ifndef QCOLORBUTTON_H
#define QCOLORBUTTON_H

#include <QWidget>

class QColor;

namespace Ui {
class QColorButton;
}

class QColorButton : public QWidget
{
    Q_OBJECT

public:

    /*!
     * \brief Edition mode to know where what to paint
     */
    typedef enum{ SCENARY, CHARACTER, CUBE } editionMode;

    /*!
     * \brief QColorButton
     * \param parent
     */
    explicit QColorButton(QWidget *parent = 0);
    ~QColorButton();

    /*!
     * \brief Gets the current color in the widget
     * \return
     */
    QColor getSelectedColor( void );

    /*!
     * \brief Change the current color of the widget
     * \param aColor
     */
    void changeColor( QColor aColor );

    /*!
     * \brief Sets the edition mode of the widget in order to paint the scene, the cube, the character,...
     * \param mode
     */
    void setEditionMode( editionMode mode);

private slots:

    /*!
     * \brief on_colorButton_clicked
     */
    void on_colorButton_clicked();

    /*!
     * \brief on_colorChanged
     * \param aColor
     */
    void on_colorChanged(QColor aColor);

private:

    /*!
     * \brief ui
     */
    Ui::QColorButton *ui;

    /*!
     * \brief _color
     */
    QColor _color;

    /*!
     * \brief edMode
     */
    editionMode edMode;
};

#endif // QCOLORBUTTON_H
