#include "scene.h"
#include <cstdio>
#include <algorithm>

namespace f3d {

// scene_node implementation
scene_node::scene_node() 
    : m_parent(nullptr)
    , m_dirty(true) {
}

scene_node::~scene_node() {
    // Remove from parent's children list
    if (m_parent) {
        m_parent->remove_child(this);
    }
    
    // Destroy all children
    for (auto* child : m_children) {
        delete child;
    }
    m_children.clear();
}

void scene_node::set_name(const std::string& name) {
    m_name = name;
}

void scene_node::set_parent(scene_node* parent) {
    if (m_parent) {
        m_parent->remove_child(this);
    }
    
    m_parent = parent;
    
    if (m_parent) {
        m_parent->add_child(this);
    }
}

void scene_node::add_child(scene_node* child) {
    if (!child) return;
    
    // Check if already a child
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it == m_children.end()) {
        m_children.push_back(child);
        child->m_parent = this;
        m_dirty = true;
    }
}

void scene_node::remove_child(scene_node* child) {
    if (!child) return;
    
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        child->m_parent = nullptr;
        m_dirty = true;
    }
}

void scene_node::set_transform(const transform& t) {
    m_transform = t;
    m_dirty = true;
}

// scene implementation
scene::scene() 
    : m_root(nullptr)
    , m_node_counter(0) {
    m_name = "Untitled Scene";
    
    // Create root node (Workspace equivalent)
    m_root = new scene_node();
    m_root->set_name("Workspace");
    m_all_nodes.push_back(m_root);
}

scene::~scene() {
    if (m_root) {
        delete m_root;
        m_root = nullptr;
    }
    m_all_nodes.clear();
}

void scene::set_name(const std::string& name) {
    m_name = name;
}

scene_node* scene::create_node(node_type type) {
    scene_node* node = nullptr;
    
    switch (type) {
        case node_type::part:
            // TODO: Create part instance
            node = new scene_node();
            break;
        case node_type::light:
            // TODO: Create light instance
            node = new scene_node();
            break;
        case node_type::camera:
            // TODO: Create camera instance
            node = new scene_node();
            break;
        case node_type::sound:
            // TODO: Create sound emitter instance
            node = new scene_node();
            break;
        case node_type::script:
            // TODO: Create script instance
            node = new scene_node();
            break;
        case node_type::folder:
            node = new scene_node();
            break;
        default:
            node = new scene_node();
            break;
    }
    
    if (node) {
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "Node_%llu", m_node_counter++);
        node->set_name(buffer);
        
        // Add to root by default
        m_root->add_child(node);
        m_all_nodes.push_back(node);
    }
    
    return node;
}

void scene::destroy_node(scene_node* node) {
    if (!node || node == m_root) return;
    
    // Remove from parent
    if (node->get_parent()) {
        node->get_parent()->remove_child(node);
    }
    
    // Remove from all nodes list
    auto it = std::find(m_all_nodes.begin(), m_all_nodes.end(), node);
    if (it != m_all_nodes.end()) {
        m_all_nodes.erase(it);
    }
    
    // Delete the node (destructor handles children cleanup)
    delete node;
}

scene_node* scene::find_node_by_name(const std::string& name) {
    for (auto* node : m_all_nodes) {
        if (node && node->get_name() == name) {
            return node;
        }
    }
    return nullptr;
}

scene_node* scene::find_node_by_path(const std::string& path) {
    // Simple path resolution: "Workspace/Part1/SubPart"
    // TODO: Implement full path resolution
    size_t last_slash = path.rfind('/');
    if (last_slash != std::string::npos) {
        std::string node_name = path.substr(last_slash + 1);
        return find_node_by_name(node_name);
    }
    return find_node_by_name(path);
}

bool scene::load_from_file(const std::string& filepath) {
    printf("[f3d] Loading scene from: %s\n", filepath.c_str());
    
    // TODO: Parse .f3d scene file format
    // Format is text-based like Roblox .rbxl
    
    (void)filepath;
    return false; // Stub
}

bool scene::save_to_file(const std::string& filepath) {
    printf("[f3d] Saving scene to: %s\n", filepath.c_str());
    
    // TODO: Serialize scene to .f3d format
    
    (void)filepath;
    return false; // Stub
}

void scene::update(float delta_time) {
    // TODO: Update all nodes in the scene
    (void)delta_time;
}

} // namespace f3d
