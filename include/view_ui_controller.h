#pragma once
#include <QObject>
#include <QString>
#include <QStringView>
#include <QtQmlIntegration>

class QJSEngine;
class QQmlEngine;

class view_ui_controller : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ViewUIController)
    QML_SINGLETON

    view_ui_controller() = default;

  public:
    Q_INVOKABLE void push(QStringView page);
    Q_INVOKABLE void pop();
    static view_ui_controller *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    static view_ui_controller *getInstance();

  signals:
    void pagePushed(const QString &page);
    void pagePopped();
};
