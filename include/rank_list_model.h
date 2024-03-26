#pragma once
#include <QAbstractListModel>
#include <QByteArray>
#include <QModelIndex>
#include <QObject>
#include <QVariant>
#include <QtCore>
#include <QtQmlIntegration>
#include <rank_list_storage.h>
#include <vector>

class rank_list_model : public QAbstractListModel
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(RankListModel)

  public:
    rank_list_model();

    enum Role
    {
        Nickname = Qt::UserRole + 1,
        Score,
    };

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

  private:
    std::vector<rank_record_item> m_records;

  private slots:
    void update();
};
