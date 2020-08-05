cmake_minimum_required(VERSION 3.16)

include(FetchContent)

FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen
        GIT_TAG        3.3
)

FetchContent_GetProperties(Eigen)
if(NOT Eigen_POPULATED)
    FetchContent_Populate(Eigen)
    message(Found ${eigen_SOURCE_DIR})
    include_directories(${eigen_SOURCE_DIR})
endif()



add_executable(schwefel example.cc)
target_link_libraries(schwefel smetaheuristics)


add_executable(quadratic quadratic.cc)
target_link_libraries(quadratic smetaheuristics)

