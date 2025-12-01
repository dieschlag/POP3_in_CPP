#include "RequestDele.h"
#include "Response.h"

Response* RequestDele::accept(Server& s) const {
    return s.visit(*this);
}