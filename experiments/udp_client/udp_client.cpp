#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

void client()
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::resolver resolver(io_service);
	boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), 
		"127.0.0.1", "13");
	boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);

	boost::asio::ip::udp::socket socket(io_service);
	socket.open(boost::asio::ip::udp::v4());

	while(true)
	{
		socket.send_to(boost::asio::buffer("send string"), receiver_endpoint);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		client();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

