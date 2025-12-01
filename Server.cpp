#include <iostream>
#include <map>

#include "asio.hpp"
#include "Server.h"
#include "RequestFactory.h"
#include "RequestUser.h"
#include "RequestPass.h"
#include "RequestQuit.h"
#include "RequestList.h"
#include "Response.h"
#include "ResponseOk.h"
#include "ResponseErr.h"
#include "RequestDele.h"
#include "RequestRetr.h"
#include "RequestNoop.h"
#include "Mailbox.h"

namespace ip = asio::ip;


// On crée l'instance du Serveur avec un objet ASIO context qui sert à
// orchestrer tous les objets et événements gérés par ASIO (connexions réseau,
// timers, etc.)
Server::Server(asio::io_context& ioContext) :
	m_io{ioContext},
	// On crée la socket sur laquelle on écoutera
	m_acceptor{ioContext, ip::tcp::endpoint{ip::tcp::v4(), ECHO_PORT}}
{}

void Server::start()
{
	
	for (;;)
	{
		m_currentState = State::WAITING_FOR_CONNECTION;
		m_stream = ip::tcp::iostream{};
		m_acceptor.accept(m_stream.socket());
		user_selected = ""; // initalize the username, updated when the client uses USER
		
		// send OK response after connection
		std::cout << "New client connected!" << std::endl;
		ResponseOk* first_response = new ResponseOk(" POP3 Server Ready");
		m_stream << *first_response;
		delete first_response;

		// begin authorization state
		m_currentState = State::AUTHORIZATION;

		// Both AUTHORIZATION and TRANSACTION states are dealt with in this loop, the difference in terme of command access is delt with in the RequestFactory
		// Thus the current state is given as a parameter 
		while (m_stream && m_currentState != State::QUITTING && m_currentState != State::UPDATE) {
			Request* req = RequestFactory::create_request(m_stream, m_currentState);
			std::cout << "Request created" << std::endl;
			Response* rep = process(*req);
			m_stream << *rep;
			delete rep;
			delete req;
		}

		// On update, the mails planned to be deleted are indeed deleted and then we quit
		if (m_currentState == State::UPDATE) {
			example_mailbox->flush_delete_queue();
			example_mailbox->unlock(); // unlocking the mailbox after use, the case where the connection is ended abruptly is not dealt with
			m_currentState = State::QUITTING;
		}

		// Reached once the QUITTING state is reached (last state reached in the loop), closing the connection
		if (m_stream) {
			m_stream.close();
		}
	}
}

Response* Server::process(const Request& req)
{
	std::cout << "Processing Request" << std::endl; 
	Response* response = req.accept(*this);
	std::cout << "Request accepted" << std::endl;
	return response;
}

Response* Server::visit(RequestQuit const& req){
	if (m_currentState == State::TRANSACTION){
		m_currentState = State::UPDATE;
		return new ResponseOk{"Closing session with delete of requested mails to delete"};
	}
	m_currentState = State::QUITTING;
	return new ResponseOk{"Closing session with no change on server"};
}

Response* Server::visit(RequestUser const& req){
	ResponseOk* response = new ResponseOk("");
	user_selected = req.get_arg();
	return response;
}

Response* Server::visit(RequestPass const& req){
	if (example_mailbox->check_credentials(user_selected, req.get_arg())){
	    example_mailbox->lock();
		m_currentState = State::TRANSACTION;
	    return new ResponseOk{"Mailbox locked and ready"};
	} else {
		return new ResponseErr{"Identifiant ou mot de passe incorrect."};
	}
}

Response* Server::visit(RequestList const& req){
	std::string message = std::to_string(example_mailbox->get_number_of_mails_stored()) + " messages (" + std::to_string(example_mailbox->get_mailbox_size()) + " octets)"; 
	std::string multiline = example_mailbox.get()->list_content();
	return new ResponseOk{message, multiline};
}

Response* Server::visit(RequestRetr const& req){	
	int index_to_retreive;
	try {
		// index provided is between 1 and number of mails in mailbox, so there is a shift by 1 in the checking of the index
		index_to_retreive = std::stoi(req.get_arg());
		if (index_to_retreive > 0 and index_to_retreive <= example_mailbox->get_number_of_mails_stored()) {
			std::string message = std::to_string(example_mailbox->get_mail_size(index_to_retreive));
			return new ResponseOk{message, example_mailbox->get_mail_content(index_to_retreive)};
		}
		return new ResponseErr{"Please provide a valid index. Use LIST command to display them."};
	} catch (std::invalid_argument) {
		return new ResponseErr{"Please provide an integer as the argument of command DELE. It must be a valid index. Use LIST command to display them."};
	} catch (std::out_of_range) {
		return new ResponseErr{"Please provide an integer as the argument of command DELE. It must be a valid index. Use LIST command to display them."};
	}
	return new ResponseErr("Internal Server Error");
}

Response* Server::visit(RequestDele const& req){	
	int index_to_delete;
	try {
		// index provided is between 1 and number of mails in mailbox, so there is a shift by 1 in the checking of the index
		index_to_delete = std::stoi(req.get_arg());
		if (index_to_delete > 0 and index_to_delete <= example_mailbox->get_number_of_mails_stored()) {
			std::cout << "Adding index " << index_to_delete << "to delete queue" << std::endl;
			example_mailbox->add_mail_to_delete_queue(index_to_delete);
			std::stringstream success_message;
			success_message << "Message of index " << index_to_delete << " has been successfully detected.";
			return new ResponseOk{success_message.str()};
		}
		return new ResponseErr{"Please provide a valid index. Use LIST command to display them."};
	} catch (std::invalid_argument) {
		return new ResponseErr{"Please provide an integer as the argument of command DELE. It must be a valid index. Use LIST command to display them."};
	} catch (std::out_of_range) {
		return new ResponseErr{"Please provide an integer as the argument of command DELE. It must be a valid index. Use LIST command to display them."};
	}
	return new ResponseErr{"Internal Server Error"};
}

Response* Server::visit(RequestStat const& req){
	std::string message = std::to_string(example_mailbox->get_number_of_mails_stored()) + " " +  std::to_string(example_mailbox->get_mailbox_size());
	return new ResponseOk{message};
}

// Capa is used by thunderbird so we have implemented it to allow the connection with the thunderbird client
// It lists the available commands for the client to use
Response* Server::visit(RequestCapa const& req){
	std::ostringstream oss;
	std::string message = "Capability list follows";
	
	std::string allowed_commands[] = {"USER", "PASS", "LIST", "RETR", "CAPA", "STAT", "QUIT", "DELE", "NOOP"};
	int number_allowed_commands = sizeof(allowed_commands) / sizeof(allowed_commands[0]); 
	
	for (int i = 0; i < number_allowed_commands; i++) {
		oss << allowed_commands[i] << "\n";
	}
	
	return new ResponseOk{message, oss.str()};
}

Response* Server::visit(Request const& req){
	return new ResponseErr{"Command invalid"};
}

Response* Server::visit(RequestNoop const& req){
	return new ResponseOk{""};
}

Response* Server::visit(RequestUnauthorized const& req){
	return new ResponseErr{"Unauthorized command in this state"};
}

Response* Server::visit(RequestInvalid const& req){
	return new ResponseErr{"Command not recognized by the server. Please use CAPA to see the list of available commands"};
}

void Server::init_mailbox() {
	example_mailbox = std::make_unique<Mailbox>();
	example_mailbox->init_mailbox_with_data();
}