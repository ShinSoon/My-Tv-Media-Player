#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>          // Include map for storing programs
#include "ChannelInfo.h"
#include "ProgramInfo.h"

// Class responsible for parsing middleware data
class Parser {
public:
    // Constructor
    Parser() = default;

    // Parses raw input data string based on defined format (CH|..;PG|..)
    void parseData(const std::string& rawData);

    // Returns the vector of parsed channels
    std::vector<ChannelInfo> getChannels();

    // Returns a vector of programs for a specific channel ID
    std::vector<ProgramInfo> getProgramsForChannel(int channelId);

private:
    // Member variables to store parsed data
    std::vector<ChannelInfo> channels;
    std::map<int, std::vector<ProgramInfo>> programsByChannelId;
    // Key: Channel ID, Value: Vector of programs for that channel
};

#endif // PARSER_H