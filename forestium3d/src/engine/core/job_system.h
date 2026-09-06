#ifndef JOB_SYSTEM_H
#define JOB_SYSTEM_H

#include <cstdint>
#include <functional>

namespace f3d {

using job_function = std::function<void()>;

struct job {
    job_function func;
    uint32_t priority;
    bool completed;
};

class job_system {
public:
    job_system();
    ~job_system();
    
    bool initialize(uint32_t worker_thread_count = 0); // 0 = auto-detect
    void shutdown();
    void update();
    
    void add_job(const job_function& func, uint32_t priority = 0);
    void wait_all_jobs();
    
    uint32_t get_worker_thread_count() const { return m_worker_thread_count; }
    uint32_t get_pending_job_count() const { return m_pending_jobs; }

private:
    uint32_t m_worker_thread_count;
    uint32_t m_pending_jobs;
    bool m_running;
    
    // Work-stealing queues will be implemented here
    // TODO: Implement proper work-stealing queue system
};

} // namespace f3d

#endif // JOB_SYSTEM_H
