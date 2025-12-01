#include <string>
#include "RequestInvalid.h"
#include "Server.h"
#include "ResponseOk.h"


Response* RequestInvalid::accept(Server& s) const {
    return s.visit(*this);
}