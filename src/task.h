#include <iostream>
#include <string>
using namespace std;

class Task{
private:
    string location;
    enum type{SHL, PY};
    bool has_started, has_ended;
    string worker_id;
    string daemon_id;
    void set_worker_id(string);
    void set_daemon_id(string);
public:
    Task(string);
    ~Task();

    string get_type();
    string get_location();

};
