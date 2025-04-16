#ifndef CHANNELINFO_H
#define CHANNELINFO_H

#include <string> // Include necessary standard headers

// Simple structure to hold channel information
struct ChannelInfo {
    int channelId = 0;
    std::string channelName = "Default Channel";
    // Add other relevant members later (e.g., service ID, type)
};

#endif // CHANNELINFO_H