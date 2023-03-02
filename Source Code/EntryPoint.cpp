#include "../Dependencies/ImGui/imgui.h"
#include "Core/Game Window/GameWindow.hpp"

extern "C" int WinMain( HINSTANCE handle, HINSTANCE, LPSTR, int ) {
    // Try to run the game window
    try {
        // Create a new game window
        core::game_window window { handle, "Sudoku Window" };

        // Run the message loop
        window.message_loop( []( ) {
            ImGui::Begin( "Hello, world!" );
            ImGui::Text( "This is some useful text." );
            ImGui::End( );
        } );
    } catch ( std::exception &exception ) {
        // Display the error message
        ::MessageBoxA( nullptr, exception.what( ), "Error", MB_OK | MB_ICONERROR );

        // Return an error code
        return 1;
    }

    // Return a success code
    return 0;
}