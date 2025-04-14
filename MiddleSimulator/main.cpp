#include <iostream> // For printing to console
#include <vector>   // For std::vector
#include <string>   // For std::string

// Include your custom headers
#include "ChannelInfo.h"
#include "ProgramInfo.h" // Not used yet, but good to keep
#include "Parser.h"

int main() {
    std::cout << "--- Middleware Simulator Started ---" << std::endl << std::endl;

    // 1. Define your sample input data string
    //    Includes valid, semi-valid, and invalid entries for testing
    std::string simulatedData = "1,Channel One;2,Channel Two HD;3,Another Channel;99,Test Only;invalid,Bad Channel ID;100;101,Final Channel";

    // 2. Create a Parser instance
    Parser dataParser;

    // 3. Call parseData, passing the simulated data
    std::cout << "Calling parser..." << std::endl;
    dataParser.parseData(simulatedData);
    std::cout << std::endl; // Add a blank line for readability

    // 4. Call getChannels() to retrieve the results
    std::cout << "Retrieving parsed channels..." << std::endl;
    std::vector<ChannelInfo> parsedChannels = dataParser.getChannels();

    // 5. Check if any channels were found and print them
    if (parsedChannels.empty()) {
        std::cout << "No valid channels were parsed." << std::endl;
    } else {
        std::cout << "Parsed Channel List:" << std::endl;
        std::cout << "--------------------" << std::endl;
        // Loop through the vector of ChannelInfo objects
        for (const ChannelInfo& channel : parsedChannels) {
            // Print the ID and Name for each channel
            std::cout << "ID: " << channel.channelId << ", Name: \"" << channel.channelName << "\"" << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }

    // Example placeholder call for ProgramInfo (not implemented yet)
    // std::vector<ProgramInfo> programs = dataParser.getProgramsForChannel(1);

    std::cout << std::endl << "--- Middleware Simulator Finished ---" << std::endl;
    return 0; // Indicate successful execution
}
