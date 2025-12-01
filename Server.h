#ifndef SERVER_H
#define SERVER_H

#include <iostream>

#include "asio.hpp"
#include "Mailbox.h"

#include "State.h"

class Request;
class RequestQuit;
class RequestUser;
class RequestPass;
class RequestList;
class RequestDele;
class RequestStat;
class RequestRetr;
class RequestCapa;
class RequestNoop;
class RequestUnauthorized;
class RequestInvalid;
class Response;
class Session;
class Mailbox;

namespace ip = asio::ip;
namespace chrono = std::chrono;

class Server
{
private:
	State m_currentState{State::STOPPED};

	asio::io_context& m_io;
	ip::tcp::acceptor m_acceptor;
	ip::tcp::iostream m_stream;

	constexpr static int ECHO_PORT = 9999;

	std::unique_ptr<Mailbox> example_mailbox; // we consider we have only one mailbox, thus we use a unique_ptr for safety
	std::string user_selected; // represents the user the client is trying to access in the current session, since there is only one connection at a time, we store it in the Server class 

	Response* process(const Request& req);
	
public:
	explicit Server(asio::io_context& io);
	Response* visit(RequestQuit const& req);
	Response* visit(RequestUser const& req);
	Response* visit(RequestPass const& req);
	Response* visit(RequestList const& req);
	Response* visit(RequestDele const& req);
	Response* visit(RequestStat const& req);
	Response* visit(RequestRetr const& req);
	Response* visit(RequestCapa const& req);
	Response* visit(RequestNoop const& req);
	Response* visit(RequestInvalid const& req);
	Response* visit(RequestUnauthorized const& req);
	Response* visit(Request const& req);
	void start();
	void init_mailbox();
};


#endif
