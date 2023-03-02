#ifndef SOURCECODE_CORE_WINDOWRENDER_WINDOWRENDER_HPP
#define SOURCECODE_CORE_WINDOWRENDER_WINDOWRENDER_HPP

#include <d3d11.h>

namespace core {
    class window_render {
      public:
        /**
         * @brief Create a device object and a swap chain
         * @param window_handle The handle to the window
         * @return true if the device and swap chain were created successfully, false otherwise
         */
        bool create_device( HWND window_handle );

        /**
         * @brief Create a render target view
         * @return true if the render target view was created successfully, false otherwise
         */
        bool create_render_target( ) noexcept;

        /**
         * @brief Destroy the device object and the swap chain
         */
        void destroy_device( ) noexcept;

        /**
         * @brief Destroy the render target view
         */
        void destroy_render_target( ) noexcept;

        /**
         * @brief Get the device object
         * @return The device object
         */
        [[nodiscard]] ID3D11Device *get_device( ) const noexcept;
        /**
         * @brief Get the device context
         * @return The device context
         */
        [[nodiscard]] ID3D11DeviceContext *get_context( ) const noexcept;
        /**
         * @brief Get the swap chain
         * @return The swap chain
         */
        [[nodiscard]] IDXGISwapChain *get_swap_chain( ) const noexcept;
        /**
         * @brief Get the render target view
         * @return The render target view
         */
        [[nodiscard]] ID3D11RenderTargetView *get_render_target_view( ) const noexcept;

      private:
        /**
         * @brief Create the swap chain description
         * @param window_handle The handle to the window
         * @return The swap chain description
         */
        [[nodiscard]] static DXGI_SWAP_CHAIN_DESC create_swap_chain_desc( HWND window_handle ) noexcept;

        /**
         * @brief The device object
         */
        ID3D11Device *m_device { };
        /**
         * @brief The device context
         */
        ID3D11DeviceContext *m_context { };
        /**
         * @brief The swap chain
         */
        IDXGISwapChain *m_swap_chain { };
        /**
         * @brief The render target view
         */
        ID3D11RenderTargetView *m_render_target_view { };
    };
} // namespace core

#endif // SOURCECODE_CORE_WINDOWRENDER_WINDOWRENDER_HPP