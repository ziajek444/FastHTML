# CMakeList.txt : CMake project for FastHTML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

project ("FastHTML")

# Add source to this project's executable.
add_executable (FastHTML "src/FastHTML.cpp" "src/mian.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FastHTML PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# - - 

# Test
enable_testing()

add_executable(
  ${PROJECT_NAME}-ut
  "src/tests.cpp"
  "src/FastHTML.cpp"
)
target_link_libraries(
  ${PROJECT_NAME}-ut
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
# - - 