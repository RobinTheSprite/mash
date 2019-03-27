cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)

add_executable(mash main.cpp)

add_executable(permit file-ops/permit.cpp)

add_executable(rd file-ops/rd.cpp)

add_executable(rf file-ops/rf.cpp)

add_executable(md file-ops/md.cpp)

add_executable(mf file-ops/mf.cpp)

add_executable(ls ls.cpp)

add_executable(echo echo.cpp)


