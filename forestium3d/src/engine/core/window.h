#ifndef WINDOW_H
#define WINDOW_H

namespace f3d {

class window {
public:
    bool initialize(int width, int height, const char* title, bool fullscreen);
    void shutdown();
    
    void poll_events();
    void swap_buffers();
    bool should_close() const;
    
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
    bool is_fullscreen() const { return m_fullscreen; }
    
    void* get_native_window();

private:
    int m_width;
    int m_height;
    bool m_fullscreen;
    bool m_should_close;
    void* m_native_window;
};

} // namespace f3d

#endif // WINDOW_H
