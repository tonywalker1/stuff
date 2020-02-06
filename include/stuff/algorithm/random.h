// Copyright (C) 2019, 2020  Tony Walker
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

#ifndef STUFF_ALGORITHM_RANDOM_H
#define STUFF_ALGORITHM_RANDOM_H

#include <stuff/core/exception.h>
#include <chrono>
#include <random>

namespace stuff::algorithm {

    STUFF_DEFINE_EXCEPTION(random_error, generic_error);

    //
    // Generate pseudorandom numbers in a given range. See random_integer and
    // random_real below.
    // Range:
    //   integer types -> [lower:upper]
    //   real types    -> [lower:upper)
    // Invariants:
    //   1) lower must be less than upper.
    // Examples:
    //   random_integer<int> r(1, 9);
    //   random_real<double> r(-1.0, 1.0);
    //
    template <typename T, typename Distribution,
        typename Engine = std::default_random_engine>
    class random_number {
    public:

        random_number(T lower, T upper)
        : m_distribution(lower, upper),
          m_engine(static_cast<unsigned>(
              std::chrono::system_clock::now().time_since_epoch().count()))
        {
            STUFF_EXPECTS(lower < upper,
                random_error,
                "bad range for random_number: ({}, {})", lower, upper);
        }

        inline T operator()(void) noexcept
        {
            return m_distribution(m_engine);
        }

    private:

        Distribution m_distribution;
        Engine       m_engine;

    }; // class random_number

    template <typename T>
    using random_integer = random_number<T, std::uniform_int_distribution<T>>;

    template <typename T>
    using random_real = random_number<T, std::uniform_real_distribution<T>>;

} // namespace stuff::algorithm

#endif // STUFF_ALGORITHM_RANDOM_H
