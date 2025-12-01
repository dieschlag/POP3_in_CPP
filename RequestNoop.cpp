#include "RequestNoop.h"
#include "Server.h"
#include "ResponseOk.h"


Response* RequestNoop::accept(Server& s) const {
    return s.visit(*this);
}