#ifndef PROGRAMINFO_H
#define PROGRAMINFO_H

#include <string> // Make sure <string> is included

// Simple structure to hold program (event) information
struct ProgramInfo {
    // int channelId = 0; // Optional: ID of the channel this program belongs to (redundant if using map key)
    int programId = 0;   // Unique ID for the program/event
    std::string programName = "Default Program";
    std::string description = "No description.";
    // Add other members later like start time, duration, etc.
};

#endif // PROGRAMINFO_H