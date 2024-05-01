cmake_minimum_required(VERSION 3.5.0)
project(pbz_lab6 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(pbz_lab6 main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
