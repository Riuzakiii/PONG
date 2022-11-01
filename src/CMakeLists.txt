add_executable(Pong main.cpp Ball.cpp FPSCounter.cpp Score.cpp ScoreTexts.cpp Wall.cpp GameEngine.cpp)

target_link_libraries(Pong PRIVATE SDL2::SDL2 SDLYogurt)
target_include_directories(Pong PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)
set_target_properties(Pong PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
