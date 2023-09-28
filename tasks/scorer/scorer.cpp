#include "scorer.h"

bool CompareEvents(Event e1, Event e2) {
    return (e1.time < e2.time);
}

bool ContainsTask(std::vector<std::string> tasks, std::string taskname) {
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i] == taskname) {
            return true;
        }
    }
    return false;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<StudentName, std::vector<Event>> event_for_student;
    for (int i = 0; i < events.size(); ++i) {
        event_for_student[events[i].student_name].push_back(events[i]);
    }

    for (auto i = event_for_student.begin(); i != event_for_student.end(); ++i) {
        std::sort((*i).second.begin(), (*i).second.end(), CompareEvents);
    }

    ScoreTable result;
    for (auto i = event_for_student.begin(); i != event_for_student.end(); ++i) {
        auto curr_student_events = (*i).second;
        std::vector<std::string> processed_tasks;
        for (int j = 0; j < curr_student_events.size(); ++j) {
            auto curr_event = curr_student_events[j];
            if (!ContainsTask(processed_tasks, curr_event.task_name)) {
                processed_tasks.push_back(curr_event.task_name);
                auto last_merge = EventType::MergeRequestClosed;
                auto last_try = EventType::CheckFailed;
                for (int k = j; k < curr_student_events.size(); ++k) {
                    if (curr_event.task_name == curr_student_events[k].task_name) {
                        if (curr_student_events[k].event_type == EventType::MergeRequestOpen &&
                            curr_student_events[k].time <= score_time) {
                            last_merge = EventType::MergeRequestOpen;
                        }
                        if (curr_student_events[k].event_type == EventType::MergeRequestClosed &&
                            curr_student_events[k].time <= score_time) {
                            last_merge = EventType::MergeRequestClosed;
                        }
                        if (curr_student_events[k].event_type == EventType::CheckSuccess &&
                            curr_student_events[k].time <= score_time) {
                            last_try = EventType::CheckSuccess;
                        }
                        if (curr_student_events[k].event_type == EventType::CheckFailed &&
                            curr_student_events[k].time <= score_time) {
                            last_try = EventType::CheckFailed;
                        }
                    }
                }
                if (last_merge == EventType::MergeRequestClosed && curr_event.time <= score_time &&
                    last_try == EventType::CheckSuccess) {
                    result[(*i).first].insert(curr_event.task_name);
                }
            }
        }
    }

    return result;
}
