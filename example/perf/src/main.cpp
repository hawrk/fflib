#include <iostream>
using namespace std;
#include "base/fftype.h"
#include "base/timer_service.h"
#include "base/performance_daemon.h"
#include "net/base_heartbeat.h"
#include "net/socket_i.h"
#include "net/net_stat.h"


using namespace ff;

struct timeval begin;
struct timeval end;

void foo(void*)
{
    AUTO_PERF();
    gettimeofday(&end, NULL);
    long cost_ms = (end.tv_sec - begin.tv_sec)*1000 + (end.tv_usec - begin.tv_usec)/1000;

    for (int i=0; i < cost_ms % 20 + 1;  ++i){
        AUTO_PERF();
        for (int j=0; j < cost_ms % 500 + 1;  ++j)
            cout <<"oh nice:" << cost_ms << "\n";
    }
}
void test(void*)
{
    gettimeofday(&end, NULL);
    long cost_ms = (end.tv_sec - begin.tv_sec)*1000 + (end.tv_usec - begin.tv_usec)/1000;

    for (int i=0; i < cost_ms % 6 + 1;  ++i){
        AUTO_PERF();
        for (int j=0; j < cost_ms % 1000 + 1;  ++j)
            cout <<"oh Ha:" << cost_ms << "\n";
    }
}
void dumy(void*)
{
    gettimeofday(&end, NULL);
    long cost_ms = (end.tv_sec - begin.tv_sec)*1000 + (end.tv_usec - begin.tv_usec)/1000;
    for (int i=0; i < cost_ms % 10 + 1;  ++i){
        AUTO_PERF();
        for (int j=0; j < cost_ms % 300 + 1;  ++j)
            cout <<"oh fuck:" << cost_ms << "\n";
    }
}

struct tt_t
{
void tt(void *p, int a, char b, const char* c, float d, long e, string f, double g, short h)
{
    cout <<p << " " << a << " " << b << " " << c << " " << d <<" " << e << " " << f << g<<h<<" ==>cxx\n";
}
    void go(void *p, int a, char b, const char* c, float d, long e, string f, double g, short h){
        cout <<"go:"<<p<<a <<b <<c<<d <<e<<f<<g<<h
        <<"\n";
    }
};

void xx(void *p)
{
    cout <<p << " ==>cxx\n";
}

class foo_t: public obj_counter_t<foo_t>
{
public:
    
};

class foo2_t: public foo_t, obj_counter_t<foo2_t>
{
public:
    
};
class dumy_t: public obj_counter_t<dumy_t>
{
public:
    
};

void test(int n = 100)
{
    AUTO_PERF();
    for (int i = 0; i < n; ++i)
    {
        foo_t* p = new foo_t();
        foo2_t* p2 = new foo2_t();
        dumy_t* p3 = new dumy_t();
    }
}
int main(int argc, char* argv[])
{
    singleton_t<performance_daemon_t>::instance().start("perf", 5);
    
    test();
    
    for (int j = 0; j < 10; ++j)
    {
        sleep(2);
        test(500);
    }
    sleep(600);
    singleton_t<performance_daemon_t>::instance().stop();
    return 0;
    task_t t1(&xx, NULL);
    task_t t2 = t1;
    tt_t t;
    task_t t3;t3= task_binder_t::gen(&tt_t::go, &t, argv, 777, 'Y', "HH", 0.33, 555, "ERER", 99.99, 6699);
    //task_binder_t::gen(&tt_t::tt, &t, argv, 1, 'a', "ccc", 0.3, 1999, "xx", 999.99, 20);
    t3.run();
    
    /*
    base_heartbeat_t<socket_ptr_t> tmp;
    tmp.set_option("xx", NULL);
    tmp.add(NULL);
    tmp.del(NULL);
    tmp.timer_check();*/
    
    // 

    timer_service_t ts(1);
    ts.timer_callback(2000, task_t(&xx, (void*)2));
    ts.timer_callback(1000, task_t(&xx, (void*)1));
    ts.timer_callback(3000, task_t(&xx, (void*)3));
    for (int i = 0; i < 1; ++i)
    ts.loop_timer(1000, task_t(&xx, (void*)4));
/*
    for (int i = 0; i < 100; ++i)
    {
        gettimeofday(&begin, NULL);
        ts.timer_callback(200, task_t(&foo, NULL));
        ts.timer_callback(300, task_t(&test, NULL));
        ts.timer_callback(500, task_t(&dumy, NULL));
        usleep(1000*100);
    }
*/
    

    //singleton_t<performance_daemon_t>::instance().stop();  
    return 0;
}
