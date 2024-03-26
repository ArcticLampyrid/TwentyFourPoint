#include <rank_list_model.h>
#include <rank_list_storage.h>

rank_list_model::rank_list_model()
{
    connect(rank_list_storage::getInstance(), &rank_list_storage::recordChanged, this, &rank_list_model::update);
    update();
}

int rank_list_model::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return static_cast<int>(m_records.size());
}

QVariant rank_list_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_records.size())
        return {};

    const auto &element = m_records.at(index.row());

    switch (role)
    {
    case Role::Nickname:
        return element.nickname;
    case Role::Score:
        return element.score;
    default:
        break;
    }

    return {};
}

QHash<int, QByteArray> rank_list_model::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty())
    {
        roles.insert(Nickname, "nickname");
        roles.insert(Score, "score");
    }
    return roles;
}

void rank_list_model::update()
{
    beginResetModel();
    m_records = rank_list_storage::getInstance()->read_records();
    endResetModel();
}