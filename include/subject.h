#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

template<typename T> class Observer;

// Apply CRTP
template<typename State, typename S> class Subject{
  std::vector<Observer<S>*> attachedObservers;
 public: 
  Subject() = default;
  void attach(Observer<S>* ob) {attachedObservers.push_back(ob); }
  // iterate through attachedObservers, calling their notify()
  // the private subclasses should pass this
  void notifyAll(S* sub) {
    for (auto obp: attachedObservers){
      obp->notify(*sub);
    }
  }
};

#endif

