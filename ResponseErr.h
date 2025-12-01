#ifndef RESPONSEERR
#define RESPONSEERR

#include "Response.h"

#include <string>

class ResponseErr : public Response {
    public :
    ResponseErr(std::string message) : Response(message){};
    ResponseErr(std::string message, std::string multiline) : Response(message, multiline){};
    std::string get_message() const override {return message;};
    std::string get_multiline() const override {return multiline;};
    std::string get_type() const override {return "-ERR";};
};

#endif