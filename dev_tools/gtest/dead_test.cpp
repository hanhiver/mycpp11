#include <gtest/gtest.h>

int func()
{
    int *ptr = NULL;
    *ptr = 100;
    return 0;
}

/*
TEST(FuncDeathTest, Nullptr)
{
    ASSERT_DEATH(func(), "");
}
*/

TEST(DeathTest, test_nullptr)
{
    ASSERT_DEATH(func(), "");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
