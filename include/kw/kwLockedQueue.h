#ifndef KW_LOCKEDQUEUE
#define KW_LOCKEDQUEUE


#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class kwLockedQueue
{
 public:
 kwLockedQueue()
   : m_queue()
    , m_mutex()
    , m_cond()
  {
    m_bThreaded = false;
  }

 kwLockedQueue(bool threaded)
   : m_queue()
    , m_mutex()
    , m_cond()
  {
    m_bThreaded = threaded;
  }

  ~kwLockedQueue()
  {
  }

  void push(T t)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(t);
    if (m_bThreaded)
      m_cond.notify_one();
  }

  T pop()
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_queue.empty())
    {
      m_cond.wait(lock);
    }
    T val = m_queue.front();
    m_queue.pop();
    return val;
  }

  bool Threaded()
  {
    return m_bThreaded;
  }

  bool empty()
  {
    return m_queue.empty();
  }
  
 private:
  bool m_bThreaded;
  std::queue<T> m_queue;
  mutable std::mutex m_mutex;
  std::condition_variable m_cond;
};      
    

#endif
