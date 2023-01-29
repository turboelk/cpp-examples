cmake_minimum_required(VERSION 3.7)
project("examples")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

function(compile_files expr)
  set(files )
	file(GLOB files "${expr}")
  string(MAKE_C_IDENTIFIER "${id}" BIN)
  foreach(f ${files})
    get_filename_component(basename ${f} NAME_WE)

    if (IS_DIRECTORY ${f})
      add_subdirectory(${f})
    else()
      string(MAKE_C_IDENTIFIER "${basename}" BIN)

      add_executable(${BIN} ${f})
      #target_include_directories(${BIN})
      target_link_libraries(${BIN} PRIVATE
        Threads::Threads
      )
    endif()
  endforeach(f)
endfunction(compile_files)

compile_files("src/*.cpp")
