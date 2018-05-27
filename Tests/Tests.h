//
// Created by razvan on 26.03.2018.
//

#ifndef LAB5_6_TESTS_H
#define LAB5_6_TESTS_H

#include "../Controller/Controller.h"

class Tests {
public:
    static void initialize(Controller &);
    static void testDog();
    static void testRepository();
    static void testController();
    static void testController2nd();
    static void testLists();
    static void testComparator();
    static void testValidator();
    static void testAll();
};


#endif //LAB5_6_TESTS_H
