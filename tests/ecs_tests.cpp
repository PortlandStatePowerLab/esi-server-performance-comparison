#include <gtest/gtest.h>
#include <ecs/world.hpp>
#include <chrono>

class TestECS : public ::testing::Test 
{
protected:
    void SetUp() override 
    {   
        world.import<simple_module>();     
    }

    void TearDown() override
    {
        // do nothing
    }

protected:
    flecs::world world;

    class Timer
    {
    public:

        using clock_t = std::chrono::high_resolution_clock;
        using duration_t = clock_t::duration;

    private:
        clock_t::time_point start_time;

    public:

        Timer(): start_time(clock_t::now()) 
        { 
            // do nothing
        };

        ~Timer()
        {
            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(get_elapsed_time()).count() << ", ";
        };

        duration_t get_elapsed_time() const 
        { 
            return (clock_t::now() - start_time); 
        };
    };

    void insert (uint64_t count)
    {
        Timer stop_watch;
        for (uint64_t i = world.count<simple_module::Xml>()+1; i <= count; i++)
        {
            world.entity()
                .set<simple_module::Xml>({"some formatted xml stuff that is really long"})
                .set<simple_module::StartTime>({i});
        };
        
    };

    void update (uint64_t start, uint64_t stop)
    {
        auto compareFunc = [start,stop](uint64_t a) { return ((a >= start) && (a <= stop)); };

        Timer stop_watch;

        auto f = world.filter<simple_module::Xml, simple_module::StartTime>();
        f.each([compareFunc](flecs::entity e, simple_module::Xml& x, simple_module::StartTime& s) {
            x.resource = "some formatted xml stuff that is really long --updated";
            s.start_time = s.start_time + 1000;
        });
    };

    void clear ()
    {
        std::cout << world.count<simple_module::Xml>();
    }
};

TEST_F(TestECS, IsSampleValid) 
{   
    for (uint64_t i = 100; i <= 1000000; i=i*10)
    {
        std::cout << "ECS Test: " << i << "\n";
        insert(i);
        update(i/2, i);
        clear();
        std::cout << "\n";
    }    
    EXPECT_TRUE(false);  
}