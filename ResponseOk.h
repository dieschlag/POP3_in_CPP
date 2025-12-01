#ifndef RESPONSEOK
#define RESPONSEOK

#include "Response.h"

#include <string>

class ResponseOk : public Response {
    public :
    ResponseOk(std::string message) : Response(message){};
    ResponseOk(std::string message, std::string multiline) : Response(message, multiline){};
    std::string get_message() const override {return message;};
    std::string get_multiline() const override {return multiline;};
    std::string get_type() const override {return "+OK";};
};

#endif