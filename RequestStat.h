#ifndef REQSTAT
#define REQSTAT

#include <string>
#include "Request.h"

class Server;

class RequestStat : public Request
{
private:
public:
    RequestStat() = default;
    std::string get_arg() const {return "";};
    virtual Response* accept(Server& s) const override;
};





#endif