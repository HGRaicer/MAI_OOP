#include <iostream>

#include "DynamicArray.hpp"
#include "MemoryResource.h"
struct Person {
    std::string name;
    int age;
    std::string address;

    Person(std::string name, const int age, std::string address)
        : name(std::move(name)), age(age), address(std::move(address)) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age << ", Address: " << person.address;
        return os;
    }
};

int main() {

    FixedBlockMemoryResource memory_resource(2048);
    DynamicArray<int> int_array(&memory_resource);


    for (int i = 0; i < 25; ++i) {
        int_array.push_back(i);
    }

    for (auto const it : int_array) {
        std::cout << it << " ";
    }
    std::cout << "\n";

    DynamicArray<float> float_array(&memory_resource);
    std::cout << float_array.get_size() << std::endl;;
    float_array.push_back(3.2f);
    std::cout << float_array.get_size() << std::endl;;
    float_array.push_back(6.6f);
    std::cout << float_array.get_size() << std::endl;;

    DynamicArray<std::pair<int, float>> complex_array(&memory_resource);
    complex_array.push_back(std::make_pair(1, 3.6));
    complex_array.push_back(std::make_pair(3, 3.3));

    DynamicArray<std::pmr::string> string_array(&memory_resource);
    string_array.push_back(std::pmr::string("nepadaem"));
    string_array.push_back(std::pmr::string("nepadaem22"));

    DynamicArray<Person> Person_array(&memory_resource);
    Person_array.push_back(Person("nepadaem", 22, "nepadaem22()"));

    for (auto const &it : Person_array) {
        std::cout << it << " ";
    }
    std::cout<<std::endl;
    for (auto const &it : string_array) {
        std::cout << it << " ";
    }
    std::cout<<std::endl;
    for (auto const it : float_array) {
        std::cout << it << " ";
    }
    std::cout<<std::endl;
    for (auto const &it : complex_array) {
        std::cout << get<0>(it) << " "<< get<1>(it) << " ";
    }
    return 0;
}

