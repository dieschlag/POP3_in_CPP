#include "Message.h"

uint64_t Message::uid_counter = 0;

std::string Message::get_raw_data() const {
    return raw_data;
}

int Message::get_uid() const {
    return uid;
}

int Message::get_message_size() const {
    std::cout << "we get here" << std::endl;
    return raw_data.length(); 
}

Message::Message(const std::string& raw_data): raw_data(raw_data), uid(uid_counter) {
    uid_counter += 1;
}

std::ostream& operator<<(std::ostream& os, std::shared_ptr<Message> message_ptr){
    return os << message_ptr->get_raw_data();
}