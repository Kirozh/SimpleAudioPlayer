#include "stylehelper.h"

QString StyleHelper::getWindowStyleSheet()
{
    return "QWidget { "
           "background-color: #454545; "
           "border: 1px solid black; "
           "}";
}

QString StyleHelper::getLabelStyleSheet()
{
    return "QLabel { "
           "color: #8f8f8f; "
           "border: none; "
           "margin: 6px; "
           "}";
}

QString StyleHelper::getCloseStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/icon3_br.png);"
           "background-color: none; "
           "icon-size: 12px;"
           "padding-left: 0px;"
           "padding-right: 0px;"
           "padding-top: 1px;"
           "padding-bottom: 1px;"
            "border: none "
           "}"
           "QToolButton:hover {"
           "image: url(:/buttons/icon3.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/icon3.png);"
            "background-color: none; "
           "}";
}

QString StyleHelper::getMaximizeStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/icon2.png);"
           "background-color: none;"
           "icon-size: 12px;"
           "padding-left: 0px;"
           "padding-right: 0px;"
           "padding-top: 1px;"
           "padding-bottom: 1px;"
           "border: none; "
           "}"
           "QToolButton:hover {"
           "image: url(:/buttons/icon2_br.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/icon2_br.png);"
           "background-color: none; "
           "}";
}

QString StyleHelper::getRestoreStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/icon2_1.png);"
          "background-color: none;"
           "icon-size: 12px;"
           "padding-left: 0px;"
           "padding-right: 0px;"
           "padding-top: 1px;"
           "padding-bottom: 1px;"
          "border:none; "
           "}"
           "QToolButton:hover {"
           "image: url(:/buttons/icon2_1_br.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/icon2_1_br.png);"
           "background-color: none; "
           "}";
}

QString StyleHelper::getMinimizeStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/icon1.png);"
           "background-color: none;"
           "icon-size: 12px;"
           "padding-left: 1px;"
           "padding-right: 0px;"
           "padding-top: 0px;"
           "padding-bottom: 1px;"
           "border: none; "
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/icon1_br.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/icon1_br.png);"
           "background-color: none; "
           "}";
}

QString StyleHelper::getNextStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/next_white.png);"
           "icon-size: 24px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/next_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/next_blue.png)"
           "}";
}

QString StyleHelper::getPreviousStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/prev_white.png);"
           "icon-size: 24px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/prev_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/prev_blue.png)"
           "}";
}

QString StyleHelper::getPlayStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/play_white.png);"
           "icon-size: 96px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/play_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/play_blue.png)"
           "}";
}

QString StyleHelper::getPauseStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/pause_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/pause_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/pause_blue.png)"
           "}";
}
QString StyleHelper::getStopStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/stop_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/stop_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/stop_blue.png)"
           "}";
}
QString StyleHelper::getRepeatCurrentStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/repeat_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/repeat_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/repeat_blue.png)"
           "}";
}
QString StyleHelper::getRepeatStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/loop_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/loop_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/loop_blue.png)"
           "}";
}
QString StyleHelper::getSoundStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/sound_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/sound_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/sound_blue.png)"
           "}";
}

QString StyleHelper::getMuteStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/mute_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/mute_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/mute_blue.png)"
           "}";
}

QString StyleHelper::getMenuStyleSheet()
{
    return "QToolButton { "
           "image: url(:/buttons/menu_white.png);"
           "icon-size: 48px;"
           "padding: 0px;"
           "margin: 0px;"
           "border: none;"
           "}"
           "QToolButton:hover { "
           "image: url(:/buttons/menu_blue.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/buttons/menu_blue.png)"
           "}";
}
/*
QString StyleHelper::getTableViewStyleSheet()
{
    return "QTableView { "
           "background-color: white; "
           "color: black; "
           "border: 1px solid #e2e2de;"
           "}"
           "QTableView::item:selected {"
           "background-color: #de8e37;"
           "}"
           "QHeaderView::section:horizintal {"
           "background-color: white;"
           "border-style: none;"
           "color: black; "
           "border: 1px solid #e2e2de; "
           "padding: 6px; "
           "}";
}
*/
