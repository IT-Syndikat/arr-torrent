#include "command_server.hpp"

#include <iostream>
#include <utility>

using namespace boost::asio;

namespace arr
{

session::session(ip::tcp::socket socket) : m_socket(std::move(socket)) {}

void session::start()
{
	do_read();
}

void session::do_read()
{
	auto self(shared_from_this());

	auto cb = [this, self](boost::system::error_code ec, std::size_t length) {
		if (!ec) {
			std::cerr << "TODO handle read\n";
			m_socket.get_io_service().stop();
		}
	};

	m_socket.async_read_some(buffer(m_data, sizeof(m_data)), cb);
}

server::server(io_service &io_service, short port)
    : m_socket(io_service), m_acceptor(io_service, ip::tcp::endpoint(ip::address_v4::loopback(), port))
{
	do_accept();
}
void server::do_accept()
{
	auto cb = [this](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<session>(std::move(m_socket))->start();
		}
	};

	m_acceptor.async_accept(m_socket, cb);
}

} // end namespace arr
