#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <vector>
#include "ChannelInfo.h"
#include "ProgramInfo.h"

// Class responsible for parsing middleware data (placeholder)
class Parser {
public:
    // Constructor (optional for now)
    Parser() = default;

    // Placeholder method to simulate parsing raw data
    // In reality, might take a byte buffer, file stream, etc.
    void parseData(const std::string& rawData) {
        // Implementation will go in Parser.cpp later
        // For now, maybe just log that parsing happened.
        // std::cout << "Parsing data: " << rawData << std::endl; // Requires <iostream>
    }

    // Placeholder method to get parsed channel info
    std::vector<ChannelInfo> getChannels() {
        // Implementation later
        return channels; // Return the member variable
    }

    // Placeholder method to get parsed program info (maybe per channel)
    std::vector<ProgramInfo> getProgramsForChannel(int channelId) {
        // Implementation later
        return programs; // Return the member variable
    }

private:
    // Placeholder member variables to store parsed data
    std::vector<ChannelInfo> channels;
    std::vector<ProgramInfo> programs;
};



#endif // PARSER_H_INCLUDED
