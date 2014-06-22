#include "QOmgStyle.h"

QString
QOmgStyle::CurrentStyleSheet( )
{
    QString style =

    "QDialog{"
        "background-color: #F0F0F0;"
    "}"

    "QLabel{"
        "color:black;"
    "}"

    "QComboBox {"
         "border: 1px solid black;"
         "border-radius: 3px;"
         "padding: 1px 18px 1px 3px;"
         "min-width: 6em;"
     "}"

     "QComboBox:editable {"
         "background: #C8C8C8;"
     "}"

     "QComboBox:!editable, QComboBox::drop-down:editable {"
          "background: #C8C8C8;"
     "}"

     "/* QComboBox gets the state when the popup is open */"
     "QComboBox:!editable:on, QComboBox::drop-down:editable:on {"
         "background: #F0F0F0;"
     "}"

    "QComboBox::down-arrow {"
        "image: url( :/Media/down_arrow.png)"
    "}"

     "QComboBox:on { /* shift the text when the popup opens */"
         "padding-top: 3px;"
         "padding-left: 4px;"
     "}"

     "QComboBox::drop-down {"
         "subcontrol-origin: padding;"
         "subcontrol-position: top right;"
         "width: 15px;"

         "border-left-width: 1px;"
         "border-left-color: darkgray;"
         "border-left-style: solid; /* just a single line */"
         "border-top-right-radius: 3px; /* same radius as the QComboBox */"
         "border-bottom-right-radius: 3px;"
      "}"

     "QComboBox::down-arrow:on { /* shift the arrow when popup is open */"
            "top: 1px;"
         "left: 1px;"
            "}"

     "QPushButton  {"
        "border-bottom-width: 1px;"
        "border-bottom-color: black;"
        "border-bottom-style: solid;"

        "border-left-width: 1px;"
        "border-left-color: darkgray;"
        "border-left-style: solid;"


        "border-top-width: 1px;"
        "border-top-color: darkgray;"
        "border-top-style: solid;"

        "border-right-width: 1px;"
        "border-right-color: black;"
        "border-right-style: solid;"

        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #C0C0C0  , stop: 1 #E0E0E0 );"
    "}"

    "QPushButton:pressed  {"
        "border-bottom-width: 1px;"
        "border-bottom-color: darkgray;"
        "border-bottom-style: solid;"

        "border-left-width: 1px;"
        "border-left-color: black;"
        "border-left-style: solid;"


        "border-top-width: 1px;"
        "border-top-color: black;"
        "border-top-style: solid;"

        "border-right-width: 1px;"
        "border-right-color: darkgray;"
        "border-right-style: solid;"

        "background-color: #E8E8E8 "
     "}"

     "QLineEdit  {"
         "border: 1px solid black;"
         "background: #C8C8C8;"
         "selection-background-color: #F0F0F0;"
         "min-height:20;"
         "}"

      "QSpinBox  {"
        "border: 1px solid black;"
        "background: #C8C8C8;"
        "min-height:20;"
        "}"

      "QSpinBox::up-button  {"
        "border: 1px solid black;"
        "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
        "image: url(:/Media/plus_black.png);"
        "}"
            "QSpinBox::up-button:pressed  {"
                    "border: 2px solid black;"
                    "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
                    "image: url(:/Media/plus_black.png);"
                    "}"

        "QSpinBox::down-button  {"
          "border: 1px solid black;"
          "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
          "image: url(:/Media/minus_black.png);"

            "}"

            "QSpinBox::down-button:pressed  {"
              "border: 2px solid black;"
              "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
              "image: url(:/Media/minus_black.png);"

                "}"
            "QDoubleSpinBox  {"
              "border: 1px solid black;"
              "background: #C8C8C8;"
              "min-height:20;"
              "}"

            "QDoubleSpinBox::up-button  {"
              "border: 1px solid black;"
              "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
              "image: url(:/Media/plus_black.png);"
              "}"
                  "QDoubleSpinBox::up-button:pressed  {"
                          "border: 2px solid black;"
                          "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
                          "image: url(:/Media/plus_black.png);"
                          "}"

              "QDoubleSpinBox::down-button  {"
                "border: 1px solid black;"
                "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
                "image: url(:/Media/minus_black.png);"

                  "}"

                  "QDoubleSpinBox::down-button:pressed  {"
                    "border: 2px solid black;"
                    "width: 15px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */"
                    "image: url(:/Media/minus_black.png);"

                      "}"

            "QToolBar  {"
                "background: #C8C8C8;"
                "spacing: 3px; /* spacing between items in the tool bar */"
            "}"

            "QDockWidget  {"
                "border: 1px solid black;"
                 "background: #787878 ;"
            "}"

            "QDockWidget::title  {"
                "text-align: center; /* align the text to the left */"
                "background: #909090;"
                "height: 0px"

            "}"

            "QScrollBar:vertical  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "width: 10px;"
                "margin: 22px 0 22px 0;"
            "}"
            "QScrollBar::handle:vertical  {"
                "background: #585858 ;"
                "height: 20px;"
            "}"
            "QScrollBar::add-line:vertical  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "height: 20px;"
                "subcontrol-position: bottom;"
                "subcontrol-origin: margin;"
            "}"

            "QScrollBar::sub-line:vertical  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "height: 20px;"
                "subcontrol-position: top;"
                "subcontrol-origin: margin;"
            "}"
            "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical  {"
                "border: 1px solid black;"
                "width: 1px;"
                "height: 1px;"
                "background: black;"
            "}"

            "QScrollBar::up-arrow:vertical:pressed, QScrollBar::down-arrow:vertical:pressed {"
                "border: 2px solid black;"
                "width: 3px;"
                "height: 3px;"
                "background: black;"
            "}"

            "QScrollBar:horizontal  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "height: 10px;"
                "margin: 0px 20px 0 20px;"
            "}"
            "QScrollBar::handle:horizontal  {"
            "background: #585858 ;"
                "min-width: 20px;"
            "}"
            "QScrollBar::add-line:horizontal  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "width: 20px;"
                "subcontrol-position: right;"
                "subcontrol-origin: margin;"
            "}"

            "QScrollBar::sub-line:horizontal  {"
                "border: 1px solid black;"
                "background: #C8C8C8;"
                "width: 20px;"
                "subcontrol-position: left;"
                "subcontrol-origin: margin;"
            "}"

            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical  {"
                "background: none;"
            "}"

            "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal  {"
                "border: 1px solid black;"
                "width: 1px;"
                "height: 1px;"
                "background: black;"
            "}"

            "QScrollBar::left-arrow:horizontal:pressed, QScrollBar::right-arrow:horizontal:pressed  {"
                "border: 1px solid black;"
                "width: 3px;"
                "height: 3px;"
                "background: black;"
            "}"

            "QMenu {"
                 "background-color: #C8C8C8; /* sets background of the menu */"
                 "border: 1px solid black;"
                 "color:black;"
             "}"

             "QMenu::item {"
                 "/* sets background of menu item. set this to something non-transparent"
                    " if you want menu color and menu item color to be different */"
                 "background-color: transparent;"
             "}"

             "QMenu::item:selected { /* when user selects item using mouse or keyboard */"
                 "background-color: #787878;"
                 "color: white"
             "}"

            "QTreeView {"
                 "show-decoration-selected: 2;"
                 "alternate-background-color: yellow;"
                 "background:#E8E8E8"
            "}"

             "QTreeView::item {"

                 "border-top-color: transparent;"
                 "border-bottom-color: transparent;"
            "}"

             "QTreeView::item:hover {"
                 "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #A0A0A0 , stop: 1 #E0E0E0 );"
                 "border: 1px solid black;"
                 "color: black"
            "}"

             "QTreeView::item:selected {"
                "background-color:#585858;"
                "border:1px solid black;"
                "color: white"

            "}"

             "QTreeView::item:selected:active{"
                "background-color:#585858;"
                "border:1px solid black;"
                "color: white"
            "}"

             "QTreeView::item:selected:!active {"
                "background-color:#585858;"
                "border:1px solid black;"
                "color: white"

            "}"

            "QListView {"
            "show-decoration-selected: 2;"
            "alternate-background-color: yellow;"
            "background:#E8E8E8"
            "}"

             "QListView::item:alternate {"
                 "background: #EEEEEE;"
            "}"

             "QListView::item:selected {"
            "border: 1px solid black;"
            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #787878, stop: 1  #66FF99);"
            "color: black"
            "}"

             "QListView::item:selected:!active {"
                "background-color:#585858;"
                "border:1px solid black;"
                "color: white"
            "}"

             "QListView::item:selected:active {"
                "background-color:#585858;"
                "border:1px solid black;"
                "color: white"
            "}"

             "QListView::item:hover {"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #A0A0A0 , stop: 1 #E0E0E0 );"
                "border: 1px solid black;"
                "color: black"
            "}"

            "QToolBar {"
                 "background: #E0E0E0;"
                 "spacing: 3px; /* spacing between items in the tool bar */"
            "}"

            "QToolBar:selected {"
                 "background:#585858;"
                 "spacing: 3px; /* spacing between items in the tool bar */"
            "}"

            "QMenuBar {"
                 "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                                   "stop:0 lightgray, stop:1 darkgray);"
            "}"

             "QMenuBar::item {"
                 "spacing: 3px; /* spacing between menu bar items */"
                 "padding: 1px 4px;"
                 "background: transparent;"
            "}"

             "QMenuBar::item:selected { /* when selected using mouse or keyboard */"
                 "border: 1px solid black;"
                 "background-color:#585858;"
                 "color:white"
            "}"

             "QMenuBar::item:pressed {"
                 "border: 1px solid black;"
                 "background-color:#585858;"
                 "color:white"
            "}";

    return style;
}
