#include "timer.h"
#include <chrono>
#include <cstdio>

namespace f3d {

timer::timer() 
    : m_elapsed_seconds(0.0)
    , m_delta_time(0.0f)
    , m_total_time(0.0f)
    , m_last_frame_time(0.0f)
    , m_frame_count(0)
    , m_fps(0.0f)
    , m_fps_accumulator(0.0f)
    , m_fps_frames(0) {
}

void timer::tick() {
    static auto last_time = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = current_time - last_time;
    last_time = current_time;
    
    m_delta_time = static_cast<float>(elapsed.count());
    m_elapsed_seconds += elapsed.count();
    m_total_time += m_delta_time;
    m_frame_count++;
    
    // FPS calculation
    m_fps_accumulator += m_delta_time;
    m_fps_frames++;
    
    if (m_fps_accumulator >= 1.0f) {
        update_fps();
        m_fps_accumulator = 0.0f;
        m_fps_frames = 0;
    }
    
    m_last_frame_time = m_total_time;
}

void timer::update_fps() {
    if (m_fps_accumulator > 0.0f) {
        m_fps = static_cast<float>(m_fps_frames) / m_fps_accumulator;
    }
}

} // namespace f3d
