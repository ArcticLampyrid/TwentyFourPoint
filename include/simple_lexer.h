#include <QIntegerForSize>
#include <QString>
#include <QStringView>

enum class token_type
{
    number,
    add,
    minus,
    multiply,
    divide,
    lparen,
    rparen,
    unknown,
    number_overflow,
    eof,
};

struct token_info
{
    token_type type;
    union {
        // 仅当 type == number 时有效
        int number;
        // 仅当 type == unknown 时有效
        char16_t unknown_char;
    } data;
};

class simple_lexer
{
  public:
    explicit simple_lexer(QStringView input);
    token_info next_token();
    [[nodiscard]] token_info current_token() const;

  private:
    QString input;
    qsizetype next_pos = 0;
    token_info current_token_info;
};