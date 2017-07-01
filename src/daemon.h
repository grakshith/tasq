#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Daemon{
public:
	Daemon();
	~Daemon();

	boost::asio::io_service _io_service;			//Service for client I/O operations
	boost::asio::io_service worker_io_service;		//Service for worker I/O operations
    boost::asio::ip::tcp::acceptor _acceptor;   	//Acceptor used to listen to incoming connections
    boost::asio::ip::tcp::acceptor worker_acceptor;	//Acceptor used to listen to incoming worker connections
    boost::asio::ip::tcp::socket incoming_socket;
    boost::thread_group _thread_group;
    std::vector<boost::asio::ip::tcp::socket*> worker_list;

    unsigned short port, worker_port;

    void runThreads(int, char**);
    void incomingConnHandler();
    void workerConnHandler();

};