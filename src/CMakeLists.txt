SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

FILE(GLOB headers "*.h")
FILE(GLOB sources "*.cpp")

ADD_LIBRARY(TinyNet SHARED ${headers} ${sources})

