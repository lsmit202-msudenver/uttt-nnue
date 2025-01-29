# Define Target Information
set(TARGET_NAME uttt)
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/uttt.cpp)

# Support IDE Visualization
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCES})

# Define Target according to options
add_executable(${TARGET_NAME} ${TARGET_SOURCES})

# Definitions for ...

# ... target properties
set_target_properties(${TARGET_NAME} PROPERTIES 
  DEBUG_POSTFIX "-d"
)

# ... compiler options
target_compile_options(${TARGET_NAME} PRIVATE ${compiler_options})
target_compile_definitions(${TARGET_NAME} PRIVATE ${compiler_definitions})

# ... linker options
target_link_options(${TARGET_NAME} PRIVATE ${linker_flags})

# ... included directories
target_include_directories(${TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
  PRIVATE 
    ${TARGET_INCLUDE_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/include
)

# link against lib
target_link_libraries(${TARGET_NAME} PUBLIC libuttt)
