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

#ifndef STUFF_UNICODE_DETECT_H
#define STUFF_UNICODE_DETECT_H

#include <string>
#include <stuff/container/byte_array.h>

namespace stuff::unicode {

    //
    // Encoding information for text.
    //
    struct encoding {
        std::string char_set;
        size_t      bom_size;
    };

    //
    // Detect the Byte-Order-Mark (BOM) if present.
    // Notes:
    // - only detects recent/common BOM's
    //
    encoding detect_bom(const container::byte_array& content);

} // namespace stuff::unicode

#endif // STUFF_UNICODE_DETECT_H
