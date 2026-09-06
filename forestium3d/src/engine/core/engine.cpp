#include "engine.h"
#include <cstdio>

namespace f3d {

engine* engine::s_instance = nullptr;

engine::engine() 
    : m_application(nullptr)
    , m_window(nullptr)
    , m_timer(nullptr)
    , m_job_system(nullptr)
    , m_memory_arena(nullptr)
    , m_event_bus(nullptr)
    , m_is_running(false) {
}

engine::~engine() {
    shutdown();
}

engine* engine::get_instance() {
    if (!s_instance) {
        s_instance = new engine();
    }
    return s_instance;
}

void engine::destroy_instance() {
    if (s_instance) {
        delete s_instance;
        s_instance = nullptr;
    }
}

bool engine::initialize(const engine_config& config) {
    m_config = config;
    
    printf("[f3d] Initializing Forestium3D Engine...\n");
    printf("[f3d] App: %s\n", config.app_name);
    printf("[f3d] Window: %dx%d, Fullscreen: %d, VSync: %d\n", 
           config.window_width, config.window_height, 
           config.fullscreen, config.vsync);
    printf("[f3d] Editor Mode: %d\n", config.editor_mode);

    // Initialize memory arena first
    m_memory_arena = new memory_arena();
    
    // Initialize event bus
    m_event_bus = new event_bus();
    
    // Initialize timer
    m_timer = new timer();
    
    // Initialize job system
    m_job_system = new job_system();
    
    // Initialize window
    m_window = new window();
    if (!m_window->initialize(config.window_width, config.window_height, config.app_name, config.fullscreen)) {
        printf("[f3d] Failed to initialize window\n");
        return false;
    }
    
    // Initialize application
    m_application = new application();
    if (!m_application->initialize()) {
        printf("[f3d] Failed to initialize application\n");
        return false;
    }

    printf("[f3d] Engine initialized successfully\n");
    m_is_running = true;
    return true;
}

void engine::run() {
    printf("[f3d] Starting main loop...\n");
    
    while (m_is_running && !m_window->should_close()) {
        m_window->poll_events();
        
        // Update timer
        m_timer->tick();
        
        // Update job system
        m_job_system->update();
        
        // Update application
        m_application->update(m_timer->get_delta_time());
        
        // Render
        m_application->render();
        
        // Swap buffers
        m_window->swap_buffers();
    }
    
    printf("[f3d] Main loop ended\n");
}

void engine::shutdown() {
    printf("[f3d] Shutting down engine...\n");
    
    m_is_running = false;
    
    if (m_application) {
        m_application->shutdown();
        delete m_application;
        m_application = nullptr;
    }
    
    if (m_window) {
        m_window->shutdown();
        delete m_window;
        m_window = nullptr;
    }
    
    if (m_job_system) {
        m_job_system->shutdown();
        delete m_job_system;
        m_job_system = nullptr;
    }
    
    if (m_timer) {
        delete m_timer;
        m_timer = nullptr;
    }
    
    if (m_event_bus) {
        delete m_event_bus;
        m_event_bus = nullptr;
    }
    
    if (m_memory_arena) {
        delete m_memory_arena;
        m_memory_arena = nullptr;
    }
    
    printf("[f3d] Engine shutdown complete\n");
}

application* engine::get_application() { return m_application; }
window* engine::get_window() { return m_window; }
timer* engine::get_timer() { return m_timer; }
job_system* engine::get_job_system() { return m_job_system; }
memory_arena* engine::get_memory_arena() { return m_memory_arena; }
event_bus* engine::get_event_bus() { return m_event_bus; }

} // namespace f3d
