cmake_minimum_required(VERSION 3.15)
project(smetaheuristics
        VERSION 0.0.1
        LANGUAGES CXX)


set(BUILD_EXAMPLES ON)



add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include/sim_annealing.h ${PROJECT_SOURCE_DIR}/include/random_opt.h )


target_include_directories(
        ${PROJECT_NAME}
        INTERFACE ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
