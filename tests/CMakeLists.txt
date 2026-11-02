include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test_money.cpp test_roulette_number.cpp test_player.cpp test_casinobank.cpp test_table.cpp test_bet.cpp test_roulette_wheel.cpp test_game_session.cpp test_journal.cpp test_bot.cpp)

target_link_libraries(run_tests gtest_main core)

include(GoogleTest)
gtest_discover_tests(run_tests)