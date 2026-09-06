#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <cstdint>

namespace f3d {

// Forward declarations
class scene_node;
class camera;
class light;
class part;
class script_instance;
class sound_emitter;

enum class node_type : uint8_t {
    none = 0,
    model,
    part,
    light,
    camera,
    sound,
    script,
    folder
};

struct transform {
    float position[3];    // x, y, z
    float rotation[3];    // pitch, yaw, roll (Euler angles)
    float scale[3];       // sx, sy, sz
    
    transform() {
        position[0] = position[1] = position[2] = 0.0f;
        rotation[0] = rotation[1] = rotation[2] = 0.0f;
        scale[0] = scale[1] = scale[2] = 1.0f;
    }
};

class scene_node {
public:
    scene_node();
    virtual ~scene_node();
    
    void set_name(const std::string& name);
    void set_parent(scene_node* parent);
    void add_child(scene_node* child);
    void remove_child(scene_node* child);
    
    const std::string& get_name() const { return m_name; }
    scene_node* get_parent() const { return m_parent; }
    const std::vector<scene_node*>& get_children() const { return m_children; }
    
    void set_transform(const transform& t);
    const transform& get_transform() const { return m_transform; }
    
    virtual node_type get_type() const { return node_type::none; }
    
    bool is_a(node_type type) const { return get_type() == type; }
    
    template<typename T>
    T* as() {
        return is_a(T::static_type()) ? static_cast<T*>(this) : nullptr;
    }
    
    template<typename T>
    const T* as() const {
        return is_a(T::static_type()) ? static_cast<const T*>(this) : nullptr;
    }

protected:
    std::string m_name;
    scene_node* m_parent;
    std::vector<scene_node*> m_children;
    transform m_transform;
    bool m_dirty;
};

class scene {
public:
    scene();
    ~scene();
    
    void set_name(const std::string& name);
    const std::string& get_name() const { return m_name; }
    
    scene_node* get_root() const { return m_root; }
    
    scene_node* create_node(node_type type);
    void destroy_node(scene_node* node);
    
    scene_node* find_node_by_name(const std::string& name);
    scene_node* find_node_by_path(const std::string& path);
    
    bool load_from_file(const std::string& filepath);
    bool save_to_file(const std::string& filepath);
    
    void update(float delta_time);

private:
    std::string m_name;
    scene_node* m_root;
    std::vector<scene_node*> m_all_nodes;
    uint64_t m_node_counter;
};

} // namespace f3d

#endif // SCENE_H
