QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    utimeeditwidget.cpp

HEADERS += \
    utimeeditwidget.h

FORMS += \
    utimeeditwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/icons.qrc

unix:!macx {
    isEmpty(prefix): prefix = /usr/local

    target.path = $$prefix/bin
    INSTALLS += target

    desktop_file.files = dist/utimeedit.desktop
    desktop_file.path = $$prefix/share/applications
    INSTALLS += desktop_file

    app_icon.files = dist/utimeedit.svg
    app_icon.path = $$prefix/share/icons/hicolor/scalable/apps
    INSTALLS += app_icon
}
