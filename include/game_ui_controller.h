#pragma once
#include <QList>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtQmlIntegration>
#include <random>

class game_ui_controller : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(GameUIController)
    QML_SINGLETON
  private:
    // 玩家昵称
    QString nickname{};

    // 当前难度
    int difficulty{};

    // 当前分数
    int score{};

    // 4 张牌的花色，0-3，辅助 UI 显示
    QList<int> card_colors{0, 0, 0, 0};

    // 4 张牌
    QList<int> cards{0, 0, 0, 0};

    // 用于计时的定时器
    QTimer timer{};
    // 用于计时的变量，单位为秒
    int time_elapsed{};

    // 随机数引擎
    std::mt19937 random_engine{std::random_device{}()};

    // 剩余题目数量，-1 表示已经结束
    int remaining_problems = 0;

  public:
    game_ui_controller();
    Q_PROPERTY(QString nickname READ get_nickname NOTIFY nicknameChanged)
    Q_PROPERTY(int difficulty READ get_difficulty NOTIFY difficultyChanged)
    Q_PROPERTY(int score READ get_score WRITE set_score NOTIFY scoreChanged)
    Q_PROPERTY(QList<int> cards READ get_cards NOTIFY cardsChanged)
    Q_PROPERTY(QList<int> card_colors READ get_card_colors NOTIFY cardColorsChanged)
    Q_PROPERTY(int time_elapsed READ get_time_elapsed NOTIFY timeElapsedChanged)
    void set_score(int score);
    [[nodiscard]] int get_score() const;
    [[nodiscard]] QString get_nickname() const;
    [[nodiscard]] int get_difficulty() const;
    [[nodiscard]] QList<int> get_cards() const;
    [[nodiscard]] QList<int> get_card_colors() const;
    [[nodiscard]] int get_time_elapsed() const;
    Q_INVOKABLE void start_game(QString nickname, int difficulty);
    Q_INVOKABLE bool new_problem();
    Q_INVOKABLE void submit_answer(QString answer);
    Q_INVOKABLE QString random_nickname();
    Q_INVOKABLE void finish_game();

  signals:
    void nicknameChanged();
    void difficultyChanged();
    void scoreChanged();
    void cardsChanged();
    void cardColorsChanged();
    void timeElapsedChanged();
    void timeout();
    void answerAccepted();
    void answerRejected();
    void gameFinished();
};
