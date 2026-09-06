#include "memory_arena.h"
#include <cstdio>
#include <cstring>
#include <algorithm>

namespace f3d {

memory_arena::memory_arena(size_t initial_size) 
    : m_buffer(nullptr)
    , m_total_bytes(initial_size)
    , m_used_bytes(0)
    , m_allocation_count(0)
    , m_peak_usage(0) {
    
    m_buffer = new uint8_t[m_total_bytes];
    printf("[f3d] Memory Arena created: %zu bytes\n", m_total_bytes);
}

memory_arena::~memory_arena() {
    clear();
}

void* memory_arena::allocate(size_t size, size_t alignment) {
    if (size == 0) {
        return nullptr;
    }
    
    // Align the current position
    size_t aligned_pos = (m_used_bytes + alignment - 1) & ~(alignment - 1);
    
    // Check if we have enough space
    if (aligned_pos + size > m_total_bytes) {
        printf("[f3d] Memory Arena exhausted! Requested: %zu, Available: %zu\n", 
               size, m_total_bytes - aligned_pos);
        return nullptr;
    }
    
    void* ptr = m_buffer + aligned_pos;
    m_used_bytes = aligned_pos + size;
    m_allocation_count++;
    
    if (m_used_bytes > m_peak_usage) {
        m_peak_usage = m_used_bytes;
    }
    
    return ptr;
}

void memory_arena::reset() {
    m_used_bytes = 0;
    m_allocation_count = 0;
}

void memory_arena::clear() {
    if (m_buffer) {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
    m_used_bytes = 0;
    m_total_bytes = 0;
    m_allocation_count = 0;
    m_peak_usage = 0;
}

float memory_arena::get_utilization() const {
    if (m_total_bytes == 0) {
        return 0.0f;
    }
    return static_cast<float>(m_peak_usage) / static_cast<float>(m_total_bytes) * 100.0f;
}

} // namespace f3d
