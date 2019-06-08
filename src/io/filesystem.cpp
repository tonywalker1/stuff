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

#include <stuff/io/filesystem.h>
#include <stuff/core/exception.h>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iterator>
#include <string>
#include <string_view>

namespace stuff {

    byte_array read_as_bytes(const fs::path& filename)
    {
        fs::ifstream file {filename, std::ifstream::binary};
        STUFF_EXPECTS(file,
            filesystem_error,
            "failed to open \"{}\"", filename.native());
        std::noskipws(file);
        return byte_array(std::istream_iterator<char>(file),
            std::istream_iterator<char>());
    }

    std::string read_as_text(const fs::path& filename)
    {
        fs::ifstream file {filename};
        STUFF_EXPECTS(file,
            filesystem_error,
            "failed to open \"{}\"", filename.native());
        std::noskipws(file);
        return std::string {std::istream_iterator<char>(file),
            std::istream_iterator<char>()};
    }

    fs::path home_dir()
    {
        const char* env = std::getenv("HOME");
        STUFF_ENSURES(env != nullptr,
            filesystem_error,
            "home directory lookup failed");
        return fs::path(env);
    }

    fs::path expand_home(const fs::path& p)
    {
        try {
            if (p.size() == 0) {
                return fs::path {p};
            }
            else if (p.native().front() == '~') {
                return home_dir().concat(&p.native()[1]);
            }
            else {
                return fs::path {p};
            }
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(filesystem_error,
                "failed to expand \"{}\"", p.native());
        }
    }

} // namespace stuff
