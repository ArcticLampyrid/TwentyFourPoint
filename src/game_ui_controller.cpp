#include <algorithm_utils.h>
#include <game_ui_controller.h>
#include <limits>
#include <random_nickname.h>
#include <rank_list_storage.h>
#include <utility>
#include <view_ui_controller.h>

using namespace Qt::StringLiterals;

static struct
{
    int time_per_problem;  // 每道题超时时间，秒
    int score_per_problem; // 每道题分数
    int n_problems;        // 每局游戏题目数量
} difficulty_settings[] = {
    {45, 3, 3},                               // 简单
    {36, 4, 3},                               // 中等
    {28, 5, 3},                               // 困难
    {28, 5, std::numeric_limits<int>::max()}, // 无尽
};

game_ui_controller::game_ui_controller()
{
    connect(&timer, &QTimer::timeout, this, [this]() {
        --time_elapsed;
        emit timeElapsedChanged();
        if (time_elapsed == 0)
        {
            timer.stop();
            remaining_problems = 0;
            emit timeout();
        }
    });
    connect(this, &game_ui_controller::gameFinished, this, [this]() {
        rank_list_storage::getInstance()->add_record({nickname, score});
    });
}

void game_ui_controller::start_game(QString nickname, int difficulty)
{
    if (nickname.isEmpty())
    {
        nickname = u"Player"_s;
    }
    if (difficulty < 0 || difficulty > 3)
    {
        difficulty = 0;
    }
    this->nickname = std::move(nickname);
    this->difficulty = difficulty;
    emit nicknameChanged();
    emit difficultyChanged();
    set_score(0);
    this->remaining_problems = difficulty_settings[difficulty].n_problems;
    view_ui_controller::getInstance()->push(u"qrc:/twenty_four_point/qml/game.qml"_s);
}

bool game_ui_controller::new_problem()
{
    if (remaining_problems == -1)
    {
        return false;
    }
    if (remaining_problems == 0)
    {
        emit gameFinished();
        remaining_problems = -1;
        return false;
    }
    remaining_problems--;

    std::uniform_int_distribution<int> card_distribute{1, 10};
    std::uniform_int_distribution<int> card_color_distribute{0, 3};
    for (int i = 0; i < 4; ++i)
    {
        cards[i] = card_distribute(random_engine);
        card_colors[i] = card_color_distribute(random_engine);
    }
    time_elapsed = difficulty_settings[this->difficulty].time_per_problem;
    emit cardsChanged();
    emit timeElapsedChanged();
    timer.start(1000);
    return true;
}

void game_ui_controller::finish_game()
{
    if (remaining_problems == -1)
    {
        return;
    }
    remaining_problems = -1;
    emit gameFinished();
}

void game_ui_controller::submit_answer(QString answer)
{
    timer.stop();
    valid_solution_return_code result;
    if (answer.trimmed().toUpper() == u"NO"_s)
    {
        result = is_solvable(cards[0], cards[1], cards[2], cards[3]) ? valid_solution_return_code::wrong_result
                                                                     : valid_solution_return_code::valid;
    }
    else
    {
        result = is_valid_solution(answer, cards.data(), cards.size());
    }
    if (result == valid_solution_return_code::valid)
    {
        set_score(score + difficulty_settings[this->difficulty].score_per_problem);
        emit answerAccepted();
    }
    else
    {
        remaining_problems = 0;
        emit answerRejected();
    }
}

QString game_ui_controller::random_nickname()
{
    return ::random_nickname();
}

QString game_ui_controller::get_nickname() const
{
    return nickname;
}

int game_ui_controller::get_difficulty() const
{
    return difficulty;
}

QList<int> game_ui_controller::get_cards() const
{
    return cards;
}

QList<int> game_ui_controller::get_card_colors() const
{
    return card_colors;
}

int game_ui_controller::get_time_elapsed() const
{
    return time_elapsed;
}

void game_ui_controller::set_score(int score)
{
    this->score = score;
    emit scoreChanged();
}

int game_ui_controller::get_score() const
{
    return score;
}
