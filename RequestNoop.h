#ifndef REQNOOP
#define REQNOOP

#include "Request.h"
#include "ResponseOk.h"
#include <string>


class Server;

class RequestNoop : public Request
{
private:
public:
    std::string get_arg() const {return "";};
    virtual Response* accept(Server& s) const override;
};


#endif