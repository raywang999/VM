#ifndef OBSERVER_H
#define OBSERVER_H

template<typename State> class Subject;

template<typename State> class Observer{
 public: 
  virtual void notify(Subject& source) =0;
};

#endif

