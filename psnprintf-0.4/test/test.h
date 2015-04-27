#ifndef PSNPRINTF_TEST_H
#define PSNPRINTF_TEST_H

#include <list>
using namespace std;

typedef int (*testfunc)();

class TestCase
{
public:
    TestCase(const char *nm, testfunc fn);
    const char *name;
    char *reason;
    virtual int run();
    testfunc func;
};

class TestSuite
{
public:
    const char *name;
    list<TestCase *> cases;
    int run();
};

class TestAssertException
{
public:
    TestAssertException(char *m);
    char *msg;
};

int checkrun(const char *suitename, int argc, char *argv[]);

#define BEGIN_SUITE(sname) \
  class suite##sname : public TestSuite \
  { \
  public: \
      suite##sname () \
      { \
          name = #sname ;
          
#define TEST_CASE(func) \
  cases.push_back( new TestCase(#func , func ) );

#define END_SUITE \
      } \
  };

#define TEST_SUITE(sname) \
  if (checkrun( #sname , argc, argv)) \
  { \
      suite##sname _suit##sname; \
      _suit##sname .run(); \
  }  
  
  

#define ASSERT_STREQUAL(x, y) \
  if (strcmp(x, y) != 0) \
  { \
      char *fmt = new char[strlen(x) + strlen(y) + 32]; \
      sprintf(fmt, "Expected %s\nReceived %s\n", x, y); \
      throw new TestAssertException(fmt); \
  }
  
#define ASSERT_STREQUAL_RET(x, y, xret, yret) \
  if (strcmp(x, y) != 0) \
  { \
      char *fmt = new char[strlen(x) + strlen(y) + 32]; \
      sprintf(fmt, "Expected %s\nReceived %s\n", x, y); \
      throw new TestAssertException(fmt); \
  } \
  else if (xret != yret) \
  { \
      char *fmt = new char[50]; \
      sprintf(fmt, "Expected return %d\nReceived return %d\n", xret, yret); \
      throw new TestAssertException(fmt); \
  } 
      

#define ASSERT_LEN(str, result, expected) \
    if (expected != result) \
    { \
        char *fmt = new char[strlen(str) + 200]; /* dodgy, yes */ \
        sprintf(fmt, "String: \"%s\"\nExpected: %d\nResult: %d\n", str, expected, result); \
        throw new TestAssertException(fmt); \
    }
    
    
#define RESET_DAMAGE(buf, sz) \
    memset(buf, 0x01, sz);
    
#define ASSERT_NODAMAGE(buf, offset, sz, str) \
    for (i = offset; i < sz; i++) \
    { \
        if (buf[i] != 0x01) \
        { \
            char *fmt = new char[50 + strlen(str)]; \
            sprintf(fmt, "Format string: %s\nDamage at offset %d (%x)\n", str, i, buf[i]); \
            throw new TestAssertException(fmt); \
        } \
    }

#define ASSERT_EQUALS(expect, result, str) \
    if (result != expect) \
    { \
        char *fmt = new char[50 + strlen(str)]; \
        sprintf(fmt, "Format string: %s\nExpected return %d\nReceived return %d\n", str, expect, result); \
        throw new TestAssertException(fmt); \
    } 

#endif

