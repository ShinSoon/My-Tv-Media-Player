// Parser.cpp

#include "Parser.h"      // Include the corresponding header file first
#include <sstream>       // For std::stringstream
#include <string>        // For std::string, std::getline, std::stoi
#include <vector>        // For std::vector
#include <map>           // For std::map
#include <iostream>      // For std::cout, std::cerr (error output)
#include <stdexcept>     // For std::invalid_argument, std::out_of_range (exceptions for stoi)

// --- Implementation of the parseData method ---
void Parser::parseData(const std::string& rawData) {
    // Clear data from previous runs
    channels.clear();
    programsByChannelId.clear();
    std::cout << "Starting parsing (V2) for data: \"" << rawData << "\"" << std::endl;

    std::stringstream ss(rawData);
    std::string recordSegment; // Holds one complete record (CH|... or PG|...)

    // Outer loop: Read records separated by semicolons
    while (std::getline(ss, recordSegment, ';')) {
        if (recordSegment.empty()) continue; // Skip empty segments

        std::stringstream ssRecord(recordSegment);
        std::string recordType;
        std::string part; // Reusable part string

        // Read the record type prefix (CH or PG)
        if (!std::getline(ssRecord, recordType, '|')) {
            std::cerr << "Warning: Malformed record segment (missing type): \"" << recordSegment << "\"" << std::endl;
            continue; // Skip this segment
        }

        // --- Process Channel Records ---
        if (recordType == "CH") {
            std::string idStr, nameStr;
            ChannelInfo currentChannel;
            int partsRead = 0;

            // Read remaining parts separated by pipe '|'
            if (std::getline(ssRecord, idStr, '|')) partsRead++;
            if (std::getline(ssRecord, nameStr, '|')) partsRead++;
            // Add more std::getline if CH format had more parts

            if (partsRead == 2) { // Check if we got the expected number of parts
                try {
                    currentChannel.channelId = std::stoi(idStr);
                    currentChannel.channelName = nameStr;
                    channels.push_back(currentChannel); // Add valid channel
                }
                catch (const std::exception& e) { // Catch stoi errors
                    std::cerr << "Error parsing CH ID \"" << idStr << "\": " << e.what() << ". Skipping CH record: \"" << recordSegment << "\"" << std::endl;
                }
            }
            else {
                std::cerr << "Warning: Incomplete CH record (expected 2 parts, got " << partsRead << "): \"" << recordSegment << "\". Channel not added." << std::endl;
            }

            // --- Process Program Records ---
        }
        else if (recordType == "PG") {
            std::string channelIdStr, programIdStr, nameStr, descStr;
            ProgramInfo currentProgram;
            int parsedChannelId = -1;
            int partsRead = 0;

            // Read remaining parts separated by pipe '|'
            if (std::getline(ssRecord, channelIdStr, '|')) partsRead++;
            if (std::getline(ssRecord, programIdStr, '|')) partsRead++;
            if (std::getline(ssRecord, nameStr, '|')) partsRead++;
            if (std::getline(ssRecord, descStr, '|')) partsRead++;
            // Add more std::getline if PG format had more parts

            if (partsRead == 4) { // Check if we got the expected number of parts
                try {
                    parsedChannelId = std::stoi(channelIdStr); // ID of channel this program belongs to
                    currentProgram.programId = std::stoi(programIdStr); // ID of the program itself
                    currentProgram.programName = nameStr;
                    currentProgram.description = descStr;

                    // Store the program in the map, keyed by its channel ID
                    // The [] operator creates an empty vector if the key doesn't exist
                    programsByChannelId[parsedChannelId].push_back(currentProgram);

                }
                catch (const std::exception& e) { // Catch stoi errors
                    std::cerr << "Error parsing PG IDs (CH:\"" << channelIdStr << "\", PG:\"" << programIdStr << "\"): " << e.what() << ". Skipping PG record: \"" << recordSegment << "\"" << std::endl;
                }
            }
            else {
                std::cerr << "Warning: Incomplete PG record (expected 4 parts, got " << partsRead << "): \"" << recordSegment << "\". Program not added." << std::endl;
            }

            // --- Handle Unknown Record Types ---
        }
        else {
            std::cerr << "Warning: Unknown record type \"" << recordType << "\" found. Skipping record: \"" << recordSegment << "\"" << std::endl;
        }
    } // End of outer loop (processing records)

    std::cout << "Parsing complete. Stored " << channels.size() << " channels and program entries for " << programsByChannelId.size() << " channels." << std::endl;
}

// --- Implementation of getChannels ---
std::vector<ChannelInfo> Parser::getChannels() {
    return channels;
}

// --- Implementation of getProgramsForChannel ---
std::vector<ProgramInfo> Parser::getProgramsForChannel(int channelId) {
    // Use 'find' to efficiently check if the channelId exists as a key in the map
    auto it = programsByChannelId.find(channelId);

    if (it != programsByChannelId.end()) {
        // If the iterator 'it' is not pointing to the 'end' (meaning the key was found)
        // return the vector of ProgramInfo objects associated with that key.
        // 'it->second' accesses the value (the vector) part of the map element found.
        return it->second;
    }
    else {
        // If 'find' returns 'end()', the key (channelId) was not found in the map.
        // Return an empty vector using list initialization '{}'.
        return {};
    }
}