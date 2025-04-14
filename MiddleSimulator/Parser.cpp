// Parser.cpp

// Parser.cpp

#include "Parser.h"      // Include the corresponding header file first
#include <sstream>       // For std::stringstream
#include <string>        // For std::string, std::getline, std::stoi
#include <vector>        // For std::vector
#include <iostream>      // For std::cout, std::cerr (error output)
#include <stdexcept>     // For std::invalid_argument, std::out_of_range (exceptions for stoi)

// --- Implementation of the parseData method ---
// The 'Parser::' prefix indicates this function belongs to the Parser class
void Parser::parseData(const std::string& rawData) {
    // 1. Clear any previously parsed channel data from the member vector
    channels.clear();
    std::cout << "Starting parsing for data: \"" << rawData << "\"" << std::endl;

    // 2. Create a stringstream to easily process the input string
    std::stringstream ss(rawData);
    std::string channelSegment; // Variable to hold "ID,Name" parts

    // 3. Outer loop: Read segments separated by semicolons
    while (std::getline(ss, channelSegment, ';')) {
        // 4. Create another stringstream for the individual segment
        std::stringstream ssSegment(channelSegment);
        std::string part;           // Variable to hold "ID" or "Name" parts
        ChannelInfo currentChannel; // Temporary object to build channel info
        int partIndex = 0;          // Counter: 0 for ID, 1 for Name

        // 5. Inner loop: Read parts separated by commas
        while (std::getline(ssSegment, part, ',')) {
            if (partIndex == 0) { // First part should be the ID
                try {
                    // 6. Convert the ID part (string) to an integer
                    currentChannel.channelId = std::stoi(part);
                } catch (const std::invalid_argument& e) {
                    // Handle cases where 'part' is not a valid integer (e.g., "abc")
                    std::cerr << "Error parsing channel ID (invalid format): \"" << part << "\". Skipping segment: \"" << channelSegment << "\"" << std::endl;
                    currentChannel.channelId = -1; // Mark as invalid
                    break; // Stop processing this segment if ID is invalid
                } catch (const std::out_of_range& e) {
                    // Handle cases where 'part' is a number but too large for an int
                    std::cerr << "Error parsing channel ID (out of range): \"" << part << "\". Skipping segment: \"" << channelSegment << "\"" << std::endl;
                    currentChannel.channelId = -1; // Mark as invalid
                    break; // Stop processing this segment
                }
            } else if (partIndex == 1) { // Second part should be the Name
                // 7. Assign the name part directly
                currentChannel.channelName = part;
            }
            // We could add handling for more parts later (partIndex > 1)

            partIndex++; // Move to the next expected part index
        } // End of inner loop (parsing parts within a segment)

        // 8. Validation check before adding to the list:
        //    - Was the ID successfully parsed (not -1)?
        //    - Did we get at least two parts (ID and Name)?
        if (currentChannel.channelId != -1 && partIndex >= 2) {
            channels.push_back(currentChannel); // Add the valid channel to our member vector
        } else if (currentChannel.channelId != -1) {
             // ID was valid, but maybe name was missing? Log a warning.
             std::cerr << "Warning: Parsed valid ID (" << currentChannel.channelId
                       << ") but potentially incomplete data in segment: \""
                       << channelSegment << "\". Channel not added." << std::endl;
        }

    } // End of outer loop (processing segments)

    std::cout << "Parsing complete. Stored " << channels.size() << " valid channels." << std::endl;
}

// --- Implementation of getChannels (if definition wasn't in Parser.h) ---
std::vector<ChannelInfo> Parser::getChannels() {
    // Simply return the member variable containing the parsed channels
    return channels;
}

// --- Implementation of getProgramsForChannel (Placeholder) ---
// We haven't parsed program info yet, so this just returns an empty vector.
std::vector<ProgramInfo> Parser::getProgramsForChannel(int channelId) {
    std::cout << "Note: getProgramsForChannel(" << channelId << ") not implemented yet." << std::endl;
    // We might want to use the 'programs' member variable here later
    std::vector<ProgramInfo> emptyProgramList;
    return emptyProgramList;
}
