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

#ifndef STUFF_IO_FILESYSTEM_H
#define STUFF_IO_FILESYSTEM_H

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <ios>
#include <iterator>
#include <string>
#include <string_view>
#include <stuff/core/byte_array.h>
#include <stuff/core/exception.h>
#include <utility>

// Use Boost instead of std::filesystem for now.
namespace fs = boost::filesystem;

namespace stuff::io {

    STUFF_DEFINE_EXCEPTION(filesystem_error, stuff::core::generic_error);

    // Alias for a vector of paths.
    using path_array = std::vector<fs::path>;

    // File compression types for functions below.
    enum class compression_type { none, bzip2, gzip };

    namespace detail {

        //
        template <typename device_t, typename stream_t>
        class basic_stream_wrapper {
        public:
            explicit basic_stream_wrapper(
                const char* filename, std::ios_base::openmode mode)
            : m_device {filename, mode}, m_stream {}
            {
            }

            inline operator bool() { return m_stream.good(); }

            [[nodiscard]] inline bool good() const noexcept
            {
                return m_stream.good();
            }

            inline stream_t& stream() { return m_stream; }

            inline void noskipws() { std::noskipws(m_stream); }

            inline void enable_compression(compression_type ct)
            {
                switch (ct) {
                case compression_type::none:
                    break;
                case compression_type::bzip2:
                    m_stream.push(boost::iostreams::bzip2_decompressor {});
                    break;
                case compression_type::gzip:
                    m_stream.push(boost::iostreams::gzip_decompressor {});
                    break;
                }
            }

            inline void connect() { m_stream.push(m_device); }

            inline std::string& getline(std::string& line)
            {
                std::getline(m_stream, line);
                return line;
            }

        protected:
            device_t m_device;
            stream_t m_stream;

        }; // struct basic_stream_wrapper

        //
        class istream_wrapper
        : public basic_stream_wrapper<boost::iostreams::file_source,
              boost::iostreams::filtering_istream> {
        public:
            istream_wrapper(const char* filename, std::ios_base::openmode mode);

            istream_wrapper(
                const fs::path& filename, std::ios_base::openmode mode);

        }; // struct istream_wrapper

        //
        template <typename C>
        C read_entire_file(const char* filename, compression_type ct,
            std::ios_base::openmode mode)
        {
            C result;

            boost::iostreams::file_source       src {filename, mode};
            boost::iostreams::filtering_istream is;
            std::noskipws(is);
            switch (ct) {
            case compression_type::none:
                break;
            case compression_type::bzip2:
                is.push(boost::iostreams::bzip2_decompressor {});
                break;
            case compression_type::gzip:
                is.push(boost::iostreams::gzip_decompressor {});
                break;
            }
            is.push(src);

            result.insert(result.end(), std::istream_iterator<char>(is),
                std::istream_iterator<char>());

            return result;
        }

    } // namespace detail


    // Read an entire file as text or binary data.
    core::byte_array read_as_bytes(
        const fs::path& filename, compression_type ct = compression_type::none);

    std::string read_as_text(
        const fs::path& filename, compression_type ct = compression_type::none);

    // Read a text file line-by-line.
    // f() must accept each line as a const std::string& or std::string_view.
    template <typename Function>
    inline void read_as_lines(
        const fs::path& filename, compression_type ct, Function f)
    {
        detail::istream_wrapper file {filename, std::ifstream::in};
        file.noskipws();
        file.enable_compression(ct);
        file.connect();

        std::string line;
        while (file) {
            file.getline(line);
            f(line);
        }
    }

    // Apply f() to each directory in dir.
    // f() must be a unary function taking a directory_entry (or path).
    template <typename Function>
    inline void for_each_directory(const fs::path& dir, Function f)
    {
        for (const auto& entry : fs::directory_iterator {dir}) {
            if (fs::is_directory(entry)) {
                f(entry);
            }
        }
    }

    // Apply f() to each file in dir.
    // f() must be a unary function taking a path.
    template <typename Function>
    inline void for_each_file(const fs::path& dir, Function f)
    {
        for (const auto& entry : fs::directory_iterator {dir}) {
            if (fs::is_regular_file(entry)) {
                f(entry);
            }
        }
    }

    // List all files in dir.
    // The returned list is not sorted.
    path_array list_files(const fs::path& dir);

    // Return the home directory for the current user.
    fs::path home_dir();

    // Given a path starting with a tilde (~), replace with the current user's
    // home directory.
    fs::path expand_home(std::string_view p);

} // namespace stuff::io

#endif // STUFF_IO_FILESYSTEM_H
