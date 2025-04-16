#include <iostream>
#include <vector>
#include <string>
#include <map> // Not strictly needed here, but Parser uses it

#include "ChannelInfo.h"
#include "ProgramInfo.h"
#include "Parser.h"

int main() {
    std::cout << "--- Middleware Simulator Started ---" << std::endl << std::endl;

    // Define sample input data using the new format
    std::string simulatedData = "CH|1|Channel One;PG|1|101|News|Current events;PG|1|102|Weather|Forecast;CH|2|Channel Two;PG|2|201|Movie|Action film;CH|3|Empty Channel;PG|99|901|Orphan Program|Belongs to no listed channel;CH|invalid|Bad Channel;PG|1|invalid_pgm|Bad Program|Desc";

    // Create a Parser instance
    Parser dataParser;

    // Call parseData with the simulated data
    std::cout << "Calling parser..." << std::endl;
    dataParser.parseData(simulatedData);
    std::cout << std::endl;

    // Retrieve and print the list of channels
    std::cout << "Retrieving parsed channels..." << std::endl;
    std::vector<ChannelInfo> parsedChannels = dataParser.getChannels();

    if (parsedChannels.empty()) {
        std::cout << "No valid channels were parsed." << std::endl;
    }
    else {
        std::cout << "Parsed Channel List:" << std::endl;
        std::cout << "--------------------" << std::endl;
        for (const ChannelInfo& channel : parsedChannels) {
            std::cout << "ID: " << channel.channelId << ", Name: \"" << channel.channelName << "\"" << std::endl;
        }
        std::cout << "--------------------" << std::endl << std::endl;

        // Retrieve and print programs for each parsed channel
        std::cout << "Retrieving program info for each channel..." << std::endl;
        for (const ChannelInfo& channel : parsedChannels) {
            std::cout << "\n--- Programs for Channel " << channel.channelId << " (" << channel.channelName << ") ---" << std::endl;
            std::vector<ProgramInfo> programs = dataParser.getProgramsForChannel(channel.channelId);

            if (programs.empty()) {
                std::cout << "  No programs found for this channel." << std::endl;
            }
            else {
                for (const ProgramInfo& program : programs) {
                    std::cout << "  Prog ID: " << program.programId
                        << ", Name: \"" << program.programName << "\""
                        << ", Desc: \"" << program.description << "\"" << std::endl;
                }
            }
        }
        std::cout << "-----------------------------------------" << std::endl;
    }

    std::cout << std::endl << "--- Middleware Simulator Finished ---" << std::endl;
    return 0;
}