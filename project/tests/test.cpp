//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

extern "C++" {
#include "../include/ui.h"
}



TEST(test, Test2) {
    UI cli("lkjhflj", 2000);
    EXPECT_EQ(cli.start(), 1);
}
