#ifndef RESPONSE
#define RESPONSE


#include <string>

class Response {

    protected :
    std::string message; // refers to what we print after the +OK or the -ERR on the first line of response
    std::string multiline; // text coming after the first line when we have a multiline response, here "multiline" has not the same meaning as in the RFC
    public :
    virtual ~Response() = default;
    Response(std::string message) : message{message} {};
    Response(std::string message, std::string multiline) : message(message), multiline(multiline){};
    std::string format_multiline(std::string multi_line_string);
    virtual std::string get_message() const = 0;
    virtual std::string get_multiline() const = 0;
    virtual std::string get_type() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Response& rep);

std::string format_multiline(std::string raw_message);

void debug_print(const std::string&);

#endif