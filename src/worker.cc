#include "worker.h"
using namespace boost::asio::ip;

Worker::Worker():_io_service(),
				 daemon_socket(_io_service){
	daemon_port = 7600;
}

Worker::~Worker(){}

void Worker::runThreads(int argc, char **argv){
	_thread_group.add_thread(new boost::thread(&Worker::daemonConnHandler,this));
	_thread_group.join_all();
}

void Worker::daemonConnHandler(){
	tcp::endpoint daemon_conn_endpoint(address::from_string("127.0.0.1"), daemon_port);
	daemon_socket.connect(daemon_conn_endpoint);
	std::vector<char> message(2);
	boost::asio::read(daemon_socket,boost::asio::buffer(message,2));
	std::cout<<std::string(message.begin(), message.end());
}



int main(int argc, char** argv){
	try{
		Worker worker;
		worker.runThreads(argc, argv);
	}
	catch(boost::system::system_error &e){
		std::cout<<e.what();
	}
	return 0;
}