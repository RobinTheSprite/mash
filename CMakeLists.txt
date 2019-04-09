cmake_minimum_required(VERSION 3.10)
project(mash)

set(CMAKE_CXX_STANDARD 17)

add_executable(mash src/main.cpp mash-error.cpp)

add_executable(ls src/ls.cpp mash-error.cpp)

add_executable(echo src/echo.cpp mash-error.cpp)

add_executable(md src/md.cpp mash-error.cpp)

add_executable(mf src/mf.cpp mash-error.cpp)

add_executable(rd src/rd.cpp mash-error.cpp)

add_executable(rf src/rf.cpp mash-error.cpp)

add_executable(ping src/ping.cpp mash-error.cpp)

add_executable(permit src/permit.cpp mash-error.cpp)