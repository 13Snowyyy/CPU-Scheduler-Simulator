#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>
#include "Process.h"

class Scheduler {
public:
    virtual ~Scheduler() = default;
    virtual AlgorithmResult run(const std::vector<Process>& processes, int quantum = 0) = 0;
};

class FCFS : public Scheduler {
public:
    AlgorithmResult run(const std::vector<Process>& processes, int quantum = 0) override;
};

class SJF : public Scheduler {
public:
    AlgorithmResult run(const std::vector<Process>& processes, int quantum = 0) override;
};

class PriorityScheduler : public Scheduler {
public:
    AlgorithmResult run(const std::vector<Process>& processes, int quantum = 0) override;
};

class RoundRobin : public Scheduler {
public:
    AlgorithmResult run(const std::vector<Process>& processes, int quantum = 0) override;
};

class Metrics {
public:
    static void finalizeProcesses(std::vector<Process>& processes);
    static double averageWaitingTime(const std::vector<Process>& processes);
    static double averageTurnaroundTime(const std::vector<Process>& processes);
    static double averageResponseTime(const std::vector<Process>& processes);
    static double cpuUtilization(const std::vector<Process>& processes, int totalTime);
    static int totalSimulationTime(const std::vector<Process>& processes);
};

class GanttChart {
public:
    static void addIdle(std::vector<GanttEntry>& gantt, int start, int end);
    static std::string toText(const std::vector<GanttEntry>& gantt);
    static void print(const std::vector<GanttEntry>& gantt);
};

AlgorithmResult buildAlgorithmResult(const std::string& algorithmName,
    std::vector<Process> processes,
    const std::vector<GanttEntry>& gantt);

#endif
