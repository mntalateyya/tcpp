cmake_minimum_required (VERSION 2.8.11)
project (tcpp)
add_executable(client client.cpp tcpp.cpp)
add_executable(server server.cpp tcpp.cpp)