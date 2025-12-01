#include "RequestFactory.h"
#include "RequestUser.h"
#include "RequestQuit.h"
#include "RequestPass.h"
#include "RequestInvalid.h"
#include "RequestList.h"
#include "RequestDele.h"
#include "RequestStat.h"
#include "RequestRetr.h"
#include "RequestCapa.h"
#include "RequestNoop.h"
#include "RequestUnauthorized.h"
#include <istream>
#include <sstream>
#include <string>

bool find_in_string_list(std::string value, std::string list[]) {
    const int list_size = sizeof(list) / sizeof(list[0]);
    return std::find(list, list + list_size, value) == list + list_size;    
}

Request * RequestFactory::create_request(std::istream& is, const State state){
    std::string str;
    std::getline(is, str);
    std::cout << "Provided command is : " << str << std::endl;
    std::istringstream stream(str);
    std::string first_word;
    stream >> first_word;
    std::string transaction_requests[] = {"LIST", "DELE", "RETR", "CAPA", "NOOP"};
    std::string authorization_requests[] = {"USER", "PASS"};

    if (first_word == "QUIT") {
        std::cout << "Creating Quit Request" << std::endl;
        return new RequestQuit();
    }

    if (first_word == "CAPA") {
        std::cout << "Creating CAPA Request" << std::endl;
        return new RequestCapa();
    }

    // Handling the requests for the AUTHORIZATION state
    // If a request supposed to be called in another state it returns an unauthorized error answer
    // Illegal commands are dealt with a specific error message

    if (state == State::AUTHORIZATION) {
        if(first_word == "USER"){
            std::cout << "Request User created" << std::endl;
            std::string username;
            stream >> username;
            std::cout << "Username provided : " << username << std::endl;
            RequestUser * req = new RequestUser(username);
            return (Request*) req;
        } else if(first_word == "PASS") {
            std::cout << "Request Pass created" << std::endl;
            std::string password;
            stream >> password;
            std::cout << password << std::endl;
            RequestPass * req = new RequestPass(password);
            return (Request*) req;
        } else if (find_in_string_list(first_word, transaction_requests)) {
            std::cout << "Unauthorized request in this state" << std::endl;
            return new RequestUnauthorized();
        }
        else {
            std::cout << "Illegal Request " << first_word << "created" << std::endl;
            RequestInvalid* req = new RequestInvalid();
            return req;
        }
    }
    
    // We are now handling the request for the TRANSACTION state 
    // If a request supposed to be called in another state it returns an unauthorized error answer
    // Illegal commands are dealt with a specific error message
    
    if (first_word == "LIST"){
        std::cout << "Creating LIST Request" << std::endl;
        RequestList* req = new RequestList();
        return req;
    } else if (first_word == "DELE") {
        std::cout << "Creating Request to DELE" << std::endl;
        std::string index_to_delete;
        stream >> index_to_delete;
        std::cout << "Index to delete is: " << index_to_delete << std::endl;
        return new RequestDele(index_to_delete);
    } else if (first_word == "STAT") {
        std::cout << "Creating STAT Request" << std::endl;
        return new RequestStat();
    } else if (first_word == "RETR") {
        std::cout << "Creating RETR Request" << std::endl;
        std::string index_to_retreive;
        stream >> index_to_retreive;
        std::cout << "Index to retreive is: " << index_to_retreive << std::endl;
        return new RequestRetr(index_to_retreive);
    } else if (first_word == "NOOP"){
        std::cout << "Creating NOOP Request" << std::endl;
        return new RequestNoop();
    } else if (find_in_string_list(first_word, authorization_requests)) {
        std::cout << "Unauthorized command in this state" << std::endl;
        return new RequestUnauthorized();
    } else {
        std::cout << "Illegal Request " << first_word << "created" << std::endl;
        RequestInvalid* req = new RequestInvalid();
        return req;
    }
}