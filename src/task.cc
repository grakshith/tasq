#include "task.h"

Task::Task(string location):
location(location),
worker_id(""),
daemon_id(""){
    has_started=false;
    has_ended=false;
    _type=SHL;
}


void Task::set_worker_id(string id){
    this->worker_id = id;
}

void Task::set_daemon_id(string id){
    this->daemon_id = id;
}

Task::type Task::get_type(){
    return this->_type;
}

string Task::get_location(){
    return this->location;
}
