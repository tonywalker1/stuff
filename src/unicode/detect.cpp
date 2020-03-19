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

#include <cstring>
#include <stuff/unicode/detect.h>

namespace stuff::unicode {

    encoding detect_bom(const container::byte_array& content)
    {
        // Always, check for longer encodings first!
        if ((content.size() >= 4)
            && (memcmp(content.data(), "\xFF\xFE\x00\x00", 4) == 0)) {
            return encoding {"UTF-32LE", 4};
        }
        if ((content.size() >= 4)
            && (memcmp(content.data(), "\x00\x00\xFE\xFF", 4) == 0)) {
            return encoding {"UTF-32BE", 4};
        }
        if ((content.size() >= 3)
            && (memcmp(content.data(), "\xEF\xBB\xBF", 3) == 0)) {
            return encoding {"UTF-8", 3};
        }
        if ((content.size() >= 2)
            && (memcmp(content.data(), "\xFF\xFE", 2) == 0)) {
            return encoding {"UTF-16LE", 2};
        }
        if ((content.size() >= 2)
            && (memcmp(content.data(), "\xFE\xFF", 2) == 0)) {
            return encoding {"UTF-16BE", 2};
        }
        // otherwise, we don't know...
        return encoding {"unknown", 0};
    }

} // namespace stuff::unicode
