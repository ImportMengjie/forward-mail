cmake_minimum_required(VERSION 2.6)
PROJECT(forward-mail)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $ENV{TARGET_LDFLAGS} -L$ENV{BUILD_DIR} -Wl,--rpath-link,$ENV{STAGING_DIR}/lib -lcurl ")


add_definitions(-std=c++11)

add_subdirectory(base)

 
SET(SOURCES main.cpp)
ADD_EXECUTABLE(forward-mail ${SOURCES})

target_link_libraries(forward-mail curl base)

INSTALL(TARGETS forward-mail RUNTIME DESTINATION bin)