#include <iostream>
#include <string>
#include <assert.h>

template<typename T>
struct Property {
  typedef T                        reference_type;
  typedef Property<reference_type> this_type;
  const reference_type &M_ref;

  const reference_type &get()
  {
    return M_ref;
  }

  this_type &operator =(const reference_type &r)
  {
    return *new (this) this_type { r };
  }
};

int main(int argc, char **argv)
{
#define DEFAULT 5
  typedef int type;
  typedef Property<type> P;

  type a = DEFAULT;
  type b = DEFAULT + 1;

  P stack_view { a };
  P &heap_view = *new P { a };

  assert(&a == &stack_view.get());
  assert(&a == &heap_view.get());

  stack_view = b;
  heap_view = b;
  
  assert(&b == &stack_view.get());
  assert(&b == &heap_view.get());
}
