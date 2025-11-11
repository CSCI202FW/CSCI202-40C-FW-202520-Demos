#include <gtest/gtest.h>
#include "../linkedStack.h"
using namespace std;
template <class t>
using stack = linkedStack<t>;

TEST(stackTest, Test1)
{
    stack<int> s(2);

    s.push(1);
    s.push(2);
    try
    {

        s.push(3);
        s.pop();
    }
    catch (...)
    {
        ASSERT_TRUE(true);
    }
    cout << s.top() << endl;
    ASSERT_EQ(s.top(), 2);
    s.pop();
    cout << s.top() << endl;
    ASSERT_EQ(s.top(), 1);
    s.pop();
    try
    {
        s.pop();
        ASSERT_TRUE(false);
    }
    catch (...)
    {
        ASSERT_TRUE(true);
    }

    stack<int> s2(100);
    s2.push(1);
    s2.push(2);
    ASSERT_FALSE(s2.isEmptyStack());
    s2.initializeStack();
    ASSERT_TRUE(s2.isEmptyStack());
}

extern "C" int startTest(int x, char **y)
{
    // cout << "begin" << endl;
    // int x = 0;
    // char ** y = NULL;
    testing::InitGoogleTest(&x, y);
    // cout << "Init Complete"<< endl;
    int code = RUN_ALL_TESTS();
    // exit(code);
    return code;
}
// int i = startTest();
extern "C" int __wrap_main(int x, char **y)
{
    return startTest(x, y);
}