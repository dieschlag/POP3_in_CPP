#ifndef REQUNAUTH
#define REQUNAUTH

#include "Request.h"
#include "ResponseOk.h"
#include <string>


class Server;

class RequestUnauthorized : public Request
{
private:
public:
    std::string get_arg() const {return "";};
    virtual Response* accept(Server& s) const override;
};


#endif