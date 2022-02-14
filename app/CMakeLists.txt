cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11 -fPIC -w")
add_library(native-lib
             SHARED
             src/main/cpp/native-lib.cpp
             src/main/cpp/JniUtils.cpp
             src/main/cpp/web_task.cpp
        src/main/cpp/cJSON.c
        src/main/cpp/parson.c)

 include_directories( src/main/cpp/include/curl
                     )

add_library(curl STATIC IMPORTED)
set_target_properties(curl
  PROPERTIES IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libcurl.a)





find_library( # Sets the name of the path variable.
              log-lib
              log )

target_link_libraries( # Specifies the target library.
                       native-lib
                       curl
                       ${log-lib} )
