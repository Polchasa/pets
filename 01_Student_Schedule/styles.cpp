#include <QString>

QString setTopButtonsStyles() {
    return "QPushButton {"
           "font-family: Roboto Light;"
           "font-size: 14pt;"
           "border-radius: 0px;"
           "background-color: #212121;"
           "border: 0px;"
           "color: #FFFFFF"           
           "}"
           "QPushButton:checked {"
           "background-color: #181818;"
           "border: 0px;"
           "}"
           "QPushButton:hover {"
           "background-color: #232323;"
           "}"
           "QPushButton:checked:hover {"
           "background-color: #181818;"
           "border: 0px;"
           "}";
}

QString setEditStyleClassic() {
    return "QLineEdit {"
           "font-family: Roboto Light;"
           "border: 0.5px solid #3498db;"
           "border-radius: 20px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
           "}";
}

QString setEditStyleBad() {
    return "QLineEdit {"
           "font-family: Roboto Light;"
           "border: 0.5px solid #3498db;"
           "border-radius: 20px;"
           "color: #c0392b;"
           "background-color: #181818;"
           "}";
}

QString setTabWidgetStyle() {
    return "background-color: #181818;";
}

QString setLogInButtonStyle() {
    return "QPushButton {"
           "font-family: Roboto Light;"
           "border: 0.5px solid #59916E;"
           "border-radius: 10px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
           "padding-left: 5px;"
           "padding-right: 5px;"
           "}"
           "QPushButton:disabled {"
           "font-family: Roboto Light;"
           "border: 0.5px solid #6C726E;"
           "color: #6C726E;"
           "}";
}

QString setLabelStyle() {
    return "QLabel {"
           "color: #6C726E;"
           "font-family: Roboto Light;"
           "}";
}

QString setLabelGoodStyle() {
    return "QLabel {"
           "color: #2ecc71;"
           "font-family: Roboto Light;"
           "}";
}

QString setLabelBadStyle() {
    return "QLabel {"
           "color: #c0392b;"
           "font-family: Roboto Light;"
           "}";
}

