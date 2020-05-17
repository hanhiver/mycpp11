#include <iostream> 
#include <map>
#include <gtest/gtest.h>

class TestMap : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        std::cout << "SetUpTestCase" << std::endl;
    }

    static void TearDownTestCase()
    {
        std::cout << "TearDownTestCase" << std::endl; 
    }

    // TEST跑之前会执行的SetUp
    virtual void SetUp()
    {
        std::cout << "SetUp" << std::endl;
        test_map.insert(std::make_pair(1, 0));
        test_map.insert(std::make_pair(2,1));
        test_map.insert(std::make_pair(3,2));
        test_map.insert(std::make_pair(4,3));
        test_map.insert(std::make_pair(5,4));
    }

    // TEST跑完之后会执行的TearDown
    virtual void TearDown()
    {
        std::cout << "TearDown" << std::endl;
        test_map.clear();
    }
    
    std::map<int, int> test_map;
};

TEST_F(TestMap, Find)
{
    std::map<int, int>::iterator it = test_map.find(1);
    ASSERT_NE(it, test_map.end());
}

TEST_F(TestMap, Size)
{
    ASSERT_EQ(test_map.size(), 5);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

