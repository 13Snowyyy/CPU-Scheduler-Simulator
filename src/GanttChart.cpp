#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Scheduler.h"

void GanttChart::addIdle(std::vector<GanttEntry>& gantt, int start, int end) {
    if (end > start) {
        gantt.push_back({start, end, -1, true});
    }
}

std::string GanttChart::toText(const std::vector<GanttEntry>& gantt) {
    if (gantt.empty()) {
        return "No execution timeline available.";
    }

    std::ostringstream output;
    output << "\nGantt Chart\n";

    output << "  ";
    for (const GanttEntry& entry : gantt) {
        int duration = std::max(1, entry.endTime - entry.startTime);
        int blockSize = std::max(8, duration * 3 + 2);
        std::string label = entry.isIdle ? "IDLE" : "P" + std::to_string(entry.processId);
        output << std::setw(blockSize) << std::right << label;
    }
    output << "\n";

    output << "  ";
    for (const GanttEntry& entry : gantt) {
        int duration = std::max(1, entry.endTime - entry.startTime);
        int blockSize = std::max(8, duration * 3 + 2);
        std::string bar(blockSize - 1, entry.isIdle ? '-' : '=');
        output << "|" << bar;
    }
    output << "|\n";

    output << "  ";
    for (const GanttEntry& entry : gantt) {
        output << std::setw(6) << std::right << entry.startTime;
    }
    output << std::setw(6) << std::right << gantt.back().endTime << "\n";

    return output.str();
}

void GanttChart::print(const std::vector<GanttEntry>& gantt) {
    std::cout << toText(gantt) << std::endl;
}
