#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "Response.h"


std::ostream& operator<<(std::ostream& os, const Response& resp){
    // Creates response string based on the request parameters and formats them to match the requirements of RFC 1939
    // First adds the +OK or the +ERR indicator with enventually an information message.
    // Then adds the multipart if not empty
    // Makes sure that all lines end with a CRLF as required and adds a final line with a "." and a CLRF if multipart
    // For now does not deal with lines starting with a "." thar requires a second "." added.
    // Response is first created as a string to be able to log it properly with \r\n which requires to browse it char by char.
    
    std::string raw_multiline = resp.get_multiline();
    std::string message = resp.get_message();
    std::cout << "message : " << resp.get_message() << std::endl;
    std::cout << "multiline : " << resp.get_multiline() << std::endl;
    
    std::string response;

    if (!message.empty()) {
        response += resp.get_type() + " " + resp.get_message() + "\r\n";
    } else {
        response += resp.get_type() + "\r\n";
    }
    
    if (!raw_multiline.empty()) {
        std::string formatted_multiline = format_multiline(raw_multiline);
        response += formatted_multiline;

        std::cout << "Printing multiline response" << std::endl;
    } else {
        std::cout << "Printing singleline response" << std::endl;
    }

    debug_print(response); // print full answer with \r\n for logging
    
    return os << response << std::flush;
}

std::string format_multiline(std::string raw_multiline) {
    // Replaces \n by \r\n for each line and adds ".\r\n" as a last line

    std::stringstream oss(raw_multiline);
    std::vector<std::string> lines;
    std::string line; // to store the line extracted from stream before adding it to lines vector
    std::string formatted_multiline;

    while (std::getline(oss, line)) {
        lines.push_back(line);
    }

    
    for (const auto& line : lines) {
        formatted_multiline += line + "\r\n";
    }
    
    formatted_multiline += ".\r\n";
    
    return formatted_multiline;
}

void debug_print(const std::string& stream_as_str) {
    // Prints a string with \r\n by browsing the string char by char

    // spacing for cleaner logs
    std::cout << std::endl;
    
    for (char c : stream_as_str) {
        switch (c) {
            case '\r': std::cout << "\\r"; break;
            case '\n': std::cout << "\\n\n"; break;
            default: std::cout << c;
        }
    }

    // spacing for cleaner logs
    std::cout << std::endl;
}