#include <string>
#include "RequestUnauthorized.h"
#include "Server.h"
#include "ResponseOk.h"

Response* RequestUnauthorized::accept(Server& s) const {
    return s.visit(*this);
}