
include_directories(../include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_executable(StaticTests StaticTests.cpp)
add_executable(Mat4f Mat4f.cpp)
