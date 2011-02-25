
project(CoreRender)
cmake_minimum_required(VERSION 2.6.0)

add_subdirectory(tests)

# Installation of files

install(DIRECTORY include/GameMath DESTINATION include FILES_MATCHING PATTERN *.hpp)
install(FILES include/GameMath.hpp DESTINATION include)
