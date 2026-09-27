#include <algorithm>
#include <queue>
#include <vector>

#include "Scheduler.h"

AlgorithmResult PriorityScheduler::run(const std::vector<Process>& processes, int quantum) {
    (void)quantum;

    std::vector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process& left, const Process& right) {
        if (left.arrivalTime != right.arrivalTime) {
            return left.arrivalTime < right.arrivalTime;
        }
        return left.id < right.id;
    });

    auto priorityComparator = [&sorted](int leftIndex, int rightIndex) {
        const Process& left = sorted[leftIndex];
        const Process& right = sorted[rightIndex];

        if (left.priority != right.priority) {
            return left.priority > right.priority;
        }
        if (left.arrivalTime != right.arrivalTime) {
            return left.arrivalTime > right.arrivalTime;
        }
        return left.id > right.id;
    };

    std::priority_queue<int, std::vector<int>, decltype(priorityComparator)> ready(priorityComparator);
    size_t nextArrivalIndex = 0;
    int currentTime = 0;
    std::vector<GanttEntry> gantt;

    while (nextArrivalIndex < sorted.size() || !ready.empty()) {
        while (nextArrivalIndex < sorted.size() && sorted[nextArrivalIndex].arrivalTime <= currentTime) {
            ready.push(static_cast<int>(nextArrivalIndex));
            ++nextArrivalIndex;
        }

        if (ready.empty()) {
            if (nextArrivalIndex < sorted.size()) {
                int nextArrivalTime = sorted[nextArrivalIndex].arrivalTime;
                GanttChart::addIdle(gantt, currentTime, nextArrivalTime);
                currentTime = nextArrivalTime;
            } else {
                break;
            }
            continue;
        }

        int selectedIndex = ready.top();
        ready.pop();

        Process& selectedProcess = sorted[selectedIndex];

        if (selectedProcess.firstStartTime == -1) {
            selectedProcess.firstStartTime = currentTime;
        }

        int startTime = currentTime;
        int endTime = currentTime + selectedProcess.burstTime;
        gantt.push_back({startTime, endTime, selectedProcess.id, false});

        selectedProcess.completionTime = endTime;
        selectedProcess.remainingTime = 0;
        currentTime = endTime;
    }

    return buildAlgorithmResult("Priority Scheduling", sorted, gantt);
}
