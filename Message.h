#ifndef MESSAGE
#define MESSAGE

#include <iostream>
#include <string>
#include <atomic>
#include <memory>
#include <stdint.h>

class Server;

class Message {
private :
    std::string raw_data;
    uint64_t uid;
    static uint64_t uid_counter; 
public:
    ~Message() = default;
    Message(const std::string& raw_data);
    std::string get_raw_data() const;
    int get_message_size() const;
    int get_uid() const;
};

std::ostream& operator<<(std::ostream& os, std::unique_ptr<Message> ptr);


#endif