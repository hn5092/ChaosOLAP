cmake_minimum_required(VERSION 3.22)
project(cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

set(ENV{JAVA_HOME} "/Users/xuyiming/Library/Java/JavaVirtualMachines/openjdk-18.0.2/Contents/Home")

include(cmake_modules/kudu_cmake_fns.txt)
# Adds a third-party library with name ${NAME}. If BUILD_SHARED_LIBS is true, the new
# library refers to ${SHARED_LIB}; otherwise it refers to ${STATIC_LIB}. If only one
# library (static or shared) is provided, it is used regardless of BUILD_SHARED_LIBS. The
# library's headers are added to the system include path.
function(IMPALA_ADD_THIRDPARTY_LIB NAME HEADER STATIC_LIB SHARED_LIB)
    message(STATUS "----------> Adding thirdparty library ${NAME}. <----------")
    if (HEADER)
        include_directories(SYSTEM ${HEADER})
        message(STATUS "Header files: ${HEADER}")
    endif()
    if (NOT STATIC_LIB AND NOT SHARED_LIB)
        message(FATAL_ERROR "Library '${NAME}' has neither shared nor static library files")
        return ()
    endif()

    if ((BUILD_SHARED_LIBS AND SHARED_LIB) OR NOT STATIC_LIB)
        ADD_THIRDPARTY_LIB(${NAME} SHARED_LIB ${SHARED_LIB})
    else()
        ADD_THIRDPARTY_LIB(${NAME} STATIC_LIB ${STATIC_LIB})
    endif()
endfunction()

find_package(JNI REQUIRED)
IMPALA_ADD_THIRDPARTY_LIB(java_jvm "${JNI_INCLUDE_DIRS}" "" ${JAVA_JVM_LIBRARY})
add_subdirectory(src)
