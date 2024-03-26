#include <QCoreApplication>
#include <QString>
#include <menu_ui_controller.h>
#include <view_ui_controller.h>

using namespace Qt::StringLiterals;

void menu_ui_controller::start()
{
    view_ui_controller::getInstance()->push(u"qrc:/twenty_four_point/qml/start_game.qml"_s);
}

void menu_ui_controller::view_rank_list()
{
    view_ui_controller::getInstance()->push(u"qrc:/twenty_four_point/qml/rank_list.qml"_s);
}

void menu_ui_controller::view_rule()
{
    view_ui_controller::getInstance()->push(u"qrc:/twenty_four_point/qml/view_rule.qml"_s);
}

void menu_ui_controller::quit_game()
{
    QCoreApplication::exit(0);
}
