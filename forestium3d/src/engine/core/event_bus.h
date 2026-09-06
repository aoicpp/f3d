#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <cstdint>
#include <functional>
#include <vector>

namespace f3d {

enum class event_type : uint8_t {
    none = 0,
    window_resize,
    window_close,
    key_pressed,
    key_released,
    mouse_button_pressed,
    mouse_button_released,
    mouse_moved,
    mouse_scrolled,
    gamepad_connected,
    gamepad_disconnected,
    scene_loaded,
    scene_unloaded,
    entity_created,
    entity_destroyed,
    component_added,
    component_removed,
    physics_collision,
    audio_play,
    audio_stop,
    custom
};

using event_callback = std::function<void(event_type, void*)>;

struct event_subscription {
    event_type type;
    event_callback callback;
    uint32_t id;
};

class event_bus {
public:
    event_bus();
    ~event_bus();
    
    uint32_t subscribe(event_type type, const event_callback& callback);
    void unsubscribe(uint32_t subscription_id);
    void unsubscribe_all(event_type type);
    
    void publish(event_type type, void* data = nullptr);
    void flush();

private:
    std::vector<event_subscription> m_subscriptions;
    std::vector<event_subscription> m_pending_subscriptions;
    std::vector<uint32_t> m_pending_unsubscribes;
    uint32_t m_next_subscription_id;
    bool m_is_flushing;
};

} // namespace f3d

#endif // EVENT_BUS_H
