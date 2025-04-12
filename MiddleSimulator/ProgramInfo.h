#ifndef PROGRAMINFO_H
#define PROGRAMINFO_H

#include <string>

// Simple structure to hold program (event) information
struct ProgramInfo {
    int programId = 0; // Or maybe Event ID
    std::string programName = "Default Program";
    std::string description = "No description.";
    // Add other relevant members later (e.g., start time, duration)
};

#endif // PROGRAMINFO_H
