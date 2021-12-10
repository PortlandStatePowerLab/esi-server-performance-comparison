#include <database/redis_client.hpp>

int main(int argc, char **argv) 
{
    for (uint64_t i = 100; i <= 1000000; i=i*10)
    {
        DBClient2 client2;
        client2.insert(i);
        client2.update(std::to_string(i/2),std::to_string(i));
        client2.clear();
        std::cout << "\n";
    }
    return 0;
}