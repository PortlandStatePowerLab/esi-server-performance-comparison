#include <gtest/gtest.h>
#include <ecs/world.hpp>

class TestECS : public ::testing::Test 
{
protected:
    void SetUp() override 
    {        
        world.import<simple_module>();

         /* Create entity with imported components */
         // TODO: make this a loop 
        world.entity("A")
            .set<simple_module::Position>({10, 20})
            .set<simple_module::Velocity>({1, 1});

        world.entity("B")
            .set<simple_module::Position>({10, 20})
            .set<simple_module::Velocity>({1, 1});

        world.entity("C")
            .set<simple_module::Position>({10, 20})
            .set<simple_module::Velocity>({1, 1});

        world.set_target_fps(10);
    }

    void TearDown() override
    {
        // do nothing
    }

protected:
    flecs::world world;
    uint64_t run_time = 10;
};

TEST_F(TestECS, IsSampleValid) 
{   
    uint64_t count = 0;
    while (count < run_time) 
    { 
        world.progress();
        count++;
    };

    EXPECT_TRUE(false);      
}