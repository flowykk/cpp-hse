#include "admission.h"

bool CompareStudents(std::pair<Applicant, const Student*> p1, std::pair<Applicant, const Student*> p2) {
    auto applicant1 = p1.first;
    auto applicant2 = p2.first;
    if (applicant1.points > applicant2.points) {
        return true;
    } else if (applicant1.points < applicant2.points) {
        return false;
    } else {
        if (applicant1.student.birth_date.year < applicant2.student.birth_date.year) {
            return true;
        } else if (applicant1.student.birth_date.year > applicant2.student.birth_date.year) {
            return false;
        } else {
            if (applicant1.student.birth_date.month < applicant2.student.birth_date.month) {
                return true;
            } else if (applicant1.student.birth_date.month > applicant2.student.birth_date.month) {
                return false;
            } else {
                if (applicant1.student.birth_date.day < applicant2.student.birth_date.day) {
                    return true;
                } else if (applicant1.student.birth_date.day > applicant2.student.birth_date.day) {
                    return false;
                } else {
                    if (applicant1.student.name > applicant2.student.name) {
                        return true;
                    } else if (applicant1.student.name < applicant2.student.name) {
                        return false;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<std::pair<Applicant, const Student*>> pairs;
    for (int i = 0; i < applicants.size(); ++i) {
        pairs.push_back(std::make_pair(applicants[i], &applicants[i].student));
    }

    std::sort(pairs.begin(), pairs.end(), CompareStudents);

    std::unordered_map<std::string, std::vector<const Student*>> result;
    for (int i = 0; i < pairs.size(); ++i) {
        auto app = pairs[i].first;
        for (int j = 0; j < app.wish_list.size(); ++j) {
            University uni;
            for (int k = 0; k < universities.size(); ++k) {
                if (universities[k].name == app.wish_list[j]) {
                    uni = universities[k];
                    break;
                }
            }
            if (result[uni.name].size() < uni.max_students) {
                result[uni.name].push_back(pairs[i].second);
                break;
            }
        }
    }

    return result;
}
