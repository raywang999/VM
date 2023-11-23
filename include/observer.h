#ifndef OBSERVER_H
#define OBSERVER_H

template<typename State> class Subject;

template<typename State> class Observer{
 public: 
  virtual void notify(const Subject<State>& source) =0;
  virtual ~Observer(){}
};

#endif

