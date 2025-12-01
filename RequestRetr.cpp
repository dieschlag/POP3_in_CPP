#include "RequestRetr.h"
#include "Response.h"

Response* RequestRetr::accept(Server& s) const {
    return s.visit(*this);
}