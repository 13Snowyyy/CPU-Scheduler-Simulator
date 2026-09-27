#include <algorithm>
#include <queue>
#include <vector>

#include "Scheduler.h"

AlgorithmResult FCFS::run(const std::vector<Process>& processes, int quantum) {
    (void)quantum;

    std::vector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process& left, const Process& right) {
        if (left.arrivalTime != right.arrivalTime) {
            return left.arrivalTime < right.arrivalTime;
        }
        return left.id < right.id;
    });

    std::queue<int> readyQueue;
    for (size_t i = 0; i < sorted.size(); ++i) {
        readyQueue.push(static_cast<int>(i));
    }

    int currentTime = 0;
    std::vector<GanttEntry> gantt;

    while (!readyQueue.empty()) {
        int index = readyQueue.front();
        readyQueue.pop();

        Process& process = sorted[index];

        if (currentTime < process.arrivalTime) {
            GanttChart::addIdle(gantt, currentTime, process.arrivalTime);
            currentTime = process.arrivalTime;
        }

        if (process.firstStartTime == -1) {
            process.firstStartTime = currentTime;
        }

        int startTime = currentTime;
        int endTime = currentTime + process.burstTime;
        gantt.push_back({startTime, endTime, process.id, false});

        process.completionTime = endTime;
        process.remainingTime = 0;
        currentTime = endTime;
    }

    return buildAlgorithmResult("FCFS", sorted, gantt);
}
