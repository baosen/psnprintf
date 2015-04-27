#include "test.h"
#include "psnprintf.test"

int main(int argc, char *argv[])
{
    try {
        TEST_SUITE(psnprintf)
    }
    catch (TestAssertException *e)
    {
        printf("Test failure: caught exception in main\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

