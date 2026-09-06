#include "event_bus.h"
#include <cstdio>
#include <algorithm>

namespace f3d {

event_bus::event_bus() 
    : m_next_subscription_id(1)
    , m_is_flushing(false) {
}

event_bus::~event_bus() {
    m_subscriptions.clear();
    m_pending_subscriptions.clear();
}

uint32_t event_bus::subscribe(event_type type, const event_callback& callback) {
    uint32_t id = m_next_subscription_id++;
    
    if (m_is_flushing) {
        // Add to pending if we're currently flushing
        m_pending_subscriptions.push_back({type, callback, id});
    } else {
        m_subscriptions.push_back({type, callback, id});
    }
    
    return id;
}

void event_bus::unsubscribe(uint32_t subscription_id) {
    if (m_is_flushing) {
        // Defer unsubscription if we're currently flushing
        m_pending_unsubscribes.push_back(subscription_id);
    } else {
        auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(),
            [subscription_id](const event_subscription& sub) {
                return sub.id == subscription_id;
            });
        
        if (it != m_subscriptions.end()) {
            m_subscriptions.erase(it);
        }
    }
}

void event_bus::unsubscribe_all(event_type type) {
    if (m_is_flushing) {
        // Collect all IDs to unsubscribe
        for (const auto& sub : m_subscriptions) {
            if (sub.type == type) {
                m_pending_unsubscribes.push_back(sub.id);
            }
        }
    } else {
        m_subscriptions.erase(
            std::remove_if(m_subscriptions.begin(), m_subscriptions.end(),
                [type](const event_subscription& sub) {
                    return sub.type == type;
                }),
            m_subscriptions.end()
        );
    }
}

void event_bus::publish(event_type type, void* data) {
    // Queue the event for processing in flush()
    // For simplicity, we'll call callbacks directly here
    // A more robust implementation would queue events
    
    for (auto& sub : m_subscriptions) {
        if (sub.type == type && sub.callback) {
            sub.callback(type, data);
        }
    }
}

void event_bus::flush() {
    m_is_flushing = true;
    
    // Process pending subscriptions
    for (auto& sub : m_pending_subscriptions) {
        m_subscriptions.push_back(sub);
    }
    m_pending_subscriptions.clear();
    
    // Process pending unsubscriptions
    for (uint32_t id : m_pending_unsubscribes) {
        auto it = std::find_if(m_subscriptions.begin(), m_subscriptions.end(),
            [id](const event_subscription& sub) {
                return sub.id == id;
            });
        
        if (it != m_subscriptions.end()) {
            m_subscriptions.erase(it);
        }
    }
    m_pending_unsubscribes.clear();
    
    m_is_flushing = false;
}

} // namespace f3d
