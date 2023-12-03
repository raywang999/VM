#ifndef NC_ROOT_STATUS_BAR_H
#define NC_ROOT_STATUS_BAR_H

#include "include/renderable.h"
#include "root_status.h"

// status bar on bottom left of the screen
// stores general information like ExLine message, error-codes
struct NCRootStatusBar: public RootStatusBar, public Renderable{
 public:
  int error_code = false;
};

#endif