#include <QStringView>
#include <algorithm>
#include <algorithm_utils.h>
#include <cmath>
#include <functional>
#include <iterator>
#include <simple_lexer.h>
#include <stack>
#include <unordered_map>

static std::function<double(double, double)> possible_ops[] = {
    [](double a, double b) { return a + b; },
    [](double a, double b) { return a - b; },
    [](double a, double b) { return a * b; },
    [](double a, double b) { return a / b; },
};

bool is_solvable(int a, int b, int c, int d)
{
    int seq[] = {a, b, c, d};
    for (int seq_id = 0; seq_id < 4 * 3 * 2 * 1; seq_id++)
    {
        // seq 为 4 个数的全排列
        for (auto &op1 : possible_ops)
        {
            for (auto &op2 : possible_ops)
            {
                for (auto &op3 : possible_ops)
                {
                    // {op1, op2, op3} 任何有效运算符（4*4*4 种可能）
                    if (std::abs(op3(op2(op1(seq[0], seq[1]), seq[2]), seq[3]) - 24) < 0.0001)
                    {
                        return true;
                    }
                }
            }
        }
        std::next_permutation(std::begin(seq), std::end(seq));
    }
    return false;
}

static int get_binary_op_priority(token_type op)
{
    switch (op)
    {
    case token_type::add:
    case token_type::minus:
        return 1;
    case token_type::multiply:
    case token_type::divide:
        return 2;
    default:
        return 0;
    }
}

static bool is_binary_op(token_type op)
{
    return op == token_type::add || op == token_type::minus || op == token_type::multiply || op == token_type::divide;
}

static double caculate_binary_op(double a, double b, token_type op)
{
    switch (op)
    {
    case token_type::add:
        return a + b;
    case token_type::minus:
        return a - b;
    case token_type::multiply:
        return a * b;
    case token_type::divide:
        return a / b;
    default:
        return 0;
    }
}

static bool evaluate_top_op(std::stack<token_type> &op_stack, std::stack<double> &num_stack)
{
    token_type type = op_stack.top();
    op_stack.pop();
    double b = num_stack.top();
    num_stack.pop();
    double a = num_stack.top();
    num_stack.pop();
    num_stack.push(caculate_binary_op(a, b, type));
    return true;
}

valid_solution_return_code is_valid_solution(QStringView expression, int *allowed_ints, size_t length_of_allowed_ints)
{
    std::unordered_map<int, int> counts;
    for (size_t i = 0; i < length_of_allowed_ints; i++)
    {
        if (counts.find(allowed_ints[i]) == counts.end())
        {
            counts.insert({allowed_ints[i], 1});
        }
        else
        {
            counts[allowed_ints[i]]++;
        }
    }
    std::stack<token_type> op_stack;
    std::stack<double> num_stack;
    bool allow_op = false;
    double result = 0;

    simple_lexer lexer(expression);
    token_info token = lexer.next_token();
    while (token.type != token_type::eof)
    {
        switch (token.type)
        {
        case token_type::number_overflow:
            return valid_solution_return_code::number_not_allowed;
        case token_type::number:
            if (counts.find(token.data.number) == counts.end())
            {
                return valid_solution_return_code::number_not_allowed;
            }
            if (--counts[token.data.number] == 0)
            {
                counts.erase(token.data.number);
            }
            num_stack.push(token.data.number);
            allow_op = true;
            break;
        case token_type::lparen:
            op_stack.push(token_type::lparen);
            allow_op = false;
            break;
        case token_type::rparen: {
            while (op_stack.top() != token_type::lparen)
            {
                evaluate_top_op(op_stack, num_stack);
            }
            op_stack.pop(); // pop l-paren
            allow_op = true;
            break;
        }
        case token_type::add:
        case token_type::minus:
        case token_type::multiply:
        case token_type::divide: {
            if (!allow_op)
            {
                return valid_solution_return_code::operator_not_allowed;
            }
            while (!op_stack.empty() && is_binary_op(op_stack.top()) &&
                   get_binary_op_priority(op_stack.top()) >= get_binary_op_priority(token.type))
            {
                evaluate_top_op(op_stack, num_stack);
            }
            op_stack.push(token.type);
            allow_op = false;
            break;
        }
        default:
            return valid_solution_return_code::unknown_token;
        }

        token = lexer.next_token();
    }
    while (!op_stack.empty())
    {
        evaluate_top_op(op_stack, num_stack);
    }

    if (num_stack.size() != 1 || std::abs(num_stack.top() - 24) >= 0.0001)
    {
        return valid_solution_return_code::wrong_result;
    }
    if (!counts.empty())
    {
        return valid_solution_return_code::number_not_used;
    }
    return valid_solution_return_code::valid;
}
