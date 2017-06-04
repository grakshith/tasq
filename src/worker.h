#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

class Worker{
public:
	Worker();
	~Worker();

	boost::asio::io_service _io_service;			//Service for I/O operations
    boost::asio::ip::tcp::socket daemon_socket;
    boost::thread_group _thread_group;

    unsigned short daemon_port;

    void runThreads(int, char**);
    void daemonConnHandler();

};