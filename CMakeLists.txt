# Set the minimum required version of CMake to 3.25
CMAKE_MINIMUM_REQUIRED( VERSION 3.25 )

# Set the C++ standard to 20
SET( CMAKE_CXX_STANDARD 20 )
# Require the C++ standard to be used
SET( CMAKE_CXX_STANDARD_REQUIRED ON )

# Set the project name to Sudoku_Game
PROJECT( Sudoku_Game )

# Create an executable with the project name and EntryPoint.cpp as its source code
ADD_EXECUTABLE( ${PROJECT_NAME} "Source Code/EntryPoint.cpp" )

# Set target properties for the executable
SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES
                       PREFIX ""
                       OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_BUILD_TYPE}" )

# Add the Source Code and Dependencies directories as subdirectories
ADD_SUBDIRECTORY( "Source Code" )
ADD_SUBDIRECTORY( "Dependencies" )