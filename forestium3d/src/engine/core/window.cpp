#include "window.h"
#include <cstdio>

// GLFW will be included here when libs are set up
// #include <GLFW/glfw3.h>

namespace f3d {

bool window::initialize(int width, int height, const char* title, bool fullscreen) {
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;
    m_should_close = false;
    m_native_window = nullptr;

    printf("[f3d] Window initializing: %dx%d, Title: %s, Fullscreen: %d\n", 
           width, height, title, fullscreen);

    // TODO: Initialize GLFW and create window
    // This is a stub until GLFW is integrated
    
    printf("[f3d] Window initialized (stub)\n");
    return true;
}

void window::shutdown() {
    printf("[f3d] Window shutting down...\n");
    
    // TODO: Destroy GLFW window
    if (m_native_window) {
        m_native_window = nullptr;
    }
    
    printf("[f3d] Window shutdown complete\n");
}

void window::poll_events() {
    // TODO: glfwPollEvents()
}

void window::swap_buffers() {
    // TODO: glfwSwapBuffers()
}

bool window::should_close() const {
    return m_should_close;
    // TODO: return glfwWindowShouldClose()
}

void* window::get_native_window() {
    return m_native_window;
}

} // namespace f3d
