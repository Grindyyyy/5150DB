#pragma once
#include "api.h"
#include "init.hpp"
#include "toggles.hpp"

extern void wait(int msec);

class Autons{
    public:
        void test();
        void closeSide();
        void farSide();
        void farSide2();
        void awp();
        void skills();
};