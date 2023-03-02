#ifndef SOURCECODE_CORE_GAMEWINDOW_GAMEWINDOW_HPP
#define SOURCECODE_CORE_GAMEWINDOW_GAMEWINDOW_HPP

#include "../Window Render/WindowRender.hpp"

#include <functional>
#include <string_view>
#include <Windows.h>

namespace core {
    class game_window : private window_render {
      public:
        /**
         * @brief Construct a new game window object
         * @param handle The handle to the instance of the application
         * @param name The name of the window to create
         * @throws std::runtime_error if the window could not be created
         */
        game_window( HINSTANCE handle, std::string_view name );

        /**
         * @brief Destroy the game window object
         */
        ~game_window( );

        /**
         * @brief Run the message loop
         * @param callback The callback to run every frame
         * @return true if the message loop should continue, false otherwise
         */
        void message_loop( const std::function< void( ) > &callback ) noexcept;

      private:
        /**
         * @brief Create the window
         * @param handle The handle to the instance of the application
         * @param name The name of the window to create
         * @return The handle to the window
         * @throws std::runtime_error if the window could not be created
         */
        static HWND create_window( HINSTANCE handle, std::string_view name );

        /**
         * @brief Destroy the window
         */
        void destroy_window( ) const noexcept;

        /**
         * @brief The window procedure
         * @param handle The handle to the window
         * @param message The message
         * @param w_param The first parameter
         * @param l_param The second parameter
         * @return The result of the message
         */
        static LRESULT window_proc( HWND handle, unsigned int message, WPARAM w_param, LPARAM l_param );

        /**
         * @brief The handle to the window
         */
        HWND m_hwnd { };
        /**
         * @brief The handle to the instance of the application
         */
        HINSTANCE m_handle { };
        /**
         * @brief The name of the window
         */
        std::string_view m_name { };
    };
} // namespace core

#endif // SOURCECODE_CORE_GAMEWINDOW_GAMEWINDOW_HPP