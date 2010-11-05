#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

class connected_player
{
private:
public:
	enum status_type {REGISTRED, PLAYING};
	status_type status;
	boost::asio::ip::udp::endpoint endpoint;

	connected_player(boost::asio::ip::udp::endpoint& endpoint_):
	  endpoint(endpoint_),
	  status(REGISTRED)
	{
	}

    bool endpoint_eq(boost::asio::ip::udp::endpoint& endpoint_)
	{
		return this->endpoint == endpoint_;
	}

};


class server
{
  enum
  { max_length = 1024 };
    boost::array < char, max_length > recv_buffer;
    boost::array < char, max_length > send_buffer;

    boost::asio::io_service io_service;
    boost::asio::ip::udp::endpoint server_endpoint;
    boost::asio::ip::udp::endpoint remote_endpoint;
    boost::asio::ip::udp::socket socket;

    std::vector <connected_player> clients;

  void print_star()
  {
    static char ch[4] = { '|', '\\', '-', '/' };
    static int i = 0;
    std::cout << '\b' << ch[i++];
    if (i == 4)
      i = 0;

  }

  void handle_send(const boost::system::error_code & error,
                   std::size_t bytes_transferred)
  {
    BOOST_FOREACH(connected_player client, clients)
	{
	          socket.async_send_to(boost::asio::buffer(send_buffer, 1),
							client.endpoint,
                             boost::bind(&server::handle_send, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::
                                         bytes_transferred));
	}
  }

  void handle_receive(const boost::system::error_code & error,
                      std::size_t bytes_transferred)
  {
    static int i = 0;
    if (bytes_transferred)
    {
      //std::cout << "Received " << ++i << " remote endpoint:" << remote_endpoint << std::endl;


	
      if (clients.end() ==
		  std::find_if(clients.begin(), clients.end(),
		  boost::bind(&connected_player::endpoint_eq, _1, remote_endpoint)))
      {
        clients.push_back(connected_player(remote_endpoint));
        std::cout << "new client: " << remote_endpoint << std::endl;
        send_buffer[0] = clients.size();


      }
    }
  }

public:
server():
  server_endpoint(boost::asio::ip::udp::v4(), 13),
    socket(io_service, server_endpoint)
  {
  }

  void read_messages()
  {
    socket.async_receive_from(boost::asio::buffer(recv_buffer),
                              remote_endpoint,
                              boost::bind(&server::handle_receive, this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::
                                          bytes_transferred));

    io_service.poll();
  }

  void send_messages()
  {
  }

  void server_run()
  {

    while (true)
    {
      read_messages();
      send_messages();

      //socket.send(boost::asio::buffer(send_buffer));

      print_star();
    }
  }

};

int main(int argc, char *argv[])
{
  try
  {
    server udp_server;
    std::cout << "Server constructed\n";

    udp_server.server_run();

  }
  catch(std::exception & e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
