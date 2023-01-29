#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

template <typename Number>
struct _A { // Both storage types, both constructors
  union {
    const Number v[3];
    struct { const Number q, r, s; };
  };

  _A(Number q_, Number r_): v{q_, r_, -q_ - r_} {}
  _A(Number q_, Number r_, Number s_): v{q_, r_, s_} {}

  Number length()
  {
    return (Number) ((abs(q) + abs(r) + abs(r)) / 2);
  }
};

template <typename Number>
struct _B {
	Number x;
	Number y;

	_B() : x(0), y(0) {}
	_B(Number x_, Number y_) : x(x_), y(y_) {}
};

template <typename Number>
bool operator ==(const _A<Number> &a, const _A<Number> &b)
{
	return a.q == b.q && a.r == b.r;
}

template <typename Number>
bool operator ==(const _B<Number> &a, const _B<Number> &b)
{
	return a.x == b.x && a.y == b.y;
}

template <typename Number>
bool operator ==(const _A<Number> &a, const _B<Number> &b)
{
	return a.q == b.x && a.r == b.y;
}

template <typename Number>
bool operator ==(const _B<Number> &a, const _A<Number> &b)
{
	return operator ==(b, a);
}

int main(int argc, char **argv)
{
	typedef _A<int> A;
	typedef _B<int> B;

#define left 27
#define right (int)0xDEADB00B

	A a { left, right };
	B b = * (B *) (void *) &a;

	assert(a == b);
	assert(b == a);
  assert(b.x == left && b.y == right);
}
