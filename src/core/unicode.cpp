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

#include <stuff/core/unicode.h>
#include <cstring>

namespace stuff {

    encoding detect_bom(const byte_array& content)
    {
        // Always, check for longer encodings first!
        if ((content.size() >= 4)
            && (memcmp(content.data(), "\xFF\xFE\x00\x00", 4) == 0)) {
            return encoding {"UTF-32LE", 4};
        }
        else if ((content.size() >= 4)
            && (memcmp(content.data(), "\x00\x00\xFE\xFF", 4) == 0)) {
            return encoding {"UTF-32BE", 4};
        }
        else if ((content.size() >= 3)
            && (memcmp(content.data(), "\xEF\xBB\xBF", 3) == 0)) {
            return encoding {"UTF-8", 3};
        }
        else if ((content.size() >= 2)
            && (memcmp(content.data(), "\xFF\xFE", 2) == 0)) {
            return encoding {"UTF-16LE", 2};
        }
        else if ((content.size() >= 2)
            && (memcmp(content.data(), "\xFE\xFF", 2) == 0)) {
            return encoding {"UTF-16BE", 2};
        }
        else {
            return encoding {"unknown", 0};
        }
    }

    std::string to_ascii(const byte_array& content)
    {
        std::string tmp;
        encoding enc {detect_bom(content)};
        for (size_t idx = enc.bom_size; idx < content.size(); ++idx) {
            unsigned char val = content[idx];
            if ((32 <= val) && (val <= 126))
                tmp += val;
            else if (val == '\n')
                tmp += val;
            else if (val == '\r')
                continue;  // skip returns
            else if (val == 0)
                continue;  // skip embedded zeros (e.g., UTF-16 encodings)
            else
                STUFF_THROW(unicode_error,
                    "illegal char \'{}\' at position {}", int(val), idx);
        }
        return tmp;
    }

} // namespace stuff
