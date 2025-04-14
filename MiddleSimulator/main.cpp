#include <iostream> // For printing to console
#include <vector>   // If using vectors directly in main (optional here)
#include <string>   // If using strings directly in main

// Include your custom headers
#include "ChannelInfo.h"
#include "ProgramInfo.h"
#include "Parser.h"

int main() {
    std::cout << "--- Middleware Simulator Started ---" << std::endl;

    // Create a Parser instance
    Parser dataParser;

    // Simulate parsing some data (replace "dummy_data" later)
    std::cout << "Simulating data parsing..." << std::endl;
    dataParser.parseData("dummy_stream_data_goes_here"); // Placeholder call

    // Simulate retrieving parsed data (will be empty for now)
    std::vector<ChannelInfo> channels = dataParser.getChannels();
    std::cout << "Retrieved " << channels.size() << " channels (initially empty)." << std::endl;

    // You could add logic here later to interact with the parser/data

    std::cout << "--- Middleware Simulator Finished ---" << std::endl;

    std::cout << "--- Completed by Leong Shin Soon ---" << std::endl;
    return 0; // Indicate successful execution
}
