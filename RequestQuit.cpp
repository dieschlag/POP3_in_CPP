#include <string>
#include "RequestQuit.h"
#include "Server.h"
#include "ResponseOk.h"

Response* RequestQuit::accept(Server& s) const {
    return s.visit(*this);
}