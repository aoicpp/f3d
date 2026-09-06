#include "ecs_entity.h"
#include <cstdio>
#include <cstring>

namespace f3d {

entity_manager::entity_manager() 
    : m_active_count(0) {
    // Initialize all entities as inactive
    for (size_t i = 0; i < max_entities; ++i) {
        m_entities[i].active = false;
        m_entities[i].version = 0;
        m_free_list.push_back(static_cast<entity_id>(i));
    }
    
    printf("[f3d] Entity Manager initialized: max %zu entities\n", max_entities);
}

entity_manager::~entity_manager() {
    // Cleanup component memory
    for (size_t i = 0; i < max_entities; ++i) {
        if (m_entities[i].active) {
            for (size_t j = 0; j < max_components; ++j) {
                if (m_entities[i].components[j]) {
                    // TODO: Properly destroy components based on type
                    delete[] static_cast<uint8_t*>(m_entities[i].components[j]);
                }
            }
        }
    }
}

entity entity_manager::create_entity() {
    if (m_free_list.empty()) {
        printf("[f3d] Entity limit reached! Max: %zu\n", max_entities);
        return {invalid_entity, 0};
    }
    
    entity_id id = m_free_list.back();
    m_free_list.pop_back();
    
    m_entities[id].active = true;
    m_entities[id].version++;
    m_entities[id].mask.reset();
    
    // Zero out component pointers
    for (size_t i = 0; i < max_components; ++i) {
        m_entities[id].components[i] = nullptr;
    }
    
    m_active_count++;
    
    return {id, m_entities[id].version};
}

void entity_manager::destroy_entity(entity e) {
    if (!is_valid(e)) {
        return;
    }
    
    entity_id id = e.id;
    
    // Destroy all components
    for (size_t i = 0; i < max_components; ++i) {
        if (m_entities[id].components[i]) {
            delete[] static_cast<uint8_t*>(m_entities[id].components[i]);
            m_entities[id].components[i] = nullptr;
        }
    }
    
    m_entities[id].active = false;
    m_entities[id].mask.reset();
    m_active_count--;
    
    m_free_list.push_back(id);
}

bool entity_manager::is_valid(entity e) const {
    if (e.id >= max_entities) {
        return false;
    }
    return m_entities[e.id].active && m_entities[e.id].version == e.version;
}

component_mask entity_manager::get_component_mask(entity e) const {
    if (!is_valid(e)) {
        return component_mask();
    }
    return m_entities[e.id].mask;
}

// Explicit template instantiations will be added in a separate file
// For now, these are stubs - full implementation requires component registry

} // namespace f3d
