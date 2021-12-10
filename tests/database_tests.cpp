#include <gtest/gtest.h>
#include <database/redis_client.hpp>

class TestDB: public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        
    }

    void TearDown() override
    {
        // do nothing
    }

protected:
};

TEST_F(TestDB, IsSampleValid) 
{   
    for (uint64_t i = 100; i <= 1000000; i=i*10)
    {
        std::cout << "DB Test: " << i << "\n";
        DBClient2 client2;
        client2.insert(i);
        client2.update(std::to_string(i/2),std::to_string(i));
        client2.clear();
        std::cout << "\n";
    }

    EXPECT_TRUE(false);      
}