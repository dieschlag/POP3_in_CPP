#include "RequestStat.h"

Response* RequestStat::accept(Server& s) const {
    return s.visit(*this);
}