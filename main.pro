QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountmanagementwidget.cpp \
    accountmodel.cpp \
    administrator.cpp \
    backup.cpp \
    forecast.cpp \
    forget.cpp \
    login_with_lock.cpp \
    main.cpp \
    data.cpp \
    change.cpp \
    history.cpp \
    in.cpp \
    jiaoyi.cpp \
    jichu.cpp \
    out.cpp \
    succes.cpp \
    transfer.cpp \
    widget.cpp \
    xinxi.cpp \
    xiugai.cpp \
    transaction_history.cpp

HEADERS += \
    accountmanagementwidget.h \
    accountmodel.h \
    administrator.h \
    backup.h \
    data.h \
    forecast.h \
    forget.h \
    login_with_lock.h \
    change.h \
    history.h \
    in.h \
    jiaoyi.h \
    jichu.h \
    out.h \
    succes.h \
    transfer.h \
    widget.h \
    xinxi.h \
    xiugai.h \
    transaction_history.h

FORMS += \
    accountmanagementwidget.ui \
    administrator.ui \
    backup.ui \
    data.ui \
    forecast.ui \
    forget.ui \
    login_with_lock.ui \
    change.ui \
    history.ui \
    in.ui \
    jiaoyi.ui \
    jichu.ui \
    out.ui \
    succes.ui \
    transfer.ui \
    widget.ui \
    xinxi.ui \
    xiugai.ui \
    transaction_history.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc \
    qss.qrc
