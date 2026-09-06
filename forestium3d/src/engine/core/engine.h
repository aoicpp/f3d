#ifndef ENGINE_H
#define ENGINE_H

#include "application.h"
#include "window.h"
#include "timer.h"
#include "job_system.h"
#include "memory_arena.h"
#include "event_bus.h"

namespace f3d {

struct engine_config {
    const char* app_name;
    int window_width;
    int window_height;
    bool fullscreen;
    bool vsync;
    bool editor_mode;
};

class engine {
public:
    static engine* get_instance();
    static void destroy_instance();

    bool initialize(const engine_config& config);
    void run();
    void shutdown();

    application* get_application();
    window* get_window();
    timer* get_timer();
    job_system* get_job_system();
    memory_arena* get_memory_arena();
    event_bus* get_event_bus();

    bool is_running() const { return m_is_running; }
    bool is_editor_mode() const { return m_config.editor_mode; }

private:
    engine();
    ~engine();

    static engine* s_instance;

    engine_config m_config;
    application* m_application;
    window* m_window;
    timer* m_timer;
    job_system* m_job_system;
    memory_arena* m_memory_arena;
    event_bus* m_event_bus;

    bool m_is_running;
};

} // namespace f3d

#endif // ENGINE_H
