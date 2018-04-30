#ifndef ARR_TORRENT_SERVER_HPP
#define ARR_TORRENT_SERVER_HPP

#include <condition_variable>
#include <memory>
#include <mutex>

#include <boost/asio.hpp>

namespace arr
{

using protocol = boost::asio::local::stream_protocol;

class session;
class server;

class session : public std::enable_shared_from_this<session>
{
  public:
	session(protocol::socket socket, server &server);

	void start();

  private:
	void do_read();

	protocol::socket m_socket;

	server &m_server;

	char m_data[1024];
};

class server
{
  public:
	server(boost::asio::io_service &io_service, protocol::endpoint endpoint);

	void quit();

	void wait_until_quit();

  private:
	void do_accept();

	protocol::socket m_socket;

	protocol::acceptor m_acceptor;

	volatile bool m_quit = false;
	std::mutex m_quit_lock;
	std::condition_variable m_quit_cv;
};

} // end namespace arr

#endif // ARR_TORRENT_SERVER_HPP
