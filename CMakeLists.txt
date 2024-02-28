cmake_minimum_required(VERSION 3.5)

project(Module15)

set(SRC_LIST 
      main.cpp
	  authentificationdata.cpp
	  sha1.cpp
	  chathash.cpp)
	  
add_executable(chathash ${SRC_LIST})	

set(CXX_FLAGS "${CXX_FLAGS} -std==c++11 -Wall")  