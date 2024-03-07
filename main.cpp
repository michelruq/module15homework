#include <iostream>

#include "authentificationdata.h"
#include "chathash.h"

void throwHere(const std::string& text) 
{
    std::cout << "Throw text: " << text.c_str() << std::endl;
    throw 1;
}

int main (int argc, char* argv[])
{
	bool good = false;
    try {

        
        ChatHash c;

        c.addItem((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345"));
        c.addItem((char*)"user2", (char*)"asdfg", sizeof("asdfg"));
        c.addItem((char*)"user3", (char*)"zsdrt", sizeof("zsdrt"));
        c.addItem((char*)"user4", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"dfd11111", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"sdgss", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"xzxvxcccc", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"123", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"34", (char*)"pasgas", sizeof("pasgas"));
        c.addItem((char*)"111", (char*)"pasgas", sizeof("pasgas"));

        c.deletion((char*)"111");
        c.deletion((char*)"dfd11111");


        if (!c.find((char*)"user1", (char*)"qwerty12345", sizeof("qwerty12345")))  throwHere("in c.login() user1");
        if (!c.find((char*)"user2", (char*)"asdfg", sizeof("asdfg")))  throwHere("in c.login() user2");
        if (!c.find((char*)"user3", (char*)"zsdrt", sizeof("zsdrt")))  throwHere("in c.login() user3");
        if (!c.find((char*)"user3", (char*)"zsdrt", sizeof("zsdrt")))  throwHere("in c.login() user3");
        if (!c.find((char*)"user4", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() user4");
        if (!c.find((char*)"xzxvxcccc", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() xzxvxcccc");
        if (!c.find((char*)"123", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 123");
        if (!c.find((char*)"34", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 34");

        if (c.find((char*)"111", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() 111");
        if (c.find((char*)"dfd11111", (char*)"pasgas", sizeof("pasgas")))  throwHere("in c.login() dfd11111");

        if (c.find((char*)"user2", (char*)"qwerty12345", sizeof("qwerty12345"))) throwHere("in test() user2 bad pass");
        if (c.find((char*)"non-exuser", (char*)"pass", sizeof("pass"))) throwHere("in test() non-ex_user");

        good = true;
    }
    catch (...) {
        good = false;
    }

    if (good) {
        std::cout << "All Test Passed" << std::endl;
    }
    else {
        std::cout << "Test has been failed" << std::endl;
    }
    return 0;
}