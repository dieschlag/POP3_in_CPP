#ifndef REPASS
#define REPASS

#include <string>
#include "Request.h"


class Server;

class RequestPass : public Request
{
private:
    std::string password;
public:
    RequestPass(std::string args) : password{args}{};
    std::string get_arg() const {return password;} ;
    Response* accept(Server& s) const override;
};

#endif