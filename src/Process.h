#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

struct Process {
    int id = 0;
    std::string name;
    int arrivalTime = 0;
    int burstTime = 0;
    int priority = 0;
    int remainingTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
    int completionTime = 0;
    int responseTime = 0;
    int firstStartTime = -1;

    Process() = default;
    Process(int idValue, std::string processName, int arrival, int burst, int priorityValue)
        : id(idValue), name(processName), arrivalTime(arrival), burstTime(burst), priority(priorityValue), remainingTime(burst) {}
};

struct GanttEntry {
    int startTime = 0;
    int endTime = 0;
    int processId = -1;
    bool isIdle = false;
};

struct AlgorithmResult {
    std::string algorithmName;
    std::vector<Process> processes;
    std::vector<GanttEntry> gantt;
    double averageWaitingTime = 0.0;
    double averageTurnaroundTime = 0.0;
    double averageResponseTime = 0.0;
    double cpuUtilization = 0.0;
    int totalSimulationTime = 0;
};

#endif
