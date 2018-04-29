#ifndef ARR_TORRENT_SERVER_HPP
#define ARR_TORRENT_SERVER_HPP

#include <memory>

#include <boost/asio.hpp>

namespace arr
{

class session : public std::enable_shared_from_this<session>
{
  public:
	session(boost::asio::ip::tcp::socket socket);

	void start();

  private:
	void do_read();

	boost::asio::ip::tcp::socket m_socket;

	char m_data[1024];
};

class server
{
  public:
	server(boost::asio::io_service &io_service, short port);

  private:
	void do_accept();

	boost::asio::ip::tcp::socket m_socket;

	boost::asio::ip::tcp::acceptor m_acceptor;
};

} // end namespace arr

#endif // ARR_TORRENT_SERVER_HPP
