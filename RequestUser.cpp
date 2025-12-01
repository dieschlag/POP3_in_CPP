#include "RequestUser.h"
#include "Server.h"


Response* RequestUser::accept(Server& s) const {
    return s.visit(*this);
}