#ifndef ARR_TORRENT_COMMAND_SERVER_HPP
#define ARR_TORRENT_COMMAND_SERVER_HPP

#include <boost/asio.hpp>

namespace arr
{

class command_session
{
  public:
	command_session(boost::asio::io_service &io_service) : m_socket(io_service) {}

	boost::asio::ip::tcp::socket &socket()
	{
		return m_socket;
	}

	void start();

  private:
	void handle_read(const boost::system::error_code &ec, size_t bytes_transferred);

	boost::asio::ip::tcp::socket m_socket;

	char m_data[1024];
};

class command_server
{
  public:
	command_server(boost::asio::io_service &io_service, short port)
	    : m_io_service(io_service),
	      m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::loopback(), port))
	{
		start_accept();
	}

  private:
	void start_accept();

	void handle_accept(command_session *new_session, const boost::system::error_code &ec);

	boost::asio::io_service &m_io_service;

	boost::asio::ip::tcp::acceptor m_acceptor;
};

} // end namespace arr

#endif // ARR_TORRENT_COMMAND_SERVER_HPP
