#include <iostream>

#include "asio.hpp"
#include "Server.h"

int main()
{

    asio::io_context io_context;
    Server pop3{io_context};
    pop3.init_mailbox();

    pop3.start();
}
