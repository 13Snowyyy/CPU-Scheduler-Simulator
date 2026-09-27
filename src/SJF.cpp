#include <algorithm>
#include <vector>

#include "Scheduler.h"

AlgorithmResult SJF::run(const std::vector<Process>& processes, int quantum) {
    (void)quantum;

    std::vector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process& left, const Process& right) {
        if (left.arrivalTime != right.arrivalTime) {
            return left.arrivalTime < right.arrivalTime;
        }
        return left.id < right.id;
    });

    std::vector<int> ready;
    size_t nextArrivalIndex = 0;
    int currentTime = 0;
    std::vector<GanttEntry> gantt;

    while (nextArrivalIndex < sorted.size() || !ready.empty()) {
        while (nextArrivalIndex < sorted.size() && sorted[nextArrivalIndex].arrivalTime <= currentTime) {
            ready.push_back(static_cast<int>(nextArrivalIndex));
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

        auto bestIt = std::min_element(ready.begin(), ready.end(), [&](int leftIndex, int rightIndex) {
            const Process& left = sorted[leftIndex];
            const Process& right = sorted[rightIndex];
            if (left.burstTime != right.burstTime) {
                return left.burstTime < right.burstTime;
            }
            if (left.arrivalTime != right.arrivalTime) {
                return left.arrivalTime < right.arrivalTime;
            }
            return left.id < right.id;
        });

        int selectedIndex = *bestIt;
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

        ready.erase(bestIt);
    }

    return buildAlgorithmResult("SJF", sorted, gantt);
}
