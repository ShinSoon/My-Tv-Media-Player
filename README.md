# my-tv-media-player

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


概述
本项目是一个简单的 C++ 应用程序，演示了如何解析一种特定的基于文本的数据格式，该格式用于表示电视频道及其关联的节目信息（类似于电子节目指南 EPG 中的数据）。它模拟了数字电视或流媒体平台中间件系统中常见的一个基本组件。
该解析器接收包含频道和节目信息的原始字符串，按照预定义的格式进行处理，并将提取的数据存储到组织化的 C++ 数据结构中（使用 std::vector 存储频道列表，使用 std::map 存储按频道分组的节目列表）。
功能特性
解析自定义的以分号分隔记录、以管道符分隔字段的文本格式。
提取频道信息（ID、名称）。
提取节目信息（频道 ID、节目 ID、名称、描述）。
将解析后的频道存储在 std::vector<ChannelInfo> 中。
将解析后的节目按频道 ID 高效地分组存储在 std::map<int, std::vector<ProgramInfo>> 中。
提供简单的方法来获取解析后的数据。
包含对格式错误的数字 ID 和不完整记录的基本错误处理。
使用标准 C++ 编写（需要 C++11 或更高版本）。
除 C++ 标准库外，无外部库依赖。
项目结构
.
├── ChannelInfo.h       # 定义用于存储频道数据的结构
├── ProgramInfo.h       # 定义用于存储节目数据的结构
├── Parser.h            # 声明 Parser 类的接口
├── Parser.cpp          # 实现 Parser 类的逻辑
├── main.cpp            # 示例用法和演示驱动程序
└── README.md           # 本文件
Use code with caution.
ChannelInfo.h: 定义 ChannelInfo 结构体。
ProgramInfo.h: 定义 ProgramInfo 结构体。
Parser.h: Parser 类的头文件，定义其公共方法和私有成员。
Parser.cpp: Parser 类的实现文件，包含解析逻辑。
main.cpp: 一个简单的可执行文件，演示如何使用 Parser 类和示例数据。
输入数据格式
解析器期望输入数据字符串遵循以下格式：
记录（Records）之间使用分号（;）分隔。
每条记录代表一个频道（CH）或一个节目（PG）。
记录内部的字段（Fields）之间使用管道符（|）分隔。
getline 通常会忽略分隔符周围的空白，但字段内容会被保留。
频道记录 (CH):
CH|<频道ID>|<频道名称>
Use code with caution.
CH: 记录类型标识符。
<频道ID>: 代表唯一频道 ID 的整数。
<频道名称>: 代表频道显示名称的字符串。
节目记录 (PG):
PG|<频道ID>|<节目ID>|<节目名称>|<节目描述>
Use code with caution.
PG: 记录类型标识符。
<频道ID>: 标识该节目所属频道的整数 ID。
<节目ID>: 代表该节目/事件的唯一 ID 的整数。
<节目名称>: 代表节目名称的字符串。
<节目描述>: 包含节目描述的字符串。
示例输入字符串:
CH|1|Channel One;PG|1|101|News|Current events;PG|1|102|Weather|Forecast;CH|2|Channel Two;PG|2|201|Movie|Action film;CH|3|Empty Channel;PG|99|901|Orphan Program|Belongs to no listed channel;CH|invalid|Bad Channel;PG|1|invalid_pgm|Bad Program|Desc
Use code with caution.
构建项目
你可以使用支持 C++11 或更高标准的 C++ 编译器（如 g++ 或 clang++）来编译项目。
使用 g++:
在终端中导航到项目目录，并运行：
g++ main.cpp Parser.cpp -o middleware_parser -std=c++11 -Wall -Wextra -pedantic
Use code with caution.
Bash
main.cpp Parser.cpp: 指定要编译的源文件。
-o middleware_parser: 指定输出的可执行文件的名称。
-std=c++11: 确保 C++11 标准兼容性（default 构造函数、stoi 等需要）。
-Wall -Wextra -pedantic: 推荐使用的标志，用于启用编译器警告以提高代码质量。
运行示例
编译成功后，在终端运行可执行文件：
./middleware_parser
Use code with caution.
Bash
这将执行 main.cpp 中的代码，该代码会：
定义示例输入数据字符串。
创建一个 Parser 实例。
调用 parseData() 处理字符串。
获取并打印已解析的频道列表。
获取并打印与每个已解析频道关联的节目列表。
将解析过程中遇到的任何错误（例如，无效 ID、记录不完整）的警告信息打印到标准错误流（stderr）。
预期输出 (基于示例数据):
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
Use code with caution.
(注意：无效记录的错误消息会输出到 stderr，而正常输出会到 stdout)。
工作原理
解析 (Parser::parseData):
使用 std::stringstream 将输入字符串视为流。
使用 std::getline 以 ';' 作为分隔符，逐段读取流。
每个段（记录）由另一个 std::stringstream 处理。
使用 std::getline 以 '|' 作为分隔符，读取记录类型（CH 或 PG）。
根据类型，使用 std::getline 以 '|' 分隔符读取剩余字段。
使用 std::stoi 将 ID 的字符串表示形式转换为整数。转换过程中的异常会被捕获。
有效的 ChannelInfo 对象被添加到 channels 向量中。
有效的 ProgramInfo 对象被添加到 programsByChannelId 映射中，与其 channelId 键相关联的 std::vector 中。该映射允许高效查找属于特定频道的节目。
数据检索:
getChannels(): 返回 channels 向量的副本。
getProgramsForChannel(int channelId): 在 programsByChannelId 映射中查找 channelId。如果找到，则返回关联的节目向量的副本；否则，返回一个空向量。
使用方法 (API)
要在你自己的代码中使用此解析器：
包含必要的头文件：
#include "Parser.h"
#include "ChannelInfo.h" // 通常通过 Parser.h 间接包含
#include "ProgramInfo.h" // 通常通过 Parser.h 间接包含
#include <string>
#include <vector>
#include <iostream> // 用于打印结果
Use code with caution.
C++
创建 Parser 的实例：
Parser myParser;
Use code with caution.
C++
提供原始数据字符串并调用 parseData:
std::string rawEpgData = "CH|10|News Channel;PG|10|500|Evening News|..."; // 你的数据
myParser.parseData(rawEpgData);
Use code with caution.
C++
获取解析后的数据：
// 获取所有频道
std::vector<ChannelInfo> allChannels = myParser.getChannels();
for (const auto& channel : allChannels) {
    std::cout << "频道 ID: " << channel.channelId << ", 名称: " << channel.channelName << std::endl;
}

// 获取特定频道的节目 (例如, 频道 ID 为 10)
int targetChannelId = 10;
std::vector<ProgramInfo> channel10Programs = myParser.getProgramsForChannel(targetChannelId);
if (channel10Programs.empty()) {
    std::cout << "未找到频道 " << targetChannelId << " 的节目。" << std::endl;
} else {
    std::cout << "频道 " << targetChannelId << " 的节目:" << std::endl;
    for (const auto& program : channel10Programs) {
        std::cout << "  - 节目 ID: " << program.programId << ", 名称: " << program.programName << std::endl;
    }
}
Use code with caution.
C++
错误处理
无效数字格式: 如果期望为整数的字段（如 ChannelID 或 ProgramID）无法使用 std::stoi 转换（例如 "abc"），则会向 stderr 打印错误消息，并跳过整个记录（CH 或 PG）。
不完整的记录: 如果记录不包含预期数量的由管道符分隔的字段，则会向 stderr 打印警告，并跳过该记录。
未知的记录类型: 如果记录不是以 "CH" 或 "PG" 开头，则会向 stderr 打印警告，并跳过该记录。
解析器会尝试处理尽可能多的有效数据，仅跳过有问题的记录。
未来可能的增强
在 ProgramInfo 中添加对节目开始时间和持续时间的支持。
实现更健壮的错误报告（例如，行号、具体的错误类型）。
支持不同或更复杂的输入格式。
为 Parser 类添加单元测试。
使用更高级的构建系统，如 CMake。
针对非常大的输入数据流优化解析性能。
许可证 (License)
本项目按“原样”提供。你可以将其视为 MIT 许可证下发布，或自由用于教育目的。