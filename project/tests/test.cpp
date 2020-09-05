//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

extern "C++" {
#include "../include/ui.h"
}

#include <iostream>
#include <sstream>
using namespace std;
TEST(test, Test1) {
    UI cli("lkjhflj", 2000);
    streambuf* oldCoutStreamBuf = cerr.rdbuf();
    ostringstream strCout;
    cerr.rdbuf( strCout.rdbuf() );

    EXPECT_EQ(cli.start(), 1);

// Restore old cout.
    cerr.rdbuf( oldCoutStreamBuf );

// Will output our Hello World! from above.

    EXPECT_EQ(strCout.str(), "Invalid Ip address\n");
}

TEST(test, Test2) {
    UI cli("192.168.0.1", 2000);
    streambuf* oldCoutStreamBuf = cerr.rdbuf();
    ostringstream strCout;
    cerr.rdbuf( strCout.rdbuf() );

    EXPECT_EQ(cli.start(), 3);

// Restore old cout.
    cerr.rdbuf( oldCoutStreamBuf );

// Will output our Hello World! from above.

    EXPECT_EQ(strCout.str(), "Connection error\n");

}

