#ifndef MODE_INSERT_MODE_H
#define MODE_INSERT_MODE_H

#include "mode.h"

class InsertMode: public Mode {
 public: 
  InsertMode(): Mode{} {
    Mode::attach_runner();
  }
};

#endif
