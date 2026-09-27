#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "Scheduler.h"

void Metrics::finalizeProcesses(std::vector<Process>& processes) {
    for (Process& process : processes) {
        if (process.completionTime == 0 && process.burstTime > 0) {
            process.completionTime = process.arrivalTime + process.burstTime;
        }

        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
        process.responseTime = (process.firstStartTime >= 0) ? (process.firstStartTime - process.arrivalTime) : 0;
        process.remainingTime = 0;
    }
}

double Metrics::averageWaitingTime(const std::vector<Process>& processes) {
    if (processes.empty()) {
        return 0.0;
    }

    int total = 0;
    for (const Process& process : processes) {
        total += process.waitingTime;
    }
    return static_cast<double>(total) / processes.size();
}

double Metrics::averageTurnaroundTime(const std::vector<Process>& processes) {
    if (processes.empty()) {
        return 0.0;
    }

    int total = 0;
    for (const Process& process : processes) {
        total += process.turnaroundTime;
    }
    return static_cast<double>(total) / processes.size();
}

double Metrics::averageResponseTime(const std::vector<Process>& processes) {
    if (processes.empty()) {
        return 0.0;
    }

    int total = 0;
    for (const Process& process : processes) {
        total += process.responseTime;
    }
    return static_cast<double>(total) / processes.size();
}

int Metrics::totalSimulationTime(const std::vector<Process>& processes) {
    int maxCompletionTime = 0;
    for (const Process& process : processes) {
        if (process.completionTime > maxCompletionTime) {
            maxCompletionTime = process.completionTime;
        }
    }
    return maxCompletionTime;
}

double Metrics::cpuUtilization(const std::vector<Process>& processes, int totalTime) {
    if (processes.empty() || totalTime <= 0) {
        return 0.0;
    }

    int totalBurstTime = 0;
    for (const Process& process : processes) {
        totalBurstTime += process.burstTime;
    }

    return (static_cast<double>(totalBurstTime) / totalTime) * 100.0;
}

AlgorithmResult buildAlgorithmResult(const std::string& algorithmName,
    std::vector<Process> processes,
    const std::vector<GanttEntry>& gantt) {
    Metrics::finalizeProcesses(processes);

    AlgorithmResult result;
    result.algorithmName = algorithmName;
    result.processes = std::move(processes);
    result.gantt = gantt;
    result.averageWaitingTime = Metrics::averageWaitingTime(result.processes);
    result.averageTurnaroundTime = Metrics::averageTurnaroundTime(result.processes);
    result.averageResponseTime = Metrics::averageResponseTime(result.processes);
    result.totalSimulationTime = Metrics::totalSimulationTime(result.processes);
    result.cpuUtilization = Metrics::cpuUtilization(result.processes, result.totalSimulationTime);
    return result;
}
