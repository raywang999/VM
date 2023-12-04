#ifndef OBSERVER_H
#define OBSERVER_H


// S is the Subject we Observe
template<typename S> class Observer{
 public: 
  // observers should implement a notify in their specialization
  void notify(const S& source);
};

#endif

