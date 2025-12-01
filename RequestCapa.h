#ifndef REQCAPA
#define REQCAPA

#include <string>
#include "Request.h"

class Server;

class RequestCapa : public Request
{
private:
public:
    RequestCapa() = default;
    std::string get_arg() const {return "";};
    virtual Response* accept(Server& s) const override;
};

#endif