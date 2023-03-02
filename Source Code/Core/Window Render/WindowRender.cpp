#include "WindowRender.hpp"

#include <array>

namespace core {
    bool window_render::create_device( HWND window_handle ) {
        // Create the swap chain description
        const DXGI_SWAP_CHAIN_DESC swap_chain_desc = create_swap_chain_desc( window_handle );

        // Check if the output window is null
        if ( swap_chain_desc.OutputWindow == nullptr )
            throw std::runtime_error( "Failed to create swap chain description" );

        // Create the feature levels
        const std::array< D3D_FEATURE_LEVEL, 2 > feature_levels { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

        // Create the device and swap chain
        auto result = D3D11CreateDeviceAndSwapChain( nullptr,
                                                     D3D_DRIVER_TYPE_HARDWARE,
                                                     nullptr,
                                                     0,
                                                     feature_levels.data( ),
                                                     feature_levels.size( ),
                                                     D3D11_SDK_VERSION,
                                                     &swap_chain_desc,
                                                     &m_swap_chain,
                                                     &m_device,
                                                     nullptr,
                                                     &m_context );

        // Check if the device and swap chain could not be created
        if ( result != S_OK )
            throw std::runtime_error( "Failed to create device and swap chain" );

        // Create the render target
        return create_render_target( );
    }

    bool window_render::create_render_target( ) noexcept {
        // Create the render target
        ID3D11Texture2D *render_target { };

        // Get the buffer
        if ( m_swap_chain->GetBuffer( 0, IID_PPV_ARGS( &render_target ) ) != S_OK )
            return false;

        // Create the render target view
        if ( m_device->CreateRenderTargetView( render_target, nullptr, &m_render_target_view ) != S_OK ) {
            // Release the render target
            render_target->Release( );
            // Set the render target to null
            render_target = nullptr;

            return false;
        }

        // Release the render target
        render_target->Release( );
        // Set the render target to null
        render_target = nullptr;

        // Return true
        return true;
    }

    void window_render::destroy_device( ) noexcept {
        // Destroy the render target
        destroy_render_target( );

        if ( m_swap_chain != nullptr ) {
            // Release the swap chain
            m_swap_chain->Release( );
            // Set the swap chain to null
            m_swap_chain = nullptr;
        }

        if ( m_context != nullptr ) {
            // Release the context
            m_context->Release( );
            // Set the context to null
            m_context = nullptr;
        }

        if ( m_device != nullptr ) {
            // Release the device
            m_device->Release( );
            // Set the device to null
            m_device = nullptr;
        }
    }

    void window_render::destroy_render_target( ) noexcept {
        if ( m_render_target_view != nullptr ) {
            // Release the render target view
            m_render_target_view->Release( );
            // Set the render target view to null
            m_render_target_view = nullptr;
        }
    }

    ID3D11Device *window_render::get_device( ) const noexcept {
        // Return the device
        return m_device;
    }

    ID3D11DeviceContext *window_render::get_context( ) const noexcept {
        // Return the context
        return m_context;
    }

    IDXGISwapChain *window_render::get_swap_chain( ) const noexcept {
        // Return the swap chain
        return m_swap_chain;
    }

    ID3D11RenderTargetView *window_render::get_render_target_view( ) const noexcept {
        // Return the render target view
        return m_render_target_view;
    }

    DXGI_SWAP_CHAIN_DESC window_render::create_swap_chain_desc( HWND window_handle ) noexcept {
        // Create the swap chain description
        DXGI_SWAP_CHAIN_DESC swap_chain_desc {
            .BufferDesc = {
                .RefreshRate = {
                    .Numerator = 60,
                    .Denominator = 0,
                },
                .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
            },
            .SampleDesc = {
                .Count = 1,
                .Quality = 0,
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = 1,
            .OutputWindow = window_handle,
            .Windowed = 1,
            .SwapEffect = DXGI_SWAP_EFFECT_DISCARD,
            .Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
        };

        // Return the swap chain description
        return swap_chain_desc;
    }
} // namespace core