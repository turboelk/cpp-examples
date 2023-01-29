#include "get_field.hpp"
#include "lua.hpp"
#include <string>
#include <vector>

#define _head(x) std::get<0>( (x) )
#define _tail(x) std::get<1>( (x) )

slw::internal::cons slw::internal::split_path(const std::string &path, const char separator/* = '.'*/)
{
    std::string h { "" };
    std::size_t i = 0;

    for (; i < path.length(); ++i) {
        const char c = path[i];
        if (separator == c) {
             // break the collection if, and only if, h isn't empty
             //  since an empty h is an indication of multiple separators
            if (h.length())
                break;
             // make sure we don't collect the character (it's a separator)
             continue;
        }

        h += c;
    }

    std::string t { "" };

    // get the remaining string *after* the separator/s,
    //  but if the index is less than the path length,
    //  the remainder is an *empty string*
    if (++i < path.length())
        t = path.substr(i);

    return std::make_tuple(
        h,
        t
    );
}

slw::internal::path::iterator::iterator(const std::string &path, const char separator/* = '.'*/)
    : M_cons(slw::internal::split_path(path, separator))
    , M_separator(separator)
    , M_end(!path.length())
{
}

slw::internal::path::iterator &slw::internal::path::iterator::operator ++()
{
    M_cons = split_path(tail(), M_separator);
    M_end = !tail().length() && !_head(M_cons).length();
    return *this;
}

slw::internal::path::iterator slw::internal::path::iterator::operator ++(int)
{
    path::iterator at = *this;
    ++(*this);
    return at;
}

bool slw::internal::path::iterator::operator ==(const slw::internal::path::iterator &other) const
{
    return _head(M_cons) == _head(M_cons)
            && _tail(M_cons) == _tail(other.M_cons)
            && M_end == other.M_end;
}

bool slw::internal::path::iterator::operator !=(const path::iterator &other) const
{
    return !(*this == other);
}

slw::internal::path::iterator::reference slw::internal::path::iterator::operator *()
{
    return _head(M_cons);
}

slw::internal::path::iterator::reference slw::internal::path::iterator::tail()
{
    return _tail(M_cons);
}

slw::internal::path::path(const std::string &path, const char separator/* = '.'*/)
    : M_end("", separator)
    , M_begin(path, separator)
{
}

slw::internal::path::iterator slw::internal::path::begin()
{
    return M_begin;
}

slw::internal::path::iterator slw::internal::path::end()
{
    return M_end;
}

void slw::internal::touch_path(lua_State *L, const std::string &p, const int idx, const char separator)
{
    slw::internal::path to { p, separator };
    slw::internal::path::iterator at = to.begin();

    // make sure we catch any attempt to index global fields early on
    // LUA_GLOBALSINDEX, et. al. doesn't play very well with pseudo-indices
    lua_getfield(L, idx, (*at).c_str());
    if (!lua_istable(L, -1) && at.tail().length()) {
        lua_pop(L, 1);
        lua_createtable(L, 0, 1);
        lua_setfield(L, idx, (*at).c_str());
        lua_getfield(L, idx, (*at).c_str());
    }

    ++at;

    for (; at != to.end(); ++at) {
        std::string k = *at;
        lua_getfield(L, -1, k.c_str());

        if (!lua_istable(L, -1) && at.tail().length()) {
            lua_pop(L, 1);
            lua_createtable(L, 0, 1);
            lua_setfield(L, -2, k.c_str());
            lua_getfield(L, -1, k.c_str());
        }

        if (lua_gettop(L) > 1)
            lua_remove(L, -2);
    }
}
