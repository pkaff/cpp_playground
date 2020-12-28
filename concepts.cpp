#include <cmath>
#include <concepts>
#include <functional>
#include <vector>

//concept inside parameter list
bool isPowerOf2(std::integral auto i) {
    return i > 0 && (i & (i - 1)) == 0;
}
bool isPowerOf2(std::floating_point auto x) {
    int exponent;
    const float mantissa = std::frexp(x, &exponent);
    return mantissa == 0.5f;
}

//dependent concepts
template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template<typename T>
concept myNumber = arithmetic<T> && sizeof(T) <= 8;

auto getSizeOfNumber(myNumber auto x) {
    return sizeof(x);
}

//requires std::hash to be implemented for T and return size_t
template<typename T>
concept hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

int main() {
    isPowerOf2(2);
    isPowerOf2(2.5f);
    getSizeOfNumber(8.0f);
    getSizeOfNumber(8);
    //getSizeOfNumber(8.0L); //fails to compile since sizeof(long double) > 8
    //static_assert(hashable<std::vector<int>>); //non-hashable types fails assert at compile time
}