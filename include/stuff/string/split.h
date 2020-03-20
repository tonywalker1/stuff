//
// Copyright (C) 2019-2020  Tony Walker
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <string>
#include <string_view>
#include <stuff/container/string_array.h>

#ifndef STUFF_STRING_SPLIT_H
    #define STUFF_STRING_SPLIT_H

namespace stuff::string {

    //
    // Non-owning string tokenizer (i.e., split a string into parts).
    //
    // Given a string and a separator, next() divides the string into a head
    // and tail: head is the portion before the separator and tail is the
    // portion after.
    //
    // Compared to the standard C/C++ functions (e.g., strtok) for tokenizing a
    // string, this class is safe but still powerful and high-performance.
    // However, for a simpler way to split a string (and examples of how to
    // use this class, see:
    //   split_string(std::string_view, char, Function)
    // and
    //   split_string(std::string_view, char)
    // below.
    //
    class string_tokenizer {
    public:
        //
        // Construct an instance that will tokenize view.
        //
        // The string to which view points, must outlive this instance of
        // string_tokenizer.
        //
        explicit string_tokenizer(std::string_view view);

        //
        // Split the string into a head and tail by finding the first use of
        // the separator (sep).
        //
        std::string_view next(char sep = ' ');

        //
        // Has the entire string been tokenized?
        //
        [[nodiscard]] inline bool is_done() const noexcept { return m_is_done; }
        [[nodiscard]] inline explicit operator bool() const noexcept
        {
            return !m_is_done;
        }
        [[nodiscard]] inline bool operator!() const noexcept
        {
            return m_is_done;
        }

        //
        // The current head token; next() should be called for a valid result.
        //
        [[nodiscard]] inline std::string_view head() const noexcept
        {
            return m_head;
        }

        //
        // The current head token; next() should be called for a valid result.
        //
        [[nodiscard]] inline std::string_view tail() const noexcept
        {
            return m_tail;
        }

    private:
        bool             m_is_done;
        std::string_view m_head;
        std::string_view m_tail;

    }; // class string_tokenizer

    //
    // Using the given separator, tokenize a string and call f() on each token.
    // f() must take a std::string_view. Note: Non-owning.
    //
    // Parameters:
    //   view  String to tokenize.
    //   sep   Separator that divides each token.
    //   f     Function to call on each token.
    //
    template <typename Function>
    inline void split_string(std::string_view view, char sep, Function f)
    {
        string_tokenizer stok {view};
        do {
            f(stok.next(sep));
        } while (stok);
    }

    //
    // Using the given separator, tokenize the string and return each token in
    // a stuff::core::string_view_array. Note: Non-owning on input and output!!!
    // Of the methods to tokenize a string, this is the slowest.
    //
    // Parameters:
    //   view  String to tokenize.
    //   sep   Separator that divides each token.
    //
    // Returns:
    //   A string_view_array containing each token.
    //
    [[nodiscard]] container::string_view_array split_string(
        std::string_view view, char sep);

} // namespace stuff::string

#endif // STUFF_STRING_SPLIT_H
