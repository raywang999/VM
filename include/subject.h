#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

template<typename State> class Observer;

template<typename State> class Subject{
  std::vector<Observer<State>*> attachedObservers;
 public: 
  Subject() = default;
  void attach(Observer<State>* ob) {attachedObservers.push_back(ob); }
  // iterate through attachedObservers, calling their notify()
  void notifyAll();
  // subclasses override this function 
  virtual State getState() const =0;
  virtual ~Subject(){}
};

template<typename State> 
inline void Subject<State>::notifyAll(){
  for (auto obp: attachedObservers){
    obp->notify(*this);
  }
}


#endif

