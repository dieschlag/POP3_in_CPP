#ifndef MAILBOX
#define MAILBOX

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Message.h"

class Mailbox {
private :
    std::string uid;
    std::vector<std::unique_ptr<Message>> message_list; // we use unique_ptr since the content of an email is not supposed to be copied and we benefit for the automatic memory release of unique_ptr.
    std::vector<int> delete_queue; // contains the real index that will be deleted, in the code we distingush LIST_index, the one displayed by LIST command and the real_index
    std::string username;
    std::string password;
    bool locked;
public:
    Mailbox() = default;
    ~Mailbox() = default;
    void add_mail(std::unique_ptr<Message> message_ptr);
    void delete_mail(int index);
    std::string get_uid() const;
    std::string get_mail_content(int index) const;
    void add_mail_to_delete_queue(int index_to_delete);
    void flush_delete_queue(); // to launch deletion of the mails when reaching QUITTING state
    void reset_delete_queue(); // to make the delete_queue empty with no deletion
    int get_mail_size(int index) const;
    void lock() {locked = true;};
    void unlock() {locked = false;}
    bool check_lock() {return locked;};
    bool check_credentials(const std::string& username, const std::string& password);
    std::string list_content() const;
    void init_mailbox_with_data();
    int get_mailbox_size() const;
    int get_number_of_mails_stored() const;
    std::string get_stats() const;
};

std::unique_ptr<Mailbox> init_mailbox_with_data();

#endif
