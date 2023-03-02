# Set the minimum required version of CMake to 3.25
CMAKE_MINIMUM_REQUIRED( VERSION 3.25 )

# Set the C++ standard to 20
SET( CMAKE_CXX_STANDARD 20 )
# Require the C++ standard to be used
SET( CMAKE_CXX_STANDARD_REQUIRED ON )

# Set the project name to Sudoku_Game
PROJECT( Sudoku_Game )

# Create an executable with the project name and EntryPoint.cpp as its source code
ADD_EXECUTABLE( ${PROJECT_NAME} WIN32 "Source Code/EntryPoint.cpp" )

# Check if the operating system is Windows
IF ( WIN32 )
    # Set the path to the DirectX SDK
    SET( DXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK" )

    # Check if the DirectX SDK is installed in the hardcoded path
    IF ( EXISTS "${DXSDK_DIR}" )
        SET( DXSDK_INCLUDE_DIR "${DXSDK_PATH}/Include" )
        SET( DXSDK_LIBRARY_DIR "${DXSDK_PATH}/Lib/x64" )
    # If it is not installed in the hardcoded path, check if the DXSDK_DIR environment variable is set
    ELSEIF ( EXISTS "$ENV{DXSDK_DIR}" )
        SET( DXSDK_DIR "$ENV{DXSDK_DIR}" )
        SET( DXSDK_INCLUDE_DIR "${DXSDK_PATH}/Include" )
        SET( DXSDK_LIBRARY_DIR "${DXSDK_PATH}/Lib/x64" )
    # If neither path is valid, issue an error message and halt the CMake configuration process
    ELSE ()
        MESSAGE( FATAL_ERROR "DirectX SDK not found" )
    ENDIF ()

    # Print a message indicating the path to the DirectX SDK that was found
    MESSAGE( STATUS "DirectX SDK found at: ${DXSDK_DIR}" )

    # Add the DirectX SDK include directory to the include path for the project
    INCLUDE_DIRECTORIES( ${DXSDK_INCLUDE_DIR} )
    # Add the DirectX SDK library directory to the linker path for the project
    LINK_DIRECTORIES( ${DXSDK_LIBRARY_DIR} )
    # Link the required DirectX libraries and dwmapi to the project
    TARGET_LINK_LIBRARIES( ${PROJECT_NAME} d3d11 d3dx11 d3dcompiler dwmapi )
ENDIF ()

# Set target properties for the executable
SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES
                       PREFIX ""
                       OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_BUILD_TYPE}" )

# Add the Source Code directory to the project
ADD_SUBDIRECTORY( "Source Code" )
# Add the Dependencies directory to the project
ADD_SUBDIRECTORY( "Dependencies" )