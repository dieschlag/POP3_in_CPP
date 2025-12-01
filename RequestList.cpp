#include "RequestList.h"

Response* RequestList::accept(Server& s) const {
    return s.visit(*this);
}