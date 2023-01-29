cmake_minimum_required(VERSION 3.7)
project("examples-lua")
set(TARGET "examples-lua")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(THREAD_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Lua 5.1 REQUIRED)

add_executable(${TARGET}
  src/main.cpp
  src/get_field.cpp
  src/get_field.hpp
  src/debug_stack.cpp
  src/debug_stack.hpp
)

target_include_directories(${TARGET} PRIVATE
  ${LUA_INCLUDE_DIR}
)

target_link_libraries(${TARGET} PRIVATE
  Threads::Threads
  Lua::Lua
  ${LUA_LIBRARIES}
)
