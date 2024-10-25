#include <gtest/gtest.h>
#include <stdexcept>
#include "six.h"
#include <iostream>

TEST(InitTest, Constr12) {
    Six const first(1, 4);
    Six const second({4});
    ASSERT_TRUE(first.equal(second));
}
TEST(InitTest, Constr13) {
    Six first(1, 4);
    Six second("4");
    ASSERT_TRUE(first.equal(second));
}

TEST(InitTest, Constr14) {
    Six const first(1, 4);
    Six tmp(1, 4);
    Six const second(tmp);
    ASSERT_TRUE(first.equal(second));
}

TEST(InitTest, Constr15) {
    Six const first(1, 4);
    Six tmp(1, 4);
    Six const second(std::move(tmp));
    ASSERT_TRUE(first.equal(second));
}

TEST(CompareTest, Equal) {
    Six const first("2");
    Six const second("2");

    ASSERT_TRUE(first.equal(second));
}

TEST(CompareTest, more) {
    Six const first("4");
    Six const second("2");

    ASSERT_TRUE(first.more(second));
}

TEST(CompareTest, less) {
    Six const first("1");
    Six const second("2");

    ASSERT_TRUE(first.less(second));
}


TEST(ArithmeticTest, sum) {
    Six const first("1");
    Six const second("2");
    Six const res("3");

    ASSERT_TRUE(res.equal(first.sum(second)));
}

TEST(ArithmeticTest, substract) {
    Six first("3");
    Six second("2");
    Six res("1");

    ASSERT_TRUE(res.equal(first.subtract(second)));
}

TEST(InitTest_Death, ConstrListEmpty) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            Six tmp({});  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("List is empty", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(InitTest_Death, ConstrListInvalid) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            Six tmp({10});  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("List contains invalid data", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(InitTest_Death, ConstrStringEmpty) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            Six tmp("");  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("String is empty", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(ArithmeticTest_Death, SubstractInvalid) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            Six tmp("3");
            Six tmp2("5");
            tmp.subtract(tmp2);  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Cannot subtract", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}