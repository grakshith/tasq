#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

class Daemon{
public:
	Daemon();
	~Daemon();

	boost::asio::io_service _io_service;							//Service for I/O operations
    boost::asio::ip::tcp::acceptor _acceptor;    					//Acceptor used to listen to incoming connections
    boost::asio::ip::tcp::socket incoming_socket;
    boost::thread_group _thread_group;

    unsigned short port;

    void runThreads(int, char**);
    void incomingConnHandler();

};