#ifndef __WORLD_H__
#define __WORLD_H__

#include <flecs.h>
#include <iostream>
#include <string>

struct simple_module
{
    // Define types inside module scope. This is not mandatory, but ensures
    // that their fully qualified Flecs name matches the C++ type name. It also
    // ensures that type names cannot clash between modules.

    struct Xml
    {
        std::string resource;
    };

    struct StartTime
    {
        uint64_t start_time;
    };

    simple_module(flecs::world &ecs)
    {
        /* Register module with world */
        ecs.module<simple_module>();

        /* Register system */
        ecs.system<Xml, StartTime>("Move")
            .each([](flecs::entity e, Xml& p, const StartTime& v) {    
                e.destruct();
            });        
    }
};

#endif // __WORLD_H__