#ifndef GET_FIELD_HPP
#define GET_FIELD_HPP

#include <string>
#include <tuple>

struct lua_State;

namespace slw {
namespace internal {

typedef std::tuple<std::string, std::string> cons;

cons split_path(const std::string &, const char separator = '.');

class path {
public:
    class iterator : public std::iterator<
            std::forward_iterator_tag,
            std::string> {
        const char M_separator;
        cons M_cons;
        bool M_end;
public:
        explicit iterator(const std::string &path = "", const char separator = '.');
        iterator &operator ++();
        iterator operator ++(int);
        bool operator ==(const iterator &other) const;
        bool operator !=(const iterator &other) const;
        reference operator *();

        reference tail();
    };

    explicit path (const std::string &path, const char separator = '.');

    iterator begin();
    iterator end();

private:
    const iterator M_end;
    iterator M_begin;
};

void touch_path(lua_State *, const std::string &path, const int idx, const char separator = '.');

}/*ns internal*/
}/*ns slw*/

#endif//GET_FIELD_HPP
