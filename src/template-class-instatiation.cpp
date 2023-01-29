#include <iostream>
#include <string>
#include <assert.h>

std::size_t id()
{
  static std::size_t i = 0;
  return ++i;
}

template<size_t L>
constexpr std::size_t c_fnv1a(const char (&str)[L], std::size_t n = L - 2)
{
    return n
        ? (c_fnv1a(str, n - 1) ^ str[n]) * (std::size_t)1099511628211
        : ((std::size_t)14695981039346656037U ^ str[n]) * (std::size_t)1099511628211;
}

template<std::size_t I>
struct prop {
    constexpr std::size_t get()
    { return I;
    }

    operator std::size_t()
    { return get();
    }

    static std::size_t id()
    { static std::size_t this_id = ::id();
        return this_id;
    }

    const char *str;
};

#define type(T, S) \
	typedef prop<c_fnv1a<sizeof(S)>(S)> T; \
	T instance_of_##T { S }

type(type_a, "Hello, world!");
type(type_b, "CROCODILE DUNDEE MAN");

int main(int argc, char **argv)
{
    std::size_t type_a_id = type_a::id();
    std::size_t type_b_id = type_b::id();
    std::cout << "type_a_id := " << std::to_string(type_a_id) << std::endl;
    std::cout << "type_b_id := " << std::to_string(type_b_id) << std::endl;
}
