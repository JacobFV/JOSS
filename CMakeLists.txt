# This is template code retrieved from the official FXTUI author at
# https://github.com/ArthurSonzogni/ftxui-starter/blob/master/CMakeLists.txt
# Its project name was replaced by `joss`

cmake_minimum_required (VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG 87a1d75bf1c1ee964e8eed4a6686544ae3b44116
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

project(joss
  LANGUAGES CXX
  VERSION 1.0.0
)

set(CMAKE_BUILD_TYPE Debug) # debug with gdb
add_executable(joss 
  src/main.cpp 
  src/view 
  src/model 
  src/controller 
  src/header 
  src/utils
  src/components/resizable_split
)
target_include_directories(joss PRIVATE src)

target_link_libraries(joss
  PRIVATE ftxui::dom
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
)

# C++17 is used. We requires fold expressions at least.
set_target_properties(joss PROPERTIES CXX_STANDARD 17)

install(TARGETS joss RUNTIME DESTINATION "bin")