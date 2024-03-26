#pragma once
#include <QObject>
#include <QtQmlIntegration>

class menu_ui_controller : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(MenuUIController)
    QML_SINGLETON
  public:
    menu_ui_controller() = default;
    Q_INVOKABLE void start();
    Q_INVOKABLE void view_rank_list();
    Q_INVOKABLE void view_rule();
    Q_INVOKABLE void quit_game();
  signals:
};
