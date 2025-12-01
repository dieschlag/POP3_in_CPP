#ifndef STATE
#define STATE

enum class State
{
    STOPPED,
    WAITING_FOR_CONNECTION,
    TALKING_TO_USER,
    AUTHORIZATION,
    TRANSACTION,
    UPDATE,
    QUITTING
};

#endif