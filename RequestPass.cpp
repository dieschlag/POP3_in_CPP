#include "RequestPass.h"
#include "Server.h"

Response* RequestPass::accept(Server& s) const {
    return s.visit(*this);
}