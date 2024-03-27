#include <QFile>
#include <QIODevice>
#include <QLocale>
#include <QString>
#include <QTextStream>
#include <view_rule_ui_controller.h>

using namespace Qt::StringLiterals;
view_rule_ui_controller::view_rule_ui_controller()
{
    QLocale locale = QLocale::system();
    QFile file(u":/twenty_four_point/resources/rule_"_s + locale.name() + u".txt"_s);
    if (!file.exists())
        file.setFileName(u":/twenty_four_point/resources/rule_"_s + locale.name().section(u'_', 0, 0) + u".txt"_s);
    if (!file.exists())
        file.setFileName(u":/twenty_four_point/resources/rule.txt"_s);
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
