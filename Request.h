#ifndef REQUEST
#define REQUEST

#include <iostream>
#include <string>
#include "Server.h"

class Request {
public:
    virtual ~Request() = default;
    virtual std::string get_arg() const = 0;
    virtual Response* accept(Server& s) const;
};


#endif
