#pragma once
#include "../common/exported.h"
#include "apiClass.h"
//
extern apiClass *api;

extern "C" {
EXPORTED void initLib();
EXPORTED void closeLib();
EXPORTED int add(int a, int b);
}