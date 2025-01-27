cmake_minimum_required(VERSION 3.20)
set(projectName "SteelCalc")
set(SOURCES 
      MyApp.cpp
      SteelCalcBase.cpp 
      SteelCalcMain.cpp
      SteelCalcOptions.cpp
      CustomGridCellEditor.h
   )

project(${projectName} VERSION 0.2.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# wxWidgets specific configuration
set(wxWidgets_CONFIGURATION "mswu")
set(wxWidgets_ROOT_DIR $ENV{WXWIN})
set(wxWidgets_LIB_DIR $ENV{WXWIN}/lib/gcc_x64_lib)
set(wxWidgets_INCLUDE_DIRS
      "${wxWidgets_ROOT_DIR}/include"
      "${wxWidgets_ROOT_DIR}/lib/gcc_x64_lib/mswu"
   )

include_directories(
      $ENV{WXWIN}/include
      $ENV{WXWIN}/lib/gcc_x64_lib/mswu
      )

link_directories($ENV{WXWIN}/lib/gcc_x64_lib)

# Find wxWidgets for static linking
find_package(wxWidgets 3.2 REQUIRED COMPONENTS gl core base)

include(${wxWidgets_USE_FILE})
set(wxWidgets_USE_STATIC ON)

# add sources to executable
add_executable(${projectName} WIN32 ${SOURCES})

target_include_directories(${projectName} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${projectName} ${wxWidgets_LIBRARIES})

# Handle project resources...
# Define the source and destination resource directories
# set(RESOURCE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
# set(RESOURCE_DEST_DIR "${CMAKE_BINARY_DIR}/resources")
# # Create a custom target to copy the resources recursively
# add_custom_target(copy_resources ALL
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_SOURCE_DIR} ${RESOURCE_DEST_DIR}
#     COMMENT "Copying resource files recursively to the build directory..."
# )

# # Create a custom command to clean the destination directory
# add_custom_command(TARGET copy_resources PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${RESOURCE_DEST_DIR}
#     COMMENT "Removing outdated resource files from the build directory..."
# )

# # Add a custom command to copy the resources recursively
# add_custom_command(TARGET copy_resources POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCE_SOURCE_DIR} ${RESOURCE_DEST_DIR}
#     COMMENT "Copying resource files recursively to the build directory..."
# )

# # Ensure the resources are copied before building the executable
# add_dependencies(${projectName} copy_resources)
