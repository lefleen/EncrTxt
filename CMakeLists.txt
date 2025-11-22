cmake_minimum_required(VERSION 3.15) 
project(EncryptorTxt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 set(ZLIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}\\zlib\\zlib-1.3.1")
 set(ZLIB_LIBRARY "${ZLIB_INCLUDE_DIRS}\\zlib.lib")

add_executable(${PROJECT_NAME}
    "main.cpp"
    "change format pixels.cpp"
    "cryptograthy.cpp"
    "get pixels.cpp"
    "user interface.cpp"
    "work with chunks.cpp"
    "work with files.cpp"
    "create png.cpp"
    "png.cpp"
    "handler read.cpp"
    "handler write.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${ZLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ZLIB_LIBRARY})