cmake_minimum_required(VERSION 2.6)  #要求的最低cmake版本号
PROJECT(forward-mail)        #项目名称

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $ENV{TARGET_LDFLAGS} -L$ENV{BUILD_DIR} -Wl,--rpath-link,$ENV{STAGING_DIR}/lib -lcurl ")


add_definitions(-std=c++11)
# find_package(libcurl)
# target_link_libraries(main libcurl)
# add_subdirectory(deps/vmime)
 
SET(SOURCES main.cpp)   #设置变量SOURCES所指定的C文件
ADD_EXECUTABLE(forward-mail ${SOURCES})   #设置最终生成的可执行文件名
 
INSTALL(TARGETS forward-mail RUNTIME DESTINATION bin)   #最后的install，必要的