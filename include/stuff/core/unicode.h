// Copyright (C) 2019  Tony Walker
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

#ifndef STUFF_UNICODE_H
#define STUFF_UNICODE_H

#include <stuff/core/byte_array.h>
#include <stuff/core/exception.h>
#include <string>

namespace stuff {

    STUFF_DEFINE_EXCEPTION(unicode_error, generic_error);

    //
    // Encoding information for text.
    //
    struct encoding {
        std::string char_set;
        size_t      bom_size;
    };

    //
    // Detect the Byte-Order-Mark (BOM) if present.
    // Only detect recent/common BOM's.
    //
    encoding detect_bom(const byte_array& content);

    //
    // Convert ASCII encoded as UTF-16 or UTF-32 into an 8-bit ASCII string.
    //
    // I occasionally get data from others that is ASCII but was generated on
    // a system or with a language that uses UTF-16, for example. This function
    // does a quick and dirty conversion. It does no language detection. Only
    // use it when you are certain your data is ASCII saved as UTF-16/32.
    // Will work if passed ASCII as 8-bit chars or UTF-8, but there is no point.
    //
    std::string to_8bit_ascii(const byte_array& content);

    // FIXME: Should provide general purpose charset detection and conversion
    // with libicu. Should employ to_8bit_ascii() fast-path.

} // namespace stuff

#endif // STUFF_UNICODE_H
