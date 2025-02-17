file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(postfix ${srcs} ${hdrs} "sample_polynom.cpp" "polynom.h" "polynom.cpp" "list.h"  "sample_list.cpp")
