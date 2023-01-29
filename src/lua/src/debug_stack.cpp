#include "debug_stack.hpp"
#include "lua.hpp"

#include <iostream>
#include <string>

void debug_stack(lua_State *L)
{
    int top = lua_gettop(L);

    for (int i = -1; i >= -top; --i) {
        int type = lua_type(L, i);
        std::string name = lua_typename(L, type);
        std::cout << std::to_string(i) << ": <"
                  << name << " (" << std::to_string(type) << ")> ";

         switch (type) {
         case LUA_TBOOLEAN:
             std::cout << " : " << (lua_toboolean(L, i)? "true": "false");
             break;
         case LUA_TNUMBER:
             std::cout << " : " << std::to_string(lua_tonumber(L, i));
             break;
         case LUA_TSTRING:
             std::cout << " : " << lua_tostring(L, i);
             break;
        }

         std::cout << std::endl;
    }
}
