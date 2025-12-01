#include <iostream>
#include <sstream>
#include <algorithm>

#include "mail_data.h"
#include "Mailbox.h"

std::string Mailbox::get_uid() const {
    return uid;
}

bool Mailbox::check_credentials(const std::string& username_to_check,const std::string& password_to_check) {
    if (username_to_check == username && password_to_check == password) {
        locked = true;
        return true;
    }
    return false;
};

void Mailbox::delete_mail(int real_index) {
    if (real_index >= 0 && real_index < message_list.size()) {
        message_list.erase(message_list.begin() + real_index);
    };
}

void Mailbox::add_mail_to_delete_queue(int LIST_index) {
    int real_index = LIST_index - 1;
    if (real_index >= 0 && real_index < message_list.size()) {
        delete_queue.push_back(real_index);
        std::cout << "Index added to delete queue" << std::endl;
    };
}

void Mailbox::reset_delete_queue() {
    delete_queue.clear();
}

// deleting an element at index n, shifts backward the elements after n, so we add a shift counter to compensate
void Mailbox::flush_delete_queue() {
    std::sort(delete_queue.begin(), delete_queue.end());
    int shift = 0;
    while (!delete_queue.empty()) {
        delete_mail(delete_queue.back() - shift);
        delete_queue.pop_back();
    }
}

void Mailbox::add_mail(std::unique_ptr<Message> message_ptr) {
    message_list.push_back(std::move(message_ptr));
}

int Mailbox::get_mailbox_size() const {
    int total_size = 0;
    for (const auto& mail : message_list) {
        total_size += mail->get_message_size();
    }
    return total_size;
}

int Mailbox::get_number_of_mails_stored() const {
    return message_list.size();
}

std::string Mailbox::get_stats() const {
    std::ostringstream oss;
    oss << get_number_of_mails_stored() << " " << get_mailbox_size();
    return oss.str();
}

std::string Mailbox::get_mail_content(int LIST_index) const {
    std::ostringstream oss;
    int real_index = LIST_index - 1;
    if (real_index >= 0 && real_index < message_list.size()) {
        return message_list[real_index]->get_raw_data();
    }
}

int Mailbox::get_mail_size(int index) const {
   int real_index = index - 1;
    if (real_index >= 0 && real_index < message_list.size()) {
        return message_list[real_index]->get_message_size();
    } 
    return 0;
}

std::string Mailbox::list_content () const {
    
    std::ostringstream oss;
    

    for (int i = 0; i < message_list.size(); i++) {
        oss << i+1 << " " << message_list[i]->get_message_size() << std::endl;
    }
    
    std::string content_list = oss.str();

    return content_list;
}

// For now we consider only one mailbox, so we init at the same time the mails contained in the mailbox and the user/passwor"d
void Mailbox::init_mailbox_with_data() {
    username = "user1@localhost";
    password = "pwd123";
    std::string mail_list[5] {mail_example1, mail_example2, mail_example3, mail_example4, mail_example5};

    for (const auto& mail : mail_list) {
        this->add_mail(std::make_unique<Message>(mail));
    }
}
