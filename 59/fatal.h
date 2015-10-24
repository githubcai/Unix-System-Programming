#include <stdio.h>
#include <stdlib.h>

#define Error(Str) FatalError(Str)
#define FatalError(Str) fsprintf(stderr, "%s\n", Str);exit(1)
