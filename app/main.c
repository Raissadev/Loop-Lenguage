#include "super/run.h"

#define MAX_LIMIT 20

int main(int argc, char* argv[])
{
    if (argc >= 2)
        runStream(argc, argv);

    else 
        runTerminal(MAX_LIMIT);

    return 0;
}
