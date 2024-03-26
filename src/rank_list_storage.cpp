#include <QCoreApplication>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <algorithm>
#include <cstddef>
#include <rank_list_storage.h>
#include <vector>

using namespace Qt::StringLiterals;

// 定义常量：最大记录数量
const constexpr size_t MAX_RECORDS = 20;

rank_list_storage::rank_list_storage()
{
    // 构造函数，在构造对象时自动被调用

    // 获取可执行文件所在目录，拼接文件名
    m_filename = QCoreApplication::applicationDirPath() + u"/rank_list.txt"_s;
}

rank_list_storage *rank_list_storage::getInstance()
{
    // 单例模式
    // 创建一个全局唯一的对象，所有人都可以通过 getInstance() 获取这个对象

    // static 修饰的变量，只会被初始化一次，然后一直存在于内存中
    static rank_list_storage instance;

    // 返回指向这个对象的指针
    return &instance;
}

std::vector<rank_record_item> rank_list_storage::read_records()
{
    std::vector<rank_record_item> records;
    QFile file(m_filename);                                // 构建文件对象
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 打开文件
        return records;                                    // 如果打开失败，返回空的记录
    QTextStream in(&file); // 关联文件对象到文本流（通过文本流读取文本文件）
    while (!in.atEnd())    // 判断没有到达文件末尾
    {
        QString nickname = in.readLine();
        if (in.atEnd())
            break;
        QString score = in.readLine();
        rank_record_item item;
        item.nickname = nickname;
        item.score = score.toInt(); // 转换为整数
        records.push_back(item);
    }
    file.close();
    return records;
}

void rank_list_storage::write_records(const std::vector<rank_record_item> &records)
{
    QFile file(m_filename);                                 // 构建文件对象
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // 打开文件
        return;                                             // 如果打开失败，直接返回（跳过写出步骤）
    QTextStream out(&file);          // 关联文件对象到文本流（通过文本流写出文本文件）
    for (const auto &item : records) // 循环，遍历动态数组 records 中的每一个元素
    {
        out << item.nickname << "\n" << item.score << "\n"; // 写出
    }
    file.close(); // 关闭文件

    // 通知记录已经改变，emit 发出信号（added by 裴骏豪）
    emit recordChanged();
}

void rank_list_storage::add_record(const rank_record_item &item)
{
    // 读取
    std::vector<rank_record_item> records = read_records();

    // 添加记录
    records.push_back(item);

    // 排序
    std::sort(records.begin(), records.end(),
              [](const rank_record_item &a, const rank_record_item &b) { return a.score > b.score; });

    // 限制最大数量
    if (records.size() > MAX_RECORDS)
        records.resize(MAX_RECORDS);

    // 回写
    write_records(records);
}
