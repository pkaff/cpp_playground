#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <iostream>

class BitPattern {
    std::uint64_t expected{};
    std::uint64_t mask{0xFFFFFFFFFFFFFFFF};
public:
    template<std::size_t Size>
    explicit consteval BitPattern(const char (&input)[Size]) {
        size_t curBit = (1 << (Size - 2));
        for (const auto c : input) {
            if (c == 0) {
                return;
            }
            if (c == '1') {
                expected |= curBit;
            } else if (c == '0') {
                // Already set
            } else if (c == 'x' || c == 'X') {
                mask &= ~curBit;
            } else {
                throw std::logic_error("Invalid bitpattern format");
            }
            curBit >>= 1;
        }
    }

    template<typename ValueType>
    constexpr friend bool operator==(ValueType val,
                              const BitPattern& pattern) requires (std::is_unsigned_v<ValueType>) {
        return (val & pattern.mask) == pattern.expected;
    }
};

int main(const int argc, const char* []) {
    static_assert(0b111001u == BitPattern("XXXXX1"));
    return (static_cast<uint32_t>(argc) == BitPattern("XXXXXX1"));
}