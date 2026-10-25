include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test_money.cpp)

target_link_libraries(run_tests gtest_main core)

include(GoogleTest)
gtest_discover_tests(run_tests)