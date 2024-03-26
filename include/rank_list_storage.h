#pragma once
#include <QObject>
#include <QString>
#include <vector>

struct rank_record_item
{
    QString nickname;
    int score;
};

class rank_list_storage : public QObject
{
    Q_OBJECT

    QString m_filename;

  private:
    rank_list_storage();

  public:
    static rank_list_storage *getInstance();
    std::vector<rank_record_item> read_records();
    void write_records(const std::vector<rank_record_item> &records);
    void add_record(const rank_record_item &item);

  signals:
    void recordChanged();
};
