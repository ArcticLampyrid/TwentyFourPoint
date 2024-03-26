#pragma once
#include <QStringView>
#include <cstddef>

enum class valid_solution_return_code
{
    valid = 0,
    wrong_result,
    number_not_allowed,
    number_not_used,
    unknown_token,
    operator_not_allowed,
};
bool is_solvable(int a, int b, int c, int d);
valid_solution_return_code is_valid_solution(QStringView expression, int *allowed_ints, size_t length_of_allowed_ints);
