#include "../include/apiClassIntf.h"
apiClass *api = nullptr;

void initLib() { api = new apiClass(); }

void closeLib() { delete api; }

int add(int a, int b) { return api->add(a, b); }