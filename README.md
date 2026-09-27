# CPU Process Scheduler Simulator

## Project Overview
This project is a beginner-friendly CPU scheduling simulator written in C++. It demonstrates how Operating System scheduling algorithms work in practice and how common Data Structures and Algorithms concepts are used to solve a real-world simulation problem.

The simulator supports the following scheduling strategies:
- FCFS (First Come First Serve)
- SJF (Shortest Job First, non-preemptive)
- Priority Scheduling (non-preemptive)
- Round Robin (preemptive)

## Browser UI

The project also includes a light-theme browser dashboard in `web/index.html`. Open that file directly in a browser to edit a workload, run each scheduling policy, compare metrics, and inspect a proportional Gantt chart. The dashboard mirrors the simulator algorithms and requires no build step.

The program computes scheduling metrics dynamically from user input and generates a Gantt chart for each algorithm.

## Features
- Menu-driven console application
- Process input validation
- FCFS, SJF, Priority, and Round Robin simulation
- Dynamic metric calculation
- Gantt chart generation
- Algorithm comparison mode
- Beginner-friendly modular code structure

## Technologies Used
- C++17
- Standard Template Library (STL)
- CMake
- Console I/O

## DSA Concepts Used
- vector for storing process records
- queue for FCFS and Round Robin ready list
- priority_queue for priority scheduling
- sorting and custom comparators for ordering jobs
- simulation logic for event-driven scheduling

## OS Concepts Used
- CPU scheduling
- Arrival time and burst time
- Waiting time and turnaround time
- Response time
- Preemptive vs non-preemptive scheduling
- Idle CPU time handling

## Scheduling Algorithms

### 1. FCFS
Idea: The process that arrives first gets the CPU first.
Data structure: queue
Steps:
1. Sort processes by arrival time.
2. Execute processes in that order.
3. Insert idle time when the CPU is waiting for new arrivals.
Time complexity: O(n log n) due to sorting.

### 2. SJF
Idea: Choose the process with the shortest burst time among the arrived processes.
Data structure: vector + sorting/custom selection
Steps:
1. Keep only processes that have already arrived.
2. Select the smallest burst time.
3. Resolve ties using arrival time and process ID.
Time complexity: O(n^2) in a simple implementation, or O(n log n) with a better priority structure.

### 3. Priority Scheduling
Idea: Run the highest-priority available process first.
Data structure: priority_queue
Important rule: smaller priority number = higher priority.
Steps:
1. Add arrived processes into a priority queue.
2. Pop the process with the smallest priority value.
3. Handle idle time when no process is ready.
Time complexity: O(n log n)

### 4. Round Robin
Idea: Each process gets CPU time up to the quantum, then moves to the back of the ready queue.
Data structure: queue
Steps:
1. Enqueue all arrived processes.
2. Run each process for min(quantum, remaining burst).
3. If unfinished, push it back to the queue.
4. Add newly arrived processes while the simulation continues.
Time complexity: O(n * q) in simulation form, or O(n * number_of_cycles)

## Scheduling Metrics
- Completion Time (CT): when the process finishes
- Turnaround Time (TAT): CT - Arrival Time
- Waiting Time (WT): TAT - Burst Time
- Response Time (RT): First Start Time - Arrival Time
- Average Waiting Time = total waiting time / number of processes
- Average Turnaround Time = total turnaround time / number of processes
- Average Response Time = total response time / number of processes
- CPU Utilization = total burst time / total simulation time * 100

## Sample Input / Output
Example process list:

P1 -> AT=0, BT=5, Priority=2
P2 -> AT=1, BT=3, Priority=1
P3 -> AT=2, BT=4, Priority=3

The program will generate a Gantt chart such as:

| P1 | P2 | P3 | P1 |
0 2 4 6 8

## Gantt Chart Example
Each algorithm produces a text-based Gantt chart showing execution timeline and idle periods.

## Project Structure

CPU-Scheduler-Simulator/
├── src/
│   ├── main.cpp
│   ├── Process.h
│   ├── Scheduler.h
│   ├── FCFS.cpp
│   ├── SJF.cpp
│   ├── Priority.cpp
│   ├── RoundRobin.cpp
│   ├── Metrics.cpp
│   └── GanttChart.cpp
│
├── tests/
│   └── test_scheduler.cpp
│
├── README.md
│
├── CMakeLists.txt
└── build/

## How to Compile and Run
1. Open a terminal in the project directory.
2. Run:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

3. Run the program:

```bash
./cpu_scheduler_simulator
```

4. To run tests:

```bash
ctest --output-on-failure
```

## Test Cases
The project should be tested with at least the following cases:

1. All processes arriving at time 0
2. Different arrival times
3. CPU idle time
4. Round Robin with multiple rotations
5. Equal burst times
6. Equal priorities

Example expected behavior:
- FCFS sorts by arrival time.
- SJF picks the smallest burst among arrived processes.
- Priority scheduling uses the smallest priority number as highest priority.
- Round Robin rotates jobs until each finishes based on quantum.

## Future Improvements
- Add file-based process import
- Add a graphical visualization of the Gantt chart
- Support aging in priority scheduling
- Add multi-level feedback queue scheduling
- Add more advanced statistical comparison plots

## What I Learned
- Queues are used to manage ready processes in FCFS and Round Robin.
- Priority queues help select the best process by priority.
- Sorting is necessary for FCFS and SJF scheduling decisions.
- Process scheduling is a practical example of algorithm choice under real constraints.
- Preemptive scheduling differs from non-preemptive scheduling in how often a running process can be interrupted.
- Scheduling metrics help compare fairness and efficiency.
- The same input can produce different results depending on the algorithm used.

---

## Beginner Notes
This simulator is intentionally simple and structured so that a student can explain each algorithm clearly:
- FCFS uses arrival order.
- SJF chooses the shortest remaining job.
- Priority scheduling chooses the smallest priority value.
- Round Robin rotates among jobs with a fixed quantum.

The code is designed to be readable, modular, and easy to extend.
