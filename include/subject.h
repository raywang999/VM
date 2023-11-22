#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

template<typename State> class Observer;

template<typename State> class Subject{
  std::vector<Observer<State>*> attachedObservers;
 public: 
  Subject() = default;
  void attach(Observer<State>* ob) {attachedObservers.push_back(ob); }
  void notifyAll();
  virtual State getState() const =0;
};

template<typename State> 
void Subject<State>::notifyAll(){
  for (auto obp: attachedObservers){
    obp->notify(*this);
  }
}


#endif

