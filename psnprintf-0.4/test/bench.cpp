// Benchmark psnprintf

#include "../psnprintf.h"

#ifndef WIN32
#include <stdio.h>
int main()
{
    printf("Benchmarking for Windows only, sorry!\n");
    return EXIT_SUCCESS;
}
#else

#ifdef CYGWIN
// Cygwin prefers posix libraries
#define _snprintf snprintf
#endif

#include <stdio.h>
#include <windows.h>
#include <winbase.h>

#define ITERATIONS 500000
#define BUFFSIZE 512

#define BENCH(label, spr, snpr, psnr) \
    printf("\n" label "\n"); \
    QueryPerformanceCounter(&start); \
    for (i = 0; i < ITERATIONS; i++) \
    { \
        spr ;\
    } \
    QueryPerformanceCounter(&end); \
    printf("sprintf: %10d\n", end.QuadPart - start.QuadPart); \
    \
    QueryPerformanceCounter(&start); \
    for (i = 0; i < ITERATIONS; i++) \
    { \
        snpr ;\
    } \
    QueryPerformanceCounter(&end); \
    printf("snprintf: %9d\n", end.QuadPart - start.QuadPart); \
    \
    QueryPerformanceCounter(&start); \
    for (i = 0; i < ITERATIONS; i++) \
    { \
        spr ;\
    } \
    QueryPerformanceCounter(&end); \
    printf("psnprintf: %8d\n", end.QuadPart - start.QuadPart);

int main()
{
    int i;
    char buf[BUFFSIZE];
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    
    printf("The following tests try to evaluate psnprintf's performance against\n"
           "your compiler's native sprintf and snprintf implementation.  Each\n"
           "test is repeated %d times and the results are reported as the\n"
           "the number of CPU cycles taken.  In my experience, these values\n"
           "are not terribly consistent.  Run the benchmark a few times to get\n"
           "a feel for how things move.\n", ITERATIONS);
    
    if (!QueryPerformanceCounter(&start))
    {
        printf("No high-resolution timer on board");
        return 0;
    }    
    
    BENCH("No substitutions", 
        sprintf(buf, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"),
        _snprintf(buf, BUFFSIZE, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"),
        psnprintf(buf, BUFFSIZE, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") )
    
    BENCH("Integer",
        sprintf(buf, "%d %5d %.5d %x %o", 46378, 23467, 342, 24378, 23784),
        _snprintf(buf, BUFFSIZE, "%d %5d %.5d %x %o", 46378, 23467, 342, 24378, 23784),
        psnprintf(buf, BUFFSIZE, "%d %5d %.5d %x %o", 46378, 23467, 342, 24378, 23784) )
    
    BENCH("String",
        sprintf(buf, "%s %10s", "ABCDEFG", "ABC"),
        _snprintf(buf, BUFFSIZE, "%s %10s", "ABCDEFG", "ABC"),
        psnprintf(buf, BUFFSIZE, "%s %10s", "ABCDEFG", "ABC") )

	return ERROR_SUCCESS;
}

#endif /* WIN32 */

