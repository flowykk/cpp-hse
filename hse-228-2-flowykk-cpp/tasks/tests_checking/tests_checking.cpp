#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {

    std::deque<std::string> deque;
    for (int i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Bottom) {
            deque.push_back(student_actions[i].name);
        } else {
            deque.push_front(student_actions[i].name);
        }
    }

    std::vector<std::string> result;
    for (int i = 0; i < queries.size(); ++i) {
        result.push_back(deque[queries[i] - 1]);
    }

    return result;
}
