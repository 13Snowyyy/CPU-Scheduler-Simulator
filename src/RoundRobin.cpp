#include <algorithm>
#include <queue>
#include <stdexcept>
#include <vector>

#include "Scheduler.h"

AlgorithmResult RoundRobin::run(const std::vector<Process>& processes, int quantum) {
    if (quantum <= 0) {
        throw std::invalid_argument("Round Robin quantum must be greater than zero.");
    }

    std::vector<Process> sorted = processes;
    std::sort(sorted.begin(), sorted.end(), [](const Process& left, const Process& right) {
        if (left.arrivalTime != right.arrivalTime) {
            return left.arrivalTime < right.arrivalTime;
        }
        return left.id < right.id;
    });

    std::queue<int> readyQueue;
    size_t nextArrivalIndex = 0;
    int currentTime = 0;
    std::vector<GanttEntry> gantt;

    while (nextArrivalIndex < sorted.size() || !readyQueue.empty()) {
        while (nextArrivalIndex < sorted.size() && sorted[nextArrivalIndex].arrivalTime <= currentTime) {
            readyQueue.push(static_cast<int>(nextArrivalIndex));
            ++nextArrivalIndex;
        }

        if (readyQueue.empty()) {
            if (nextArrivalIndex < sorted.size()) {
                int nextArrivalTime = sorted[nextArrivalIndex].arrivalTime;
                GanttChart::addIdle(gantt, currentTime, nextArrivalTime);
                currentTime = nextArrivalTime;
            } else {
                break;
            }
            continue;
        }

        int selectedIndex = readyQueue.front();
        readyQueue.pop();

        Process& selectedProcess = sorted[selectedIndex];
        if (selectedProcess.firstStartTime == -1) {
            selectedProcess.firstStartTime = currentTime;
        }

        int slice = std::min(quantum, selectedProcess.remainingTime);
        int startTime = currentTime;
        int endTime = currentTime + slice;
        gantt.push_back({startTime, endTime, selectedProcess.id, false});

        currentTime = endTime;
        selectedProcess.remainingTime -= slice;

        while (nextArrivalIndex < sorted.size() && sorted[nextArrivalIndex].arrivalTime <= currentTime) {
            readyQueue.push(static_cast<int>(nextArrivalIndex));
            ++nextArrivalIndex;
        }

        if (selectedProcess.remainingTime > 0) {
            readyQueue.push(selectedIndex);
        } else {
            selectedProcess.completionTime = currentTime;
        }
    }

    return buildAlgorithmResult("Round Robin", sorted, gantt);
}
