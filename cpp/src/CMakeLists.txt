
add_library(cpp SHARED jni_wrapper.cc library.cpp)

include_directories(${JNI_INCLUDE_DIRS})
