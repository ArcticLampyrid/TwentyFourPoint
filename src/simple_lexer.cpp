#include <QChar>
#include <limits>
#include <simple_lexer.h>

simple_lexer::simple_lexer(QStringView input) : input(input.toString())
{
}

token_info simple_lexer::next_token()
{
    token_info token;
    if (this->next_pos >= this->input.size())
    {
        token.type = token_type::eof;
    }
    else
    {
        QChar ch = this->input[this->next_pos];
        if (ch.isDigit())
        {
            token.type = token_type::number;
            token.data.number = 0;
            while (this->next_pos < this->input.size() && this->input[this->next_pos].isDigit())
            {
                ch = this->input[this->next_pos];
                if (token.data.number > (std::numeric_limits<int>::max() - ch.digitValue()) / 10)
                {
                    token.type = token_type::number_overflow;
                }
                token.data.number = token.data.number * 10 + ch.digitValue();
                this->next_pos++;
            }
        }
        else if (ch == u'+' || ch == u'＋')
        {
            token.type = token_type::add;
            this->next_pos++;
        }
        else if (ch == u'-')
        {
            token.type = token_type::minus;
            this->next_pos++;
        }
        else if (ch == u'*' || ch == u'×')
        {
            token.type = token_type::multiply;
            this->next_pos++;
        }
        else if (ch == u'/' || ch == u'÷')
        {
            token.type = token_type::divide;
            this->next_pos++;
        }
        else if (ch == u'(' || ch == u'（')
        {
            token.type = token_type::lparen;
            this->next_pos++;
        }
        else if (ch == u')' || ch == u'）')
        {
            token.type = token_type::rparen;
            this->next_pos++;
        }
        else
        {
            token.type = token_type::unknown;
            token.data.unknown_char = ch.unicode();
            this->next_pos++;
        }
    }
    this->current_token_info = token;
    return token;
}

token_info simple_lexer::current_token() const
{
    return this->current_token_info;
}
