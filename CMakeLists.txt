cmake_minimum_required(VERSION 3.4)
project(multiformats)

set(CMAKE_CXX_STANDARD 17)

set(INC_FOLDERS
        include)

set(UTILS_FOLDERS
        utils)

include_directories(${INC_FOLDERS})
include_directories(${UTILS_FOLDERS})

add_executable(${PROJECT_NAME}
        main.cpp
        src/cid.cpp
        src/multibase.cpp
        src/multiaddr.cpp
        src/multihash.cpp
        utils/base.cpp)

target_link_libraries(${PROJECT_NAME} C:/OpenSSL-Win64/lib/openssl.lib C:/OpenSSL-Win64/lib/libcrypto.lib)
target_include_directories(${PROJECT_NAME} PUBLIC C:/OpenSSL-Win64/include)
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
