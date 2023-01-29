#include <iostream>
#include <string>

#include "lua.hpp"
#include "debug_stack.hpp"
#include "get_field.hpp"

int main(int argc, char **argv)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dostring(L,
        "person = {}\n"
        "person.age = 27\n"
        "person.employed = false\n"
        "person.name = 'Marcus Skarpsvärd'\n"
        "person.has = {}\n"
        "person.has.home = false\n"
        "person.has.problems = 'Too many to count!'\n"
    );

    std::string input;

    do {
        std::cout << "Set path separator: ";
        std::getline(std::cin, input);
    } while (input.length() != 1);

    char separator = input[0];

    do {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.length() > 4 && input.substr(0, 4) == "set ") {
            separator = input[4];
            input = "";
            continue;
        }

        slw::internal::touch_path(L, input, LUA_GLOBALSINDEX, separator);
        lua_pop(L, lua_gettop(L));
    } while ("exit" != input);
}

