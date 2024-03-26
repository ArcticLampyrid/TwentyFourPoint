#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <view_rule_ui_controller.h>

using namespace Qt::StringLiterals;
view_rule_ui_controller::view_rule_ui_controller()
{
    QFile file(u":/twenty_four_point/resources/rule.txt"_s);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    rule = in.readAll();
    file.close();
}
QString view_rule_ui_controller::get_rule() const
{
    return rule;
}
