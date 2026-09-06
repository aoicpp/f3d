#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

namespace f3d {

class timer {
public:
    timer();
    
    void tick();
    
    float get_delta_time() const { return m_delta_time; }
    float get_total_time() const { return m_total_time; }
    double get_elapsed_seconds() const { return m_elapsed_seconds; }
    
    uint64_t get_frame_count() const { return m_frame_count; }
    float get_fps() const { return m_fps; }

private:
    void update_fps();

    double m_elapsed_seconds;
    float m_delta_time;
    float m_total_time;
    float m_last_frame_time;
    
    uint64_t m_frame_count;
    float m_fps;
    float m_fps_accumulator;
    uint32_t m_fps_frames;
};

} // namespace f3d

#endif // TIMER_H
