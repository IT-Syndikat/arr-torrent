#ifndef ARR_TORRENT_SERVER_HPP
#define ARR_TORRENT_SERVER_HPP

#include <memory>
#include <vector>

#include <cstdint>

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
	void read_msg_size();

	void read_msg();

	protocol::socket m_socket;

	server &m_server;

	std::uint32_t m_msg_size;
	std::vector<char> m_msg_buffer;
};

class server
{
  public:
	server(boost::asio::io_service &io_service, protocol::endpoint endpoint);

	void quit();

	void wait_until_quit();

  private:
	void accept();

	protocol::socket m_socket;

	protocol::acceptor m_acceptor;
};

} // end namespace arr

#endif // ARR_TORRENT_SERVER_HPP
