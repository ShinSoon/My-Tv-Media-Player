# my-tv-media-player
Okay, here is a complete and comprehensive README.md file for the project.

# Middleware Channel/Program Parser

## Overview

This project is a simple C++ application demonstrating how to parse a specific text-based data format representing television channels and their associated programs (similar to data found in an Electronic Program Guide - EPG). It simulates a basic component often found in middleware systems for digital TV or streaming platforms.

The parser takes a raw string containing channel and program information, processes it according to a defined format, and stores the extracted data into organized C++ data structures (`std::vector` for channels and `std::map` for programs grouped by channel).

## Features

*   Parses a custom semicolon-separated and pipe-delimited text format.
*   Extracts Channel information (ID, Name).
*   Extracts Program information (Channel ID, Program ID, Name, Description).
*   Stores parsed channels in a `std::vector<ChannelInfo>`.
*   Stores parsed programs efficiently grouped by channel ID in a `std::map<int, std::vector<ProgramInfo>>`.
*   Provides simple methods to retrieve the parsed data.
*   Includes basic error handling for malformed numerical IDs and incomplete records.
*   Written in standard C++ (requires C++11 or later).
*   No external library dependencies beyond the C++ Standard Library.

## Project Structure


.
├── ChannelInfo.h # Defines the structure for holding channel data
├── ProgramInfo.h # Defines the structure for holding program data
├── Parser.h # Declares the Parser class interface
├── Parser.cpp # Implements the Parser class logic
├── main.cpp # Example usage and demonstration driver
└── README.md # This file

*   **`ChannelInfo.h`**: Defines the `ChannelInfo` struct.
*   **`ProgramInfo.h`**: Defines the `ProgramInfo` struct.
*   **`Parser.h`**: Header file for the `Parser` class, defining its public methods and private members.
*   **`Parser.cpp`**: Implementation file for the `Parser` class, containing the parsing logic.
*   **`main.cpp`**: A simple executable that demonstrates how to use the `Parser` class with sample data.

## Input Data Format

The parser expects the input data string to follow this format:

*   Records are separated by semicolons (`;`).
*   Each record represents either a Channel (`CH`) or a Program (`PG`).
*   Fields within a record are separated by pipes (`|`).
*   Whitespace around delimiters is generally ignored by `getline`, but field content is preserved.

**Channel Record (`CH`):**
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END

CH|<ChannelID>|<ChannelName>

*   `CH`: Record type identifier.
*   `<ChannelID>`: An integer representing the unique channel ID.
*   `<ChannelName>`: A string representing the channel's display name.

**Program Record (`PG`):**
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END

PG|<ChannelID>|<ProgramID>|<ProgramName>|<ProgramDescription>

*   `PG`: Record type identifier.
*   `<ChannelID>`: An integer identifying the channel this program belongs to.
*   `<ProgramID>`: An integer representing the unique ID for this program/event.
*   `<ProgramName>`: A string representing the program's title.
*   `<ProgramDescription>`: A string containing the program's description.

**Example Input String:**
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END

CH|1|Channel One;PG|1|101|News|Current events;PG|1|102|Weather|Forecast;CH|2|Channel Two;PG|2|201|Movie|Action film;CH|3|Empty Channel;PG|99|901|Orphan Program|Belongs to no listed channel;CH|invalid|Bad Channel;PG|1|invalid_pgm|Bad Program|Desc

## Building the Project

You can compile the project using a C++ compiler that supports C++11 or later (like g++ or clang++).

**Using g++:**

Navigate to the project directory in your terminal and run:

```bash
g++ main.cpp Parser.cpp -o middleware_parser -std=c++11 -Wall -Wextra -pedantic
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END

main.cpp Parser.cpp: Specifies the source files to compile.

-o middleware_parser: Specifies the name of the output executable file.

-std=c++11: Ensures C++11 standard compatibility (required for default constructor, stoi, etc.).

-Wall -Wextra -pedantic: Recommended flags to enable compiler warnings for better code quality.

Running the Example

After successful compilation, run the executable from your terminal:

./middleware_parser
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
Bash
IGNORE_WHEN_COPYING_END

This will execute the code in main.cpp, which:

Defines the sample input data string.

Creates a Parser instance.

Calls parseData() to process the string.

Retrieves and prints the list of parsed channels.

Retrieves and prints the programs associated with each parsed channel.

Prints warning messages to standard error (stderr) for any parsing errors encountered (e.g., invalid IDs, incomplete records).

Expected Output (based on the sample data):

--- Middleware Simulator Started ---

Calling parser...
Starting parsing (V2) for data: "CH|1|Channel One;PG|1|101|News|Current events;PG|1|102|Weather|Forecast;CH|2|Channel Two;PG|2|201|Movie|Action film;CH|3|Empty Channel;PG|99|901|Orphan Program|Belongs to no listed channel;CH|invalid|Bad Channel;PG|1|invalid_pgm|Bad Program|Desc"
Error parsing CH ID "invalid": std::invalid_argument: stoi: no conversion. Skipping CH record: "CH|invalid|Bad Channel"
Error parsing PG IDs (CH:"1", PG:"invalid_pgm"): std::invalid_argument: stoi: no conversion. Skipping PG record: "PG|1|invalid_pgm|Bad Program|Desc"
Parsing complete. Stored 3 channels and program entries for 3 channels.


Retrieving parsed channels...
Parsed Channel List:
--------------------
ID: 1, Name: "Channel One"
ID: 2, Name: "Channel Two"
ID: 3, Name: "Empty Channel"
--------------------

Retrieving program info for each channel...

--- Programs for Channel 1 (Channel One) ---
  Prog ID: 101, Name: "News", Desc: "Current events"
  Prog ID: 102, Name: "Weather", Desc: "Forecast"

--- Programs for Channel 2 (Channel Two) ---
  Prog ID: 201, Name: "Movie", Desc: "Action film"

--- Programs for Channel 3 (Empty Channel) ---
  No programs found for this channel.
-----------------------------------------

--- Middleware Simulator Finished ---
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END

(Note: Error messages for invalid records go to stderr, while normal output goes to stdout).

How It Works

Parsing (Parser::parseData):

The input string is treated as a stream using std::stringstream.

The stream is read segment by segment using std::getline with ';' as the delimiter.

Each segment (record) is processed by another std::stringstream.

The record type (CH or PG) is read using std::getline with '|' as the delimiter.

Based on the type, the remaining fields are read using std::getline with '|'.

String representations of IDs are converted to integers using std::stoi. Exceptions during conversion are caught.

Valid ChannelInfo objects are added to the channels vector.

Valid ProgramInfo objects are added to the std::vector associated with their channelId key within the programsByChannelId map. The map allows efficient lookup of programs belonging to a specific channel.

Data Retrieval:

getChannels(): Returns a copy of the channels vector.

getProgramsForChannel(int channelId): Looks up the channelId in the programsByChannelId map. If found, it returns a copy of the associated program vector; otherwise, it returns an empty vector.

Usage (API)

To use the parser in your own code:

Include the necessary headers:

#include "Parser.h"
#include "ChannelInfo.h" // Often included indirectly via Parser.h
#include "ProgramInfo.h" // Often included indirectly via Parser.h
#include <string>
#include <vector>
#include <iostream> // For printing results
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
C++
IGNORE_WHEN_COPYING_END

Create an instance of the Parser:

Parser myParser;
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
C++
IGNORE_WHEN_COPYING_END

Provide the raw data string and call parseData:

std::string rawEpgData = "CH|10|News Channel;PG|10|500|Evening News|..."; // Your data
myParser.parseData(rawEpgData);
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
C++
IGNORE_WHEN_COPYING_END

Retrieve the parsed data:

// Get all channels
std::vector<ChannelInfo> allChannels = myParser.getChannels();
for (const auto& channel : allChannels) {
    std::cout << "Channel ID: " << channel.channelId << ", Name: " << channel.channelName << std::endl;
}

// Get programs for a specific channel (e.g., channel ID 10)
int targetChannelId = 10;
std::vector<ProgramInfo> channel10Programs = myParser.getProgramsForChannel(targetChannelId);
if (channel10Programs.empty()) {
    std::cout << "No programs found for channel " << targetChannelId << std::endl;
} else {
    std::cout << "Programs for channel " << targetChannelId << ":" << std::endl;
    for (const auto& program : channel10Programs) {
        std::cout << "  - Program ID: " << program.programId << ", Name: " << program.programName << std::endl;
    }
}
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
C++
IGNORE_WHEN_COPYING_END
Error Handling

Invalid Number Format: If a field expected to be an integer (like ChannelID or ProgramID) cannot be converted using std::stoi (e.g., "abc"), an error message is printed to stderr, and the entire record (CH or PG) is skipped.

Incomplete Records: If a record does not contain the expected number of pipe-separated fields, a warning is printed to stderr, and the record is skipped.

Unknown Record Type: If a record starts with something other than "CH" or "PG", a warning is printed to stderr, and the record is skipped.

The parser attempts to process as much valid data as possible, skipping only the problematic records.

Future Enhancements

Add support for program start times and durations in ProgramInfo.

Implement more robust error reporting (e.g., line numbers, specific error types).

Support different or more complex input formats.

Add unit tests for the Parser class.

Use a more advanced build system like CMake.

Optimize parsing for very large input data streams.

License

This project is provided as-is. You can consider it under the MIT License or use it freely for educational purposes.

(Optional: Include MIT License text here if desired)
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END