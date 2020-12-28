#include <typetraits>

export module math;

template<std::is_arithmetic T>
export T math(T i) {
    return i + 3;
}