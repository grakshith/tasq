#include "worker.h"
using namespace boost::asio::ip;

Worker::Worker():_io_service(),
                 daemon_socket(_io_service){
    daemon_port = 7600;
}

Worker::~Worker(){}

void Worker::runThreads(int argc, char **argv){
    _thread_group.add_thread(new boost::thread(&Worker::daemonConnHandler,this,argv[1]));
    _thread_group.join_all();
}

void Worker::daemonConnHandler(std::string addr){
    tcp::endpoint daemon_conn_endpoint(address::from_string(addr), daemon_port);
    daemon_socket.connect(daemon_conn_endpoint);
    std::vector<char> message(3);
    boost::asio::read(daemon_socket,boost::asio::buffer(message,3));
    std::cout<<std::string(message.begin(), message.end());
}



int main(int argc, char** argv){
    if(argc<2){
        std::cerr<<"Usage: worker <daemon addr>\n";
        return 1;
    }
    try{
        Worker worker;
        worker.runThreads(argc, argv);
    }
    catch(boost::system::system_error &e){
        std::cout<<e.what();
    }
    return 0;
}
