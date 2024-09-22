#include <stdexcept>
#include <gtest/gtest.h>
#include "../include/number1.h"

TEST(BasicTest, BasicTest_01) {
    constexpr int start = 2, end = 7;
    EXPECT_EQ(how_one_in_cons(start, end), 11);
}

TEST(BasicTest, BasicTest_02) {
    constexpr int start = 2, end = 11;
    EXPECT_EQ(how_one_in_cons(start, end), 19);
}

TEST(BasicTest, BasicTest_03) {
    constexpr int start = 0, end = 100;
    EXPECT_EQ(how_one_in_cons(start, end), 319);
}
TEST(BasicTest, BasicTest_04) {
    constexpr int start = 0, end = 0;
    EXPECT_EQ(how_one_in_cons(start, end), 0);
}

TEST(InvalidArgsTest_Death, InvalidArgsTest_01) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            how_one_in_cons(7, 2);  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Invalid arguments entered(must be start < end and start > 0 and end > 0)", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(InvalidArgsTest_Death, InvalidArgsTest_02) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            how_one_in_cons(-1, 2);  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Invalid arguments entered(must be start < end and start > 0 and end > 0)", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(InvalidArgsTest_Death, InvalidArgsTest_03) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            how_one_in_cons(-20, -5);  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Invalid arguments entered(must be start < end and start > 0 and end > 0)", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(InvalidArgsTest_Death, InvalidArgsTest_04) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            how_one_in_cons(2, -7);  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::invalid_argument& e) {  // ловим std::invalid_argument
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Invalid arguments entered(must be start < end and start > 0 and end > 0)", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::invalid_argument);  // проверяем, что выброшено именно std::invalid_argument
}

TEST(OverflowedAnsTest_Death, OverflowedAnsTest_01) {
    // этот тест проверяет, что ожидаемое исключение выбрасывается
    EXPECT_THROW({
        try {
            how_one_in_cons(2, (INT_MAX - 1));  // здесь выполняется код, который должен выбросить исключение
        }
        catch (const std::overflow_error& e) {  // ловим std::overflow_error
            // этот блок проверяет, что сообщение исключения корректно
            EXPECT_STREQ("Integer type overflowed(Answer is too big)", e.what());  // проверка на текст сообщения
            throw;  // повторно выбрасываем исключение, чтобы EXPECT_THROW сработал
        }
    }, std::overflow_error);  // проверяем, что выброшено именно std::overflow_error
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}