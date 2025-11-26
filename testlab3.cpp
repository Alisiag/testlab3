// lab3_var15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <latch>
#include <vector>
#include <thread>
#include <memory>
#include <syncstream>

struct Action
{
    char name;
    int index;

};

void f(char x, int i) {
    std::osyncstream out(std::cout);
    out << "Action " << i << " was performed from the set " << x << std::endl;
    out << "Calculation started..." << std::endl;

    for (int k = 0; k < 1000000; ++k);

    out << "Calculation completed" << std::endl;
}

void work(std::vector<Action> Actions, std::map<char, std::vector<char>> edges, std::map<char, std::latch*> latchMap) {
    for (int n = 0; n < Actions.size(); ++n) {
        char curr = Actions[n].name;
        for (char p : edges[curr]) {
            latchMap[p]->wait();
        }
        f(Actions[n].name, Actions[n].index);
        latchMap[Actions[n].name]->count_down();
    }
}

int main()
{
    const size_t nt = 5;
    std::map<char, std::vector<char>> edges = {
    {'a', {}},
    {'b', {}},
    {'c', {}},
    {'d', {'a'}},
    {'e', {'a'}},
    {'f', {'b','c'}},
    {'g', {'d'}},
    {'h', {'d'}},
    {'i', {'e','f'}},
    {'j', {'g'}},
    {'k', {'h','i'}}
    };

    std::latch a_latch(7);
    std::latch b_latch(7);
    std::latch c_latch(6);
    std::latch d_latch(6);
    std::latch e_latch(7);
    std::latch f_latch(4);
    std::latch g_latch(4);
    std::latch h_latch(7);
    std::latch i_latch(4);
    std::latch j_latch(9);
    std::latch k_latch(5);




    std::vector<Action> thread1_actions = {
    {'a',1}, {'a',6}, {'b',4}, {'c',2}, {'d',1}, {'d',6}, {'e',5}, {'f',3}, {'g',1}, {'i', 1}, {'h', 6},{'k',1}, {'j',4}, {'j',9}
    };
    std::vector<Action> thread2_actions = {
        {'a',2}, {'a',7}, {'b',5}, {'c',3}, {'d',2}, {'e',1}, {'e', 6}, { 'f',4 }, {'g',2}, {'i',2}, {'h',7}, {'k',2}, {'j',5}
    };
    std::vector<Action> thread3_actions = {
        {'a',3}, {'b',1}, {'b',6}, {'c',4}, {'d',3}, {'e',2},{'e', 7}, { 'h',1 }, {'g',3}, {'i',3},{'j', 1}, { 'k',3 }, {'j',6}
    };
    std::vector<Action> thread4_actions = {
        {'a',4}, {'b',2}, {'b',7}, {'c',5}, {'d',4}, {'e',3}, {'f',1}, {'h',2}, {'g',4}, {'i',4}, {'j', 2}, { 'k',4 }, {'j',7}
    };
    std::vector<Action> thread5_actions = {
        {'a',5},{'b', 3}, {'c',1}, {'c',6}, {'d',5}, {'e',4}, {'f',2}, {'h',3}, {'h',4}, {'h',5}, {'j',3}, {'k',5}, {'j',8}
    };

    std::map<char, std::latch*> latchMap = {
    { 'a', &a_latch },
    { 'b', &b_latch },
    { 'c', &c_latch },
    { 'd', &d_latch },
    { 'e', &e_latch },
    { 'f', &f_latch },
    { 'g', &g_latch },
    { 'h', &h_latch },
    { 'i', &i_latch },
    { 'j', &j_latch },
    { 'k', &k_latch }

    };



    std::thread t1(work, thread1_actions, edges, latchMap);
    std::thread t2(work, thread2_actions, edges, latchMap);
    std::thread t3(work, thread3_actions, edges, latchMap);
    std::thread t4(work, thread4_actions, edges, latchMap);
    std::thread t5(work, thread5_actions, edges, latchMap);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();



    return 0;

}

