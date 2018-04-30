#include "command_server.hpp"

#include <iostream>
#include <thread>
#include <utility>

using namespace boost::asio;

namespace arr
{

session::session(protocol::socket socket, server &server) : m_socket(std::move(socket)), m_server(server) {}

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
			m_server.quit();
		}
	};

	m_socket.async_read_some(buffer(m_data, sizeof(m_data)), cb);
}

server::server(io_service &io_service, protocol::endpoint endpoint)
    : m_socket(io_service), m_acceptor(io_service, endpoint)
{
	do_accept();
}

void server::quit()
{
	{
		std::lock_guard<std::mutex> lk(m_quit_lock);
		m_quit = true;
	}
	m_quit_cv.notify_all();
}

void server::wait_until_quit()
{
	auto ul = std::unique_lock<std::mutex>(m_quit_lock);
	m_quit_cv.wait(ul, [&]() { return m_quit; });
}

void server::do_accept()
{
	auto cb = [this](boost::system::error_code ec) {
		if (!ec) {
			std::make_shared<session>(std::move(m_socket), *this)->start();
		}
	};

	m_acceptor.async_accept(m_socket, cb);
}

} // end namespace arr
