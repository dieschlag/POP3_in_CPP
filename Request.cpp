#include "Request.h"
#include "Server.h"
#include "Response.h"


Response* Request::accept(Server& s) const {
    std::cout << "Requete acceptée" << std::endl;
    return s.visit(*this);
}