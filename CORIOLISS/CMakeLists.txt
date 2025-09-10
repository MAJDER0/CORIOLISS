# CORIOLISS/CMakeLists.txt
add_executable(viewer
  CORIOLISS.cpp
)

target_include_directories(viewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SDL2 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(viewer PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  glad::glad
  OpenGL::GL
)

if(MSVC)
  target_compile_options(viewer PRIVATE /W4 /permissive-)
else()
  target_compile_options(viewer PRIVATE -Wall -Wextra -Wpedantic)
endif()
