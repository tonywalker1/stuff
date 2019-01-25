#include <stuff/exception.h>
#include <gtest/gtest.h>

TEST(ExceptionTests, DefineException)
{
    // define a new exception
    STUFF_DEFINE_EXCEPTION(stuff_error, stuff::generic_error);

    // should be compatible with base classes
    EXPECT_THROW(throw stuff_error {""}, std::exception);
    EXPECT_THROW(throw stuff_error {""}, std::runtime_error);
    EXPECT_THROW(throw stuff_error {""}, stuff::generic_error);
    EXPECT_THROW(throw stuff_error {""}, stuff_error);
}

TEST(ExceptionTests, ThrowMacro)
{
    // throwing should actually throw
    // the error caught should match the error thrown
    EXPECT_THROW(STUFF_THROW(stuff::generic_error, ""), stuff::generic_error);

    // the message caught should match the message thrown
    try {
        STUFF_THROW(stuff::generic_error, "the answer is {}", 42);
    }
    catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "stuff::generic_error: the answer is 42");
    }
}

TEST(ExceptionTests, ToString)
{
    // the message caught should match the message thrown
    try {
        STUFF_THROW(stuff::generic_error, "the answer is {}", 42);
    }
    catch (const std::exception& e) {
        EXPECT_EQ(stuff::to_string(e),
            "stuff::generic_error: the answer is 42");
    }

    // the message caught should match the message thrown
    try {
        try {
            STUFF_THROW(stuff::generic_error, "the answer is {}", 42);
        }
        catch (const std::exception& e) {
            EXPECT_EQ(stuff::to_string(e),
                "stuff::generic_error: the answer is 42");
            STUFF_NESTED_THROW(stuff::generic_error,
                "on to a higher level");
        }
    }
    catch (const std::exception& e) {
        EXPECT_EQ(stuff::to_string(e),
            "stuff::generic_error: on to a higher level\n"
            "  stuff::generic_error: the answer is 42");
    }
}

TEST(ExceptionTests, AssertMacro)
{
    // throwing should actually throw
    // the error caught should match the error thrown
    EXPECT_NO_THROW(STUFF_ASSERT(1 == 1, stuff::generic_error, ""));
    EXPECT_THROW(STUFF_ASSERT(1 == 0, stuff::generic_error, ""),
        stuff::generic_error);

    // the message caught should match the message thrown
    try {
        STUFF_ASSERT(1 == 0, stuff::generic_error, "the answer is {}", 42);
    }
    catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "stuff::generic_error: the answer is 42");
    }
}

TEST(ExceptionTests, PreconditionMacro)
{
    // throwing should actually throw
    // the error caught should match the error thrown
    EXPECT_NO_THROW(STUFF_EXPECTS(1 == 1, stuff::generic_error, ""));
    EXPECT_THROW(STUFF_EXPECTS(1 == 0, stuff::generic_error, ""),
        stuff::generic_error);

    // the message caught should match the message thrown
    try {
        STUFF_EXPECTS(1 == 0, stuff::generic_error, "the answer is {}", 42);
    }
    catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "stuff::generic_error: the answer is 42");
    }
}

TEST(ExceptionTests, PostconditionMacro)
{
    // throwing should actually throw
    // the error caught should match the error thrown
    EXPECT_NO_THROW(STUFF_ENSURES(1 == 1, stuff::generic_error, ""));
    EXPECT_THROW(STUFF_ENSURES(1 == 0, stuff::generic_error, ""),
        stuff::generic_error);

    // the message caught should match the message thrown
    try {
        STUFF_ENSURES(1 == 0, stuff::generic_error, "the answer is {}", 42);
    }
    catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "stuff::generic_error: the answer is 42");
    }
}
