#ifndef MEMORY_ARENA_H
#define MEMORY_ARENA_H

#include <cstddef>
#include <cstdint>

namespace f3d {

class memory_arena {
public:
    memory_arena(size_t initial_size = 1024 * 1024); // 1MB default
    ~memory_arena();
    
    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));
    void reset();
    void clear();
    
    size_t get_used_bytes() const { return m_used_bytes; }
    size_t get_total_bytes() const { return m_total_bytes; }
    size_t get_allocation_count() const { return m_allocation_count; }
    
    float get_utilization() const;

private:
    uint8_t* m_buffer;
    size_t m_total_bytes;
    size_t m_used_bytes;
    size_t m_allocation_count;
    size_t m_peak_usage;
};

// Helper macros for arena allocation
#define F3D_ARENA_ALLOC(arena, type) \
    static_cast<type*>(arena.allocate(sizeof(type), alignof(type)))

#define F3D_ARENA_ALLOC_ARRAY(arena, type, count) \
    static_cast<type*>(arena.allocate(sizeof(type) * count, alignof(type)))

} // namespace f3d

#endif // MEMORY_ARENA_H
