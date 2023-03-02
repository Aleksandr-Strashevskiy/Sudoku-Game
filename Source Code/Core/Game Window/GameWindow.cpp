#include "GameWindow.hpp"

#include "../../../Dependencies/ImGui/Backend/imgui_impl_dx11.h"
#include "../../../Dependencies/ImGui/Backend/imgui_impl_win32.h"
#include "../../../Dependencies/ImGui/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND, unsigned int, WPARAM, LPARAM );

namespace core {
    game_window::game_window( HINSTANCE handle, std::string_view name )
        : m_hwnd { create_window( handle, name ) }, m_handle { handle }, m_name { name } {
        // Check if the window handle is null
        if ( m_hwnd == nullptr )
            throw std::runtime_error( "Failed to create window" );

        // Create the device
        if ( !create_device( m_hwnd ) )
            throw std::runtime_error( "Failed to create device" );

        // Show the window
        ::ShowWindow( m_hwnd, SW_HIDE );

        // Update the window
        ::UpdateWindow( m_hwnd );

        // Initialize ImGui
        ImGui::CreateContext( );

        // Initialize ImGui Viewports
        ImGuiIO &io = ImGui::GetIO( );
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.IniFilename = nullptr;

        // Initialize ImGui Win32
        ::ImGui_ImplWin32_Init( m_hwnd );
        // Initialize ImGui DirectX 11
        ::ImGui_ImplDX11_Init( get_device( ), get_context( ) );
    }

    game_window::~game_window( ) {
        // Destroy ImGui DirectX 11
        ImGui_ImplDX11_Shutdown( );
        // Destroy ImGui Win32
        ImGui_ImplWin32_Shutdown( );

        // Destroy ImGui
        ImGui::DestroyContext( );

        // Destroy the device
        destroy_device( );

        // Destroy the window
        destroy_window( );
    }

    void game_window::message_loop( const std::function< void( ) > &callback ) noexcept {
        // Create a new message tag
        MSG message_tag { };

        // Retrieve the next message from the message queue
        while ( auto retrieves_message = static_cast< int >( ::GetMessageA( &message_tag, nullptr, 0, 0 ) ) ) {
            // Check if the message could not be retrieved
            if ( retrieves_message == -1 )
                break;

            // Translate the message to the appropriate format
            ::TranslateMessage( &message_tag );
            // Dispatch the message to the window procedure
            ::DispatchMessageA( &message_tag );

            // Create a new ImGui frame
            ImGui_ImplDX11_NewFrame( );
            ImGui_ImplWin32_NewFrame( );

            // Render the ImGui frame
            ImGui::NewFrame( );

            // Call the callback function
            callback( );

            // Render the ImGui frame
            ImGui::Render( );

            // Check if the ImGui Viewports are enabled
            if ( ( ImGui::GetIO( ).ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) != 0 ) {
                // Create a new ImGui viewport
                ImGui::UpdatePlatformWindows( );
                ImGui::RenderPlatformWindowsDefault( );
            }

            // Render the ImGui draw data
            ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

            // Present the frame
            get_swap_chain( )->Present( 1, 0 );
        }
    }

    HWND game_window::create_window( HINSTANCE handle, std::string_view name ) {
        // Create a new window class with the specified name and attributes
        WNDCLASSEXA window_class { .cbSize        = sizeof( WNDCLASSEXA ),
                                   .style         = CS_CLASSDC,
                                   .lpfnWndProc   = window_proc,
                                   .hInstance     = handle,
                                   .lpszClassName = name.data( ) };

        // Register the window class with the operating system
        if ( ::RegisterClassExA( &window_class ) == 0 )
            throw std::runtime_error( "Failed to register window class" );

        // Create the window with the specified attributes
        HWND window_handle = ::CreateWindowExA( WS_EX_OVERLAPPEDWINDOW,
                                                name.data( ),
                                                name.data( ),
                                                WS_POPUP,
                                                0,
                                                0,
                                                1,
                                                1,
                                                nullptr,
                                                nullptr,
                                                handle,
                                                nullptr );

        // Check if the window handle is null
        if ( window_handle == nullptr )
            throw std::runtime_error( "Failed to create window" );

        // Return the handle to the created window
        return window_handle;
    }

    void game_window::destroy_window( ) const noexcept {
        // Destroy the window
        ::DestroyWindow( m_hwnd );

        // Unregister the window class
        ::UnregisterClassA( m_name.data( ), m_handle );
    }

    LRESULT game_window::window_proc( HWND handle, unsigned int message, WPARAM w_param, LPARAM l_param ) {
        // Check if the message is from ImGui
        if ( ImGui_ImplWin32_WndProcHandler( handle, message, w_param, l_param ) != 0 )
            return 1;

        switch ( message ) {
            case WM_DESTROY :
                // Post a quit message
                ::PostQuitMessage( 0 );
                break;
            case WM_CLOSE :
                // Destroy the window
                ::DestroyWindow( handle );
                break;
            case WM_SYSCOMMAND :
                // Check if the key menu is pressed
                if ( w_param == SC_KEYMENU )
                    return 0;
                break;
            default :
                break;
        }

        // Return the default window procedure
        return ::DefWindowProcA( handle, message, w_param, l_param );
    }
} // namespace core