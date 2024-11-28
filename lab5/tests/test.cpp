#include "DynamicArray.hpp"
#include "MemoryResource.h"
#include <gtest\gtest.h>
#include <memory>


TEST(BaseArray, ArrayInt) {
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<int> int_array(&memory_resource);

    int array[25];
    for (int i = 0; i < 25; ++i) {
        array[i] = i;
    }

    for (int i = 0; i < 25; ++i) {
        int_array.push_back(i);
    }

    for (auto const it : int_array) {
        ASSERT_EQ(it, array[it]);
    }

}

TEST(stdArray, ArrayPair) {
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<std::pair<int, float>> complex_array(&memory_resource);
    complex_array.push_back(std::make_pair(1, 3.6));

    auto pair = std::make_pair(1, 3.6f);
    ASSERT_EQ(pair.first, complex_array[0].first);
    ASSERT_EQ(pair.second, complex_array[0].second);

}

TEST(stdArray, ArrayString) {
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<std::pmr::string> string_array(&memory_resource);
    string_array.push_back(std::pmr::string("nepadaem"));

    auto str = std::pmr::string("nepadaem");
    ASSERT_EQ(str, string_array[0]);
}

TEST(CustomArray, ArrayPerson) {
    struct Person {
        std::string name;
        int age;
        std::string address;

        Person(std::string name, const int age, std::string address)
            : name(std::move(name)), age(age), address(std::move(address)) {}
    };
    FixedBlockMemoryResource memory_resource(1024);
    DynamicArray<Person> person_array(&memory_resource);
    person_array.push_back(Person("nepadaem", 12, "nepadaem3"));

    auto person = Person("nepadaem", 12, "nepadaem3");
    ASSERT_EQ(person.name, person_array[0].name);
    ASSERT_EQ(person.age, person_array[0].age);
    ASSERT_EQ(person.address, person_array[0].address);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}