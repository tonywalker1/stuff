# MIT License
#
# Copyright (c) 2019 Tony Walker
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# create_benchmark() simplifies building benchmark tests.
#
# Arguments:
#   NAME    Name of the benchmark executable (REQUIRED).
#   SRC     List of source files (.cpp) for the benchmark (OPTIONAL).
#   LIBS    List of libraries to link against (REQUIRED).
#
# Example:
# create_benchmark(NAME something_benchmarks SRC something.cpp LIBS ${SOME_LIBS})

function(create_benchmark)

    cmake_parse_arguments(BENCHMARK "" "NAME" "SRC;LIBS" ${ARGN})

    add_executable(${BENCHMARK_NAME}
        ${BENCHMARK_SRC}
    )

    target_link_libraries(${BENCHMARK_NAME}
        ${BENCHMARK_LIBS}
    )

    add_custom_target(RUN_${BENCHMARK_NAME}
        DEPENDS
            ${BENCHMARK_NAME}
        COMMAND
            ${BENCHMARK_NAME}
                --benchmark_repetitions=10
                --benchmark_report_aggregates_only=true
    )
    add_dependencies(benchmark RUN_${BENCHMARK_NAME})

endfunction(create_benchmark)
