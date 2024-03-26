#include <QJSEngine>
#include <QQmlEngine>
#include <QtCore>
#include <view_ui_controller.h>

void view_ui_controller::push(QStringView page)
{
    emit pagePushed(page.toString());
}

void view_ui_controller::pop()
{
    emit pagePopped();
}

view_ui_controller *view_ui_controller::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

view_ui_controller *view_ui_controller::getInstance()
{
    static view_ui_controller instance;
    return &instance;
}