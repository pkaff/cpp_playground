#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ranges>

struct User {
    std::string name;
    int age;
};

std::vector<User> users{{"name1", 10},
                        {"name2", 20},
                        {"name3", 30}};

const std::vector<User> constUsers{{"name1", 10},
                                   {"name2", 20},
                                   {"name3", 30}};
bool underage(const User& user) {
    return user.age < 18;
}

int main() {
    //Sorting with ranges
    auto sortByAge = [](auto& lhs, auto& rhs) {
        return lhs.age < rhs.age;
    };

    std::sort(users.begin(), users.end(), sortByAge); //previously required begin and end explicitly
    std::ranges::sort(users, sortByAge); //ranges enbles this directly
    std::ranges::sort(users, std::less{}, &User::age); //projections gets rid of the comparator lambda

    //Filtering const vector
    std::cout << "Filtering using iterators:" << std::endl;
    std::vector<User> filteredUsers;
    std::copy_if(users.begin(), users.end(), std::back_inserter(filteredUsers), std::not_fn(underage)); //copy if not satisfies underage
    std::transform(filteredUsers.begin(), filteredUsers.end(), std::ostream_iterator<int>(std::cout, "\n"), [](const auto& user) { return user.age; }); //print each user

    std::cout << "Filtering using concepts:" << std::endl;
    for (const auto& age : constUsers
        | std::views::filter(std::not_fn(underage))
        | std::views::transform([](const auto& user) { return user.age; })) {
        std::cout << age << std::endl;
    }

    //Generating ranges:
    //iota generates the range [0, 10)
    for (auto i : std::views::iota(0, 10)) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    //iota without end range is a lazy generator from which we can further constrain using the take concept
    for (auto i : std::views::iota(0) | std::views::take(9)) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}