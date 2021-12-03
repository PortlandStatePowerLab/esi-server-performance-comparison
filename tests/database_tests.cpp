#include <gtest/gtest.h>
#include <database/db_client.hpp>

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
    DBClient client;
};

TEST_F(TestDB, IsSampleValid) 
{   
    client.Insert();

    EXPECT_TRUE(false);      
}