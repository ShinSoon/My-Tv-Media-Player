#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <vector>
#include "ChannelInfo.h"
#include "ProgramInfo.h"

// Class responsible for parsing middleware data
class Parser {
public:
    // Constructor (optional for now)
    Parser() = default;

    // --- Declarations Only ---
    // The implementation is in Parser.cpp

    // Method to parse raw data
    void parseData(const std::string& rawData); // <--- REMOVED body, added ;

    // Method to get parsed channel info
    std::vector<ChannelInfo> getChannels();     // <--- REMOVED body, added ;

    // Method to get parsed program info (maybe per channel)
    std::vector<ProgramInfo> getProgramsForChannel(int channelId); // <--- REMOVED body, added ;


private:
    // Member variables to store parsed data
    std::vector<ChannelInfo> channels;
    std::vector<ProgramInfo> programs; // Still unused in parsing logic
};

#endif // PARSER_H_INCLUDED
