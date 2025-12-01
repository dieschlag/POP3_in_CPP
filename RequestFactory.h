#ifndef REQFACTORY
#define REQFACTORY

#include "Request.h"
#include <istream>
#include <sstream>

class RequestFactory{
    public :
    static Request* create_request(std::istream& is, const State state);
};

#endif