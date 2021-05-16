cmake_minimum_required(VERSION 3.10)

# Create the shared library

project(jel VERSION 0.0.0)

add_library(${PROJECT_NAME} SHARED
  ${CMAKE_CURRENT_LIST_DIR}/src/core.c
  ${CMAKE_CURRENT_LIST_DIR}/src/component/component_stack.c
  ${CMAKE_CURRENT_LIST_DIR}/src/component/component_stack_utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/entity/entity.c
  ${CMAKE_CURRENT_LIST_DIR}/src/entity/entity_utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/error/error.c
  ${CMAKE_CURRENT_LIST_DIR}/src/error/error_utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/hierarchy/hierarchy.c
  ${CMAKE_CURRENT_LIST_DIR}/src/prefab/prefab.c
  ${CMAKE_CURRENT_LIST_DIR}/src/prefab/prefab_utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/table/query.c
  ${CMAKE_CURRENT_LIST_DIR}/src/table/table.c
  ${CMAKE_CURRENT_LIST_DIR}/src/table/table_utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/type/type.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY lib
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION}
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

# Installation
if (UNIX)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/JEL)

endif (UNIX)
