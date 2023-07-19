cmake_minimum_required(VERSION 3.0)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

project(sgp4 C)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(sgp4 STATIC ${CMAKE_SOURCE_DIR}/src/brent.c)
add_library(sg4coord STATIC ${CMAKE_SOURCE_DIR}/src/sgp4coord.c)
add_library(sgp4ext STATIC ${CMAKE_SOURCE_DIR}/src/sgp4ext.c)
add_library(sgp4io STATIC ${CMAKE_SOURCE_DIR}/src/sgp4io.c)
add_library(sgp4pred STATIC ${CMAKE_SOURCE_DIR}/src/sgp4pred.c)
add_library(sgp4unit STATIC ${CMAKE_SOURCE_DIR}/src/sgp4unit.c)
add_library(visible STATIC ${CMAKE_SOURCE_DIR}/src/visible.c)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
install(TARGETS sgp4 DESTINATION lib)
