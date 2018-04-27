#include "command_server.hpp"

#include <iostream>

#include <boost/bind.hpp>

namespace arr
{

void command_session::start()
{
	m_socket.async_read_some(boost::asio::buffer(m_data, sizeof(m_data)),
	                         boost::bind(&command_session::handle_read, this, boost::asio::placeholders::error,
	                                     boost::asio::placeholders::bytes_transferred));
}

void command_session::handle_read(const boost::system::error_code &ec, size_t bytes_transferred)
{
	std::cerr << "TODO handle read\n";
	m_socket.get_io_service().stop();
	delete this;
}

void command_server::start_accept()
{
	command_session *new_session = new command_session(m_io_service);
	m_acceptor.async_accept(new_session->socket(), boost::bind(&command_server::handle_accept, this, new_session,
	                                                           boost::asio::placeholders::error));
}

void command_server::handle_accept(command_session *new_session, const boost::system::error_code &ec)
{
	if (!ec) {
		new_session->start();
	} else {
		delete new_session;
	}

	start_accept();
}

} // end namespace arr
