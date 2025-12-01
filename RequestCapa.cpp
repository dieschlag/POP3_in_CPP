#include "RequestCapa.h"

Response* RequestCapa::accept(Server& s) const {
    return s.visit(*this);
}