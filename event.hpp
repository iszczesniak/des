#ifndef EVENT_HPP
#define EVENT_HPP

#include "module.hpp"

template <typename S>
class event
{
  // The time of the event.
  typename S::time_type m_t;
  // The module of the event.  We need a pointer, not a reference to a
  // module, because events are pushed into priority_queue, which
  // maintains its elements in a heap, and the heap in turn swaps its
  // elements, which uses the (more or copy) assignment operator.  For
  // this reason you cannot make a reference bind (reinitialize,
  // rebind) to a new expression.
  module<S> *m_m;

public:
  event(typename S::time_type t, module<S> *m): m_t(t), m_m(m)
  {
  }

  void process() const
  {
    (*m_m)(m_t);
  }

  // Needed for sorting the events in the priority queue.
  bool operator<(const event<S> &e) const
  {
    return m_t > e.m_t;
  }

  typename S::time_type get_time() const
  {
    return m_t;
  }
};

#endif /* EVENT_HPP */
