#ifndef ROOT_STATUS_BAR_H
#define ROOT_STATUS_BAR_H

#include <string>

// status bar on bottom of the screen
// stores the information 
class RootStatusBar {
 public:
  std::string left, mid, right;
  bool showerror = false;
  //void render() override;
};

#endif