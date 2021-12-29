cmake_minimum_required(VERSION 3.10)

# Create the shared library

project(jel VERSION 0.0.0)

set(SRC
  ${CMAKE_CURRENT_LIST_DIR}/src/core.c
  ${CMAKE_CURRENT_LIST_DIR}/src/utility.c
  ${CMAKE_CURRENT_LIST_DIR}/src/component/component.c
  ${CMAKE_CURRENT_LIST_DIR}/src/component/component_map.c
  ${CMAKE_CURRENT_LIST_DIR}/src/component/component_table.c
  ${CMAKE_CURRENT_LIST_DIR}/src/entity/entity.c
  ${CMAKE_CURRENT_LIST_DIR}/src/entity/entity_manager.c
  ${CMAKE_CURRENT_LIST_DIR}/src/logger/logger.c
  ${CMAKE_CURRENT_LIST_DIR}/src/query/query.c
  ${CMAKE_CURRENT_LIST_DIR}/src/table/table.c
  ${CMAKE_CURRENT_LIST_DIR}/src/table/table_stack.c
  ${CMAKE_CURRENT_LIST_DIR}/src/type/type.c
)

add_library(${PROJECT_NAME} SHARED ${SRC})
add_library(${PROJECT_NAME}_static STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/src
)

target_include_directories(${PROJECT_NAME}_static PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY lib
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION}
)

set_target_properties(${PROJECT_NAME}_static PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY lib
  OUTPUT_NAME jel
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Windows compilation stuff
if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zc:preprocessor")
endif (MSVC)

if (EMSCRIPTEN)
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -s WASM=1")
endif ()

# Installation
if (UNIX)

include(GNUInstallDirs)

# Shared library
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
# Static library
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
# Include directory
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/JEL)

endif (UNIX)

# Make the test
project(test)

add_executable(test
  ${CMAKE_CURRENT_LIST_DIR}/src/test.c
)

target_link_directories(test PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/lib
)

target_link_libraries(test PUBLIC jel)

set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
