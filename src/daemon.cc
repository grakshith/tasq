#include "daemon.h"

Daemon::Daemon():_io_service(),
                 worker_io_service(),
                 _acceptor(_io_service),
                 worker_acceptor(worker_io_service),
                 incoming_socket(_io_service){
    port = 7262;
    worker_port = 7600;
}

Daemon::~Daemon(){}

void Daemon::run_threads(int argc, char **argv){
    _thread_group.add_thread(new boost::thread(&Daemon::incoming_conn_handler,this));
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    _thread_group.add_thread(new boost::thread(&Daemon::worker_conn_handler,this));
    _thread_group.join_all();
}

void Daemon::worker_conn_handler(){
    boost::asio::ip::tcp::endpoint worker_conn_endpoint(boost::asio::ip::tcp::v4(), worker_port);
    worker_acceptor.open(worker_conn_endpoint.protocol());
    worker_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    worker_acceptor.bind(worker_conn_endpoint);
    std::cout<<"Tasq is listening for workers on port "<<worker_port<<std::endl;
    while(1){
        worker_acceptor.listen();
        boost::asio::ip::tcp::socket *worker_socket = new boost::asio::ip::tcp::socket(worker_io_service);
        worker_acceptor.accept(*worker_socket);
        std::cout<<"Connection from "<<worker_socket->remote_endpoint().address().to_string()<<":"
                 <<std::to_string(worker_socket->remote_endpoint().port())<<std::endl;
        worker_list.push_back(worker_socket);
        std::string message = "OK";
        boost::asio::write(*worker_socket, boost::asio::buffer(&message[0], message.size()));
        std::cout<<"Sent"<<std::endl;
    }
}

void Daemon::incoming_conn_handler(){
    boost::asio::ip::tcp::endpoint incoming_conn_endpoint(boost::asio::ip::tcp::v4(), port);
    _acceptor.open(incoming_conn_endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(incoming_conn_endpoint);
    std::cout<<"Tasq Daemon is now listening on port "<<port<<std::endl;
    while(1){
        _acceptor.listen();
        _acceptor.accept(incoming_socket);
        std::cout<<"Connection from "<<incoming_socket.remote_endpoint().address().to_string()<<":"
                 <<std::to_string(incoming_socket.remote_endpoint().port())<<std::endl;
        std::vector<char> location(100);
        incoming_socket.read_some(boost::asio::buffer(location, 100));
        std::string task_location = std::string(location.begin(), location.end());
        shared_ptr<Task> new_task = create_new_task(task_location);
        std::cout<<"New Task created"<<std::endl;
        push_task_to_queue(new_task);
        std::string message = "OK\n";
        boost::asio::write(incoming_socket,boost::asio::buffer(&message[0],message.size()));
        incoming_socket.close();
    }
}

void Daemon::push_task_to_queue(std::shared_ptr<Task> &t){
    push_mtx.lock();
    task_queue.push_back(t);
    push_mtx.unlock();
}

std::shared_ptr<Task> Daemon::create_new_task(string &location){
    std::shared_ptr<Task> t(new Task(location));
}

int main(int argc, char** argv){
    try{
        Daemon daemon;
        daemon.run_threads(argc, argv);
    }
    catch(boost::system::system_error &e){
        std::cout<<e.what();
    }
    return 0;
}
