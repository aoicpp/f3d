#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include <cstdint>
#include <vector>
#include <bitset>

namespace f3d {

using entity_id = uint32_t;
using component_mask = std::bitset<64>;

constexpr entity_id invalid_entity = UINT32_MAX;
constexpr size_t max_components = 64;
constexpr size_t max_entities = 100000;

// Component types (register your components here)
enum class component_type : uint8_t {
    transform = 0,
    mesh_renderer,
    camera,
    light,
    rigid_body,
    collider,
    audio_source,
    script,
    tag,
    custom_0,
    custom_1,
    custom_2,
    custom_3,
    count
};

struct entity {
    entity_id id;
    uint32_t version;
    
    bool is_valid() const { return id != invalid_entity; }
    bool operator==(const entity& other) const { return id == other.id && version == other.version; }
    bool operator!=(const entity& other) const { return !(*this == other); }
};

class entity_manager {
public:
    entity_manager();
    ~entity_manager();
    
    entity create_entity();
    void destroy_entity(entity e);
    
    bool is_valid(entity e) const;
    
    template<typename T>
    void add_component(entity e);
    
    template<typename T>
    void remove_component(entity e);
    
    template<typename T>
    bool has_component(entity e) const;
    
    template<typename T>
    T* get_component(entity e);
    
    template<typename T>
    const T* get_component(entity e) const;
    
    component_mask get_component_mask(entity e) const;
    
    size_t get_active_entity_count() const { return m_active_count; }
    size_t get_max_entities() const { return max_entities; }

private:
    struct entity_record {
        uint32_t version;
        component_mask mask;
        bool active;
        void* components[max_components]; // Pointers to component data
        
        entity_record() : version(0), active(false) {
            for (size_t i = 0; i < max_components; ++i) {
                components[i] = nullptr;
            }
        }
    };
    
    entity_record m_entities[max_entities];
    std::vector<entity_id> m_free_list;
    size_t m_active_count;
};

// System base class
class system {
public:
    virtual ~system() = default;
    virtual void update(float delta_time) = 0;
    virtual component_mask get_required_components() const = 0;
};

} // namespace f3d

#endif // ECS_ENTITY_H
