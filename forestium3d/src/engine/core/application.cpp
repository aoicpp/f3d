#include "application.h"
#include <cstdio>

namespace f3d {

bool application::initialize() {
    printf("[f3d] Application initializing...\n");
    m_initialized = true;
    printf("[f3d] Application initialized\n");
    return true;
}

void application::update(float delta_time) {
    // Update game logic here
    (void)delta_time;
}

void application::render() {
    // Render scene here
}

void application::shutdown() {
    printf("[f3d] Application shutting down...\n");
    m_initialized = false;
}

} // namespace f3d
