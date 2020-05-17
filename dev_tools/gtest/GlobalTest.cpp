#include <iostream> 
#include <gtest/gtest.h>

class GlobalTest : public testing::Environment
{
public:
    virtual void SetUp()
    {
        std::cout << "SetUp" << std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "TearDown" << std::endl;
    }
};

int abs(int x)
{
    return x > 0 ? x : -x; 
}

TEST(IsabsTest, HandlerTrueReturn)
{
    ASSERT_TRUE(abs(1)==1) << "abs(1) = 1";
    ASSERT_TRUE(abs(-1) == 1) << "abs(-1)=1";
    ASSERT_FALSE(abs(-2) == -2);  //期待结果是false
    ASSERT_EQ(abs(1),abs(-1));
    ASSERT_NE(abs(-1),0);
    ASSERT_LT(abs(-1),2);
    ASSERT_GT(abs(-1),0);
    ASSERT_LE(abs(-1),2);
    ASSERT_GE(abs(-1),0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    testing::Environment* env = new GlobalTest();
    testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}
