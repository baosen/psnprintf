#include <stdio.h>
#include "test.h"

int TestSuite::run()
{
    list<char *> messages;
    printf("%s: ", name);
    list<TestCase *>::iterator it;
    for (it = cases.begin(); it != cases.end(); it++)
    {
        int result = (*it)->run();
        if (result)
            printf(".");
        else
        {
            printf("F");
            char *nm = new char[strlen((*it)->name) + 9];
            sprintf(nm, "FAILED: %s", (*it)->name);
            messages.push_back(nm);
            if ((*it)->reason)
                messages.push_back((*it)->reason);
        }
    }
    
    if (messages.size() > 0)
    {
        list<char*>::iterator msgit;
        printf("\n");
        for (msgit = messages.begin(); msgit != messages.end(); msgit++)
        {
            printf("%s\n", *msgit);
            delete[] *msgit;
        }
    }
    else
    {
        printf("OK\n");
    }
    return 1;
}

TestCase::TestCase(const char *nm, testfunc fn)
{
    func = fn;
    name = nm;
    reason = NULL;
}

int TestCase::run()
{
    try
    {
        return func();
    }
    catch (TestAssertException *f)
    {
        reason = f->msg;
        return 0;
    }
}

TestAssertException::TestAssertException(char *m)
{
    msg = m;
}

int checkrun(const char *suitename, int argc, char *argv[])
{
    if (argc <= 1)
        return 1;
        
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], suitename) == 0)
            return 1;
    }
    return 0;
}
    

