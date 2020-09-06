//
// Created by Dellvin on 06.09.2020.
//
#include "gtest/gtest.h"

extern "C++" {
#include "../include/client/ui.h"
#include "../include/server/server.h"
}
#include "clientForTest.h"
#include "../include/server/session/constexp.h"
#include "../include/server/room/constexp.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>

using namespace std;
TEST(test, ClientTest1) {
    UI cli("lkjhflj", 2000);
    streambuf* oldCoutStreamBuf = cerr.rdbuf();
    ostringstream strCout;
    cerr.rdbuf( strCout.rdbuf() );

    EXPECT_EQ(cli.start(), 1);

    cerr.rdbuf( oldCoutStreamBuf );


    EXPECT_EQ(strCout.str(), "Invalid Ip address\n");
}

//TEST(test, ClientTest2) {
//    UI cli("192.168.0.1", 2000);
//    streambuf* oldCoutStreamBuf = cerr.rdbuf();
//    ostringstream strCout;
//    cerr.rdbuf( strCout.rdbuf() );
//    EXPECT_EQ(cli.start(), 3);
//    cerr.rdbuf( oldCoutStreamBuf );
//    EXPECT_EQ(strCout.str(), "Connection error\n");
//}

TEST(test, ServerTest1) {
    streambuf* oldCoutStreamBuf = cerr.rdbuf();
    ostringstream strCout;
    cerr.rdbuf( strCout.rdbuf() );
    Server s(111);
    s.start();
    cerr.rdbuf( oldCoutStreamBuf );
    EXPECT_EQ(strCout.str(), "Binding error\n");
}

TEST(test, ServerTest2) {
    int stdoutCopy=dup(1);
    int test=open("test.txt",O_RDWR|O_CREAT,0666 );
    dup2(test, 1);
    int res=fork();
    if(res==-1){
        exit(1);
    }
    if(!res){
        alarm(1);
        Server s(2021);
        s.start();
        _exit(0);
    }
    wait(nullptr);
    close(test);
    dup2(stdoutCopy, 1);
    close(stdoutCopy);
    std::ifstream in("test.txt");
    std::string result;
    std::getline(in, result);
    in.close();
    EXPECT_EQ(result, "Waiting for connections...");

    remove("test.txt");
}

TEST(test, both1) {
    int stdoutCopy=dup(1);
    int stderrCopy=dup(2);
    int test=open("test.txt",O_RDWR|O_CREAT,0666);
    dup2(test, 1);
    dup2(test, 2);
    int res=fork();
    if(res==-1){
        exit(1);
    }
    if(!res){
        alarm(5);
        res=fork();
        if(res==-1)exit(1);
        if(!res){
            alarm(3);
            Server s(2021);
            s.start();
            exit(0);
        }
        sleep(1);
        UI cli("127.0.0.1",2021);
        cli.start();
        exit(0);
    }
    wait(nullptr);

    dup2(stdoutCopy, 1);
    dup2(stderrCopy, 2);
    close(test);
    close(stderrCopy);
    close(stdoutCopy);
    std::ifstream in("test.txt");
    std::string result;
    std::getline(in, result);
    EXPECT_EQ(result, "Waiting for connections...");
    std::getline(in, result);
    EXPECT_EQ(result, "You successfully connected to server!");
    std::getline(in, result);
    std::string connectedMess;
    for(uint8_t i=0;i<strlen("Client with socket number");i++){
        connectedMess+=result[i];
    }
    EXPECT_EQ(connectedMess, "Client with socket number");
    in.close();
    remove("test.txt");
}

TEST(test, server_work) {
    int stdoutCopy=dup(1);
    int stderrCopy=dup(2);
    int test=open("test.txt",O_RDWR|O_CREAT,0666);
    dup2(test, 1);
    dup2(test, 2);
    int res=fork();
    if(res==-1){
        exit(1);
    }
    if(!res){
        alarm(6);
        res=fork();
        if(res==-1)exit(1);
        if(!res){
            alarm(3);
            Server s(2021);
            s.start();
            exit(0);
        }
        clientForTest t("127.0.0.1", 2021);
        t.start();
        t.recv();
        t.send("(*&^%$\n");
        std::string answer;
        answer=t.recv();
        EXPECT_EQ(answer, WRONG_LOGIN);
        t.send("dellvin\n");
        answer=t.recv();
        EXPECT_EQ(answer, SIGN_IN_OK);
        t.send("#help\n");
        answer=t.recv();
        EXPECT_EQ(answer, HELP_MESSAGE);
        t.send("#join room\n");
        answer=t.recv();
        EXPECT_EQ(answer, JOIN_ERROR);
        t.send("#asdiifg\n");
        answer=t.recv();
        EXPECT_EQ(answer, UNDEFINE_MESSAGE);
        t.send("#create room\n");
        answer=t.recv();
        EXPECT_EQ(answer, "The room 'room' has been created!\n");
        t.send("asihdf\n");
        answer=t.recv();
        EXPECT_EQ(answer, "dellvin: asihdf\n");
        exit(0);
    }
    wait(nullptr);
    close(test);
    dup2(stdoutCopy, 1);
    dup2(stderrCopy, 2);
    close(stderrCopy);
    close(stdoutCopy);
    //remove("test.txt");
}