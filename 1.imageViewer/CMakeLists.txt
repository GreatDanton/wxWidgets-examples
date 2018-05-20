cmake_minimum_required(VERSION 3.5)
project(imageViewer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# include header files
include_directories(include)

# source files
set (SRC_FILES
        src/main.cpp
        src/scrolledwindow.cpp
        src/scrolledimage.cpp
        src/mainframe.cpp
     )

# create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# link wxwidgets
find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    # and for each of your dependent executable/library targets:
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()

