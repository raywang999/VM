#ifndef RESETABLE_H
#define RESETABLE_H

class Resetable {
  // give subclass a way to reset its internal state, if necessary
  virtual void doReset(){};
  // class is in a valid state
  bool valid = true;
 protected:
  void set(bool valid) {this->valid = valid;}
 public: 
  // reset to a valid state 
  void reset() {valid = true; doReset();}
  bool isValid() const {return valid; }
};

#endif
