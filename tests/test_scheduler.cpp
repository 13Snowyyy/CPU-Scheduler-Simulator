#include <cassert>
#include <cmath>
#include <vector>

#include "Scheduler.h"

int main() {
    std::vector<Process> processes = {
        Process(1, "P1", 0, 4, 2),
        Process(2, "P2", 1, 3, 1),
        Process(3, "P3", 2, 2, 3)
    };

    FCFS fcfs;
    auto fcfsResult = fcfs.run(processes);
    assert(fcfsResult.processes.size() == 3);
    assert(fcfsResult.processes[0].completionTime >= 0);

    SJF sjf;
    auto sjfResult = sjf.run(processes);
    assert(sjfResult.processes.size() == 3);

    PriorityScheduler priorityScheduler;
    auto priorityResult = priorityScheduler.run(processes);
    assert(priorityResult.processes.size() == 3);

    RoundRobin roundRobin;
    auto rrResult = roundRobin.run(processes, 2);
    assert(rrResult.processes.size() == 3);
    assert(rrResult.totalSimulationTime > 0);

    std::vector<Process> allAtZero = {
        Process(1, "P1", 0, 5, 1),
        Process(2, "P2", 0, 2, 2),
        Process(3, "P3", 0, 4, 3)
    };

    auto fcfsZero = FCFS{}.run(allAtZero);
    assert(fcfsZero.processes.size() == 3);
    assert(std::fabs(fcfsZero.averageWaitingTime - 4.0) < 0.01);

    return 0;
}
