// MIT License
//
// Copyright (c) 2019 Tony Walker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
