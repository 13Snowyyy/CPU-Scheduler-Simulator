#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Scheduler.h"

namespace {

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt, int minimum) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minimum) {
                return value;
            }
            std::cout << "Value must be >= " << minimum << ".\n";
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
        clearInput();
    }
}

std::vector<Process> inputProcesses(int processCount) {
    std::vector<Process> processes;
    processes.reserve(processCount);

    for (int i = 1; i <= processCount; ++i) {
        std::cout << "\nProcess " << i << "\n";
        int arrivalTime = readInt("Arrival time: ", 0);
        int burstTime = readInt("Burst time: ", 1);
        int priority = readInt("Priority (smaller is higher priority): ", 0);

        processes.push_back(Process(i, "P" + std::to_string(i), arrivalTime, burstTime, priority));
    }

    return processes;
}

void printResultTable(const AlgorithmResult& result) {
    std::cout << "\n=== " << result.algorithmName << " ===\n";
    std::cout << "+--------+-----+-----+--------+-----+-----+-----+-----+\n";
    std::cout << "| PID    | AT  | BT  | PRIOR  | CT  | TAT | WT  | RT  |\n";
    std::cout << "+--------+-----+-----+--------+-----+-----+-----+-----+\n";

    for (const Process& process : result.processes) {
        std::cout << "| " << std::left << std::setw(6) << process.id
                  << " | " << std::setw(3) << process.arrivalTime
                  << " | " << std::setw(3) << process.burstTime
                  << " | " << std::setw(6) << process.priority
                  << " | " << std::setw(3) << process.completionTime
                  << " | " << std::setw(3) << process.turnaroundTime
                  << " | " << std::setw(3) << process.waitingTime
                  << " | " << std::setw(3) << process.responseTime
                  << " |\n";
    }

    std::cout << "+--------+-----+-----+--------+-----+-----+-----+-----+\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << result.averageWaitingTime << "\n";
    std::cout << "Average Turnaround Time: " << result.averageTurnaroundTime << "\n";
    std::cout << "Average Response Time: " << result.averageResponseTime << "\n";
    std::cout << "CPU Utilization: " << result.cpuUtilization << "%\n";
    std::cout << "Total Simulation Time: " << result.totalSimulationTime << "\n\n";

    std::cout << GanttChart::toText(result.gantt) << "\n";
}

void printComparisonTable(const std::vector<AlgorithmResult>& results) {
    std::cout << "\n=== Algorithm Comparison ===\n";
    std::cout << std::left
              << std::setw(18) << "Algorithm"
              << std::setw(12) << "Avg WT"
              << std::setw(12) << "Avg TAT"
              << std::setw(12) << "Avg RT"
              << "CPU Util%\n";

    std::cout << std::fixed << std::setprecision(2);
    for (const AlgorithmResult& result : results) {
        std::cout << std::left
                  << std::setw(18) << result.algorithmName
                  << std::setw(12) << result.averageWaitingTime
                  << std::setw(12) << result.averageTurnaroundTime
                  << std::setw(12) << result.averageResponseTime
                  << result.cpuUtilization << "\n";
    }

    std::cout << "\nNote: No algorithm is universally best; the best choice depends on the workload.\n";
}

void runAllAlgorithms(const std::vector<Process>& processes, int quantum) {
    std::vector<AlgorithmResult> results;

    FCFS fcfs;
    results.push_back(fcfs.run(processes));

    SJF sjf;
    results.push_back(sjf.run(processes));

    PriorityScheduler priorityScheduler;
    results.push_back(priorityScheduler.run(processes));

    RoundRobin roundRobin;
    results.push_back(roundRobin.run(processes, quantum));

    for (const AlgorithmResult& result : results) {
        printResultTable(result);
    }

    printComparisonTable(results);
}

}  // namespace

int main() {
    std::cout << "\n# ========================================\n";
    std::cout << "CPU PROCESS SCHEDULER\n";
    std::cout << "# ========================================\n";

    int processCount = readInt("Enter number of processes: ", 1);
    std::vector<Process> processes = inputProcesses(processCount);
    int rrQuantum = readInt("Enter Round Robin quantum: ", 1);

    while (true) {
        std::cout << "\n# ========================================\n";
        std::cout << "Choose scheduling algorithm:\n";
        std::cout << "1. FCFS\n";
        std::cout << "2. SJF\n";
        std::cout << "3. Priority Scheduling\n";
        std::cout << "4. Round Robin\n";
        std::cout << "5. All Algorithms\n";
        std::cout << "6. Exit\n";
        std::cout << "# ========================================\n";

        int choice = readInt("Select an option: ", 1);

        if (choice == 6) {
            std::cout << "Exiting scheduler.\n";
            break;
        }

        switch (choice) {
            case 1: {
                FCFS fcfs;
                printResultTable(fcfs.run(processes));
                break;
            }
            case 2: {
                SJF sjf;
                printResultTable(sjf.run(processes));
                break;
            }
            case 3: {
                PriorityScheduler priorityScheduler;
                printResultTable(priorityScheduler.run(processes));
                break;
            }
            case 4: {
                RoundRobin roundRobin;
                printResultTable(roundRobin.run(processes, rrQuantum));
                break;
            }
            case 5: {
                runAllAlgorithms(processes, rrQuantum);
                break;
            }
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }

    return 0;
}
