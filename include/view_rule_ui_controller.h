#pragma once
#include <QObject>
#include <QString>
#include <QtQmlIntegration>

class view_rule_ui_controller : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ViewRuleUIController)
    QML_SINGLETON
  private:
    QString rule{};

  public:
    view_rule_ui_controller();
    Q_PROPERTY(QString rule READ get_rule CONSTANT)
    [[nodiscard]] QString get_rule() const;
};
