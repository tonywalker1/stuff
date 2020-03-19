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

#include <stuff/core/string.h>

namespace stuff::core {

    string_tokenizer::string_tokenizer(std::string_view view)
    : m_is_done {false}, m_tail {view}
    {
    }

    std::string_view string_tokenizer::next(char sep)
    {
        if (m_is_done) {
            m_head = std::string_view {};
            return m_head;
        }

        auto pos = m_tail.find(sep);
        if (pos == std::string_view::npos) {
            m_is_done = true;
            m_head    = m_tail;
            m_tail    = std::string_view {};
        }
        else {
            m_head = m_tail.substr(0, pos);
            m_tail.remove_prefix(pos + 1);
        }
        return m_head;
    }

    container::string_view_array split_string(std::string_view view, char sep)
    {
        container::string_view_array result;
        string_tokenizer             stok {view};
        do {
            result.emplace_back(stok.next(sep));
        } while (stok);
        return result;
    }

} // namespace stuff::core
