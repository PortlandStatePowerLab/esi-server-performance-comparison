#ifndef __REDIS_CLIENT_H__
#define __REDIS_CLIENT_H__

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <variant>
#include <chrono>
#include <vector>

#include <redis-cpp/stream.h>
#include <redis-cpp/execute.h>

class Timer
{
public:
    using clock_t = std::chrono::high_resolution_clock;
    using duration_t = clock_t::duration;

private:
    clock_t::time_point start_time;

public:
    Timer() : start_time(clock_t::now()){
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

class DBClient2
{
public:
    DBClient2(){
        // do nothing
    };
    ~DBClient2(){
        try
        {
            auto stream = rediscpp::make_stream("localhost", "6379");
            auto response = rediscpp::execute(*stream, "FLUSHALL");
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    };

    void insert(uint64_t count)
    {
        Timer stop_watch;

        try
        {
            auto stream = rediscpp::make_stream("localhost", "6379");

            // Executing command 'SET' N times without getting any response
            for (uint64_t i = 1; i <= count; ++i)
            {
                auto const item = std::to_string(i);
                rediscpp::execute_no_flush(*stream,
                                           "SET", key_pref + item, "some formatted xml stuff that is really long");
            }

            // Flush all
            std::flush(*stream);

            // Getting response for each sent 'SET' request
            for (uint64_t i = 1; i <= count; ++i)
            {
                // this is the only way to clear the response array that I have seen
                rediscpp::value value{*stream};
            }

            // Executing command 'SET' N times without getting any response
            for (uint64_t i = 1; i <= count; ++i)
            {
                auto const item = std::to_string(i);
                rediscpp::execute_no_flush(*stream,
                                           "ZADD", set_key, item, key_pref + item);
            }

            // Flush all
            std::flush(*stream);

            // Getting response for each sent 'SET' request
            for (uint64_t i = 1; i <= count; ++i)
            {
                // this is the only way to clear the response array that I have seen
                rediscpp::value value{*stream};
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    };

    void query(const std::string& start, const std::string& stop)
    {
        // A message printer. The message from a queue.
        auto storeKeys = [this](auto const &value)
        {
            using namespace rediscpp::resp::deserialization;
            std::visit(
                rediscpp::resp::detail::overloaded{
                    [this](bulk_string const &val)
                    {
                        keys.push_back((std::string)val.get());
                    },
                    [](auto const &)
                    {
                        std::cout << "Unexpected value type." << std::endl;
                    }},
                value);
        };

        try
        {
            auto stream = rediscpp::make_stream("localhost", "6379");

            rediscpp::execute_no_flush(*stream, "ZRANGEBYSCORE", "frr.start.index", start, stop);

            // Flush all
            std::flush(*stream);

            // Reading / waiting for a message.
            rediscpp::value value{*stream};

            std::visit(
                rediscpp::resp::detail::overloaded
                {// We're wondered only an array in response. Otherwise, there is an error.
                    [&storeKeys](rediscpp::resp::deserialization::array const &arr)
                    {
                        for (auto const &i : arr.get())
                        {
                            storeKeys(i);
                        }
                    },
                    // Oops. An error in a response.
                    [](rediscpp::resp::deserialization::error_message const &err)
                    {
                        std::cerr << "Error: " << err.get() << std::endl;
                    },
                    // An unexpected response.
                    [](auto const &)
                    {
                        std::cout << "Unexpected value type." << std::endl;
                    }},
                   value.get()
            );
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    };

    void update (const std::string& start, const std::string& stop)
    {
        Timer stop_watch;

        query(start,stop);

        try
        {
            auto stream = rediscpp::make_stream("localhost", "6379");

            // Executing command 'SET' N times without getting any response
            for (const auto key : keys)
            {
                rediscpp::execute_no_flush(*stream,
                                           "SET", key, "some formatted xml stuff that is really long --updated");
            }

            // Flush all
            std::flush(*stream);

            // Getting response for each sent 'SET' request
            for (const auto key : keys)
            {
                // this is the only way to clear the response array that I have seen
                rediscpp::value value{*stream};
            }

            // Executing command 'SET' N times without getting any response
            uint64_t start = 1000000;
            for (const auto key : keys)
            {
                rediscpp::execute_no_flush(*stream,
                                           "ZADD", set_key, std::to_string(start), key);
                start++;
            }

            // Flush all
            std::flush(*stream);

            // Getting response for each sent 'SET' request
            for (const auto key : keys)
            {
                // this is the only way to clear the response array that I have seen
                rediscpp::value value{*stream};
            }

            keys.clear();
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void clear()
    {
        Timer stop_watch;

        query("-inf", "+inf");

        try
        {
            auto stream = rediscpp::make_stream("localhost", "6379");

            for (const auto key : keys)
            {
                rediscpp::execute_no_flush(*stream, "GETDEL", key);
            }

            // Flush all
            std::flush(*stream);

            // Getting response for each sent 'SET' request
            for (const auto key : keys)
            {
                // this is the only way to clear the response array that I have seen
                rediscpp::value value{*stream};
            }

            keys.clear();
        }
        catch (std::exception const &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    std::string key_pref = "frr_";
    std::string set_key = "frr.start.index";
    std::vector<std::string> keys;
};

#endif // __REDIS_CLIENT_H__