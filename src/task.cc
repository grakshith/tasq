#include "task.h"

Task::Task(string location):
location(location),
worker_id(""),
daemon_id(""){
    has_started=false;
    has_ended=false;
    type=SHL;		
}

Task::~Task(){}

void Task::set_worker_id(string id){
    this->worker_id = id;
}

void Task::set_daemon_id(string id){
    this->daemon_id = id;
}

string Task::get_type(){
    return this->type;
}

string get_location(){
    return this->location;
}
