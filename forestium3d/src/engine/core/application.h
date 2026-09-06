#ifndef APPLICATION_H
#define APPLICATION_H

namespace f3d {

class application {
public:
    bool initialize();
    void update(float delta_time);
    void render();
    void shutdown();

private:
    bool m_initialized;
};

} // namespace f3d

#endif // APPLICATION_H
