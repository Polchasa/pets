#include "styles.h"
#include "globals.h"

#include <QString>

QString setTopButtonsStyles() {
    return QStringLiteral("QPushButton {"
           "font-family: %1;"
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
                          "}").arg(fontName);
}

QString setEditStyleClassic() {
    return QStringLiteral("QLineEdit {"
           "font-family: %1;"
           "border: 0.5px solid #3498db;"
           "border-radius: 20px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
                          "}").arg(fontName);
}

QString setEditStyleBad() {
    return QStringLiteral("QLineEdit {"
           "font-family: %1;"
           "border: 0.5px solid #3498db;"
           "border-radius: 20px;"
           "color: #c0392b;"
           "background-color: #181818;"
                          "}").arg(fontName);
}

QString setTabWidgetStyle() {
    return "background-color: #181818;";
}

QString setLogInButtonStyle() {
    return QStringLiteral("QPushButton {"
           "font-family: %1;"
           "border: 0.5px solid #59916E;"
           "border-radius: 10px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
           "padding-left: 5px;"
           "padding-right: 5px;"
           "}"
           "QPushButton:disabled {"
           "font-family: %1;"
           "border: 0.5px solid #6C726E;"
           "color: #6C726E;"
           "}"
           "QPushButton:focus {"
           "border: 0.5px solid #1be34d;"
           "outline: none;"
                          "}").arg(fontName);
}

QString setLogOutButtonStyle() {
    return QStringLiteral("QPushButton {"
           "font-family: %1;"
           "border: 0.5px solid #e74c3c;"
           "border-radius: 10px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
           "padding-top: 10px;"
           "padding-bottom: 10px;"
           "margin-right: 15px;"
           "}"
           "QPushButton:focus {"
           "border: 0.5px solid #c0392b;"
           "outline: none;"
                          "}").arg(fontName);
}

QString setUserNameSurnameStyle() {
    return QStringLiteral("QLabel {"
           "font-family: %1;"
           "border: 0.5px solid #3498db;"
           "border-radius: 10px;"
           "color: #FFFFFF;"
           "padding-top: 3px;"
           "padding-bottom: 3px;"
           "margin-left: 15px;"
                          "}").arg(fontName)
        ;
}

QString setAddLessonStyle() {
    return QStringLiteral("QPushButton {"
           "font-family: %1;"
           "border: 0.5px solid #59916E;"
           "border-radius: 10px;"
           "color: #FFFFFF;"
           "background-color: #181818;"
           "margin-right: 15px;"
           "margin-left: 15px;"
           "}"
           "QPushButton:pressed {"
           "border: 0.5px solid #1be34d;"
           "}"
           "QPushButton:focus {"
           "outline: none;"
           "}").arg(fontName)
        ;
}

QString setDayDateStyle() {
    return QStringLiteral("QLabel {"
           "font-family: %1;"
           "color: #FFFFFF;"
           "padding-top: 3px;"
           "padding-bottom: 3px;"
                          "}").arg(fontName)
        ;
}

QString setNameLabelStyle() {
    return QStringLiteral("QLabel {"
           "color: #FFFFFF;"
           "font-family: %1;"
           "font-size: 12px;"
                          "}").arg(fontName);
}

QString setLabelStyle() {
    return QStringLiteral("QLabel {"
           "color: #6C726E;"
           "font-family: %1;"
                          "}").arg(fontName);
}

QString setLabelGoodStyle() {
    return QStringLiteral("QLabel {"
           "color: #2ecc71;"
           "font-family: %1;"
                          "}").arg(fontName);
}

QString setLabelBadStyle() {
    return QStringLiteral("QLabel {"
           "color: #c0392b;"
           "font-family: %1;"
                          "}").arg(fontName);
}
