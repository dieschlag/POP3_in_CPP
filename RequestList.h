#ifndef REQLIST
#define REQLIST

#include <string>
#include "Request.h"

class Server;

class RequestList : public Request
{
private:
public:
    RequestList() = default;
    std::string get_arg() const {return "";};
    virtual Response* accept(Server& s) const override;
};





#endif