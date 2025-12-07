cmake_minimum_required(VERSION 3.10)
project(AI_DSA_CHATBOT)

set(CMAKE_CXX_STANDARD 17)

# Set output directories for all targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# =============================================
# Global include directory (all targets see it)
# =============================================
include_directories(${CMAKE_SOURCE_DIR}/include)

# =============================================
# DSA Static Library (core algorithms)
# =============================================
file(GLOB_RECURSE DSA_SOURCES "${CMAKE_SOURCE_DIR}/src/dsa/*.cpp")
add_library(dsa STATIC ${DSA_SOURCES})
target_include_directories(dsa PUBLIC ${CMAKE_SOURCE_DIR}/include)

# =============================================
# Chatbot Library
# =============================================
file(GLOB_RECURSE CHATBOT_SOURCES "${CMAKE_SOURCE_DIR}/src/chatbot/*.cpp")
add_library(chatbot_lib STATIC ${CHATBOT_SOURCES})
target_include_directories(chatbot_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(chatbot_lib PUBLIC dsa)

# =============================================
# Main Chatbot Executable
# =============================================
if(EXISTS ${CMAKE_SOURCE_DIR}/src/main.cpp)
    add_executable(chatbot src/main.cpp)
    target_link_libraries(chatbot PRIVATE chatbot_lib dsa)
endif()

# =============================================
# Automatic Test Discovery
# =============================================
# Find all test_*.cpp files in tests/ and create executables
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/test_*.cpp")

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${test_name} PRIVATE dsa chatbot_lib)
endforeach()

# =============================================
# Enable Testing (optional, for ctest)
# =============================================
enable_testing()
foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
