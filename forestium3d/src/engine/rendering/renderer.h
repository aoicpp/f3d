#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <string>

namespace f3d {

enum class render_api : uint8_t {
    opengl = 0,
    directx11,
    directx12,
    metal,
    vulkan
};

struct renderer_config {
    render_api api;
    int swapchain_width;
    int swapchain_height;
    bool vsync;
    bool fullscreen;
    uint8_t msaa_samples;
};

class renderer {
public:
    static renderer* get_instance();
    static void destroy_instance();
    
    bool initialize(const renderer_config& config);
    void shutdown();
    
    void begin_frame();
    void end_frame();
    
    void set_viewport(int x, int y, int width, int height);
    void set_scissor(int x, int y, int width, int height);
    void clear_color(float r, float g, float b, float a);
    void clear_depth(float depth);
    
    render_api get_api() const { return m_config.api; }
    int get_width() const { return m_config.swapchain_width; }
    int get_height() const { return m_config.swapchain_height; }
    
    void* get_native_device();
    void* get_native_context();

private:
    renderer();
    ~renderer();
    
    static renderer* s_instance;
    
    renderer_config m_config;
    bool m_initialized;
    void* m_native_device;
    void* m_native_context;
};

} // namespace f3d

#endif // RENDERER_H
