#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <mutex>
#include "task.h"

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
    std::vector<std::shared_ptr<Task> > task_queue; // Queue which holds the task instances
    std::mutex push_mtx, pop_mtx;                   //Mutexes for queue operations

    unsigned short port, worker_port;

    void run_threads(int, char**);
    void incoming_conn_handler();
    void worker_conn_handler();
    void push_task_to_queue(std::shared_ptr<Task>&);
    std::shared_ptr<Task> create_new_task(string&);
    void update();

};
