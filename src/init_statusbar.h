#ifndef INIT_STATUSBAR_H
#define INIT_STATUSBAR_H

#include "init_windows.h"
#include "init_modes.h"
#include "init_cursor.h"

struct StatusBarClosure {
  WindowsClosure& windowsClosure;
  ModesClosure& modesClosure;

  StatusBarClosure(WindowsClosure& windowsClosure, ModesClosure& modesClosure): 
    windowsClosure{windowsClosure}, modesClosure{modesClosure} {}
  
  // set the required text for the root StatusBar and render
  void renderStatusBar(){ 
    auto mode = modesClosure.rootModeManager.getMode();
    auto& message = windowsClosure.rootStatusBar.left;
    if (mode == ModeType::Insert){
      message = "-- INSERT --";
    } else if (mode == ModeType::Replace){
      message = "-- REPLACE --";
    } else if (mode == ModeType::Ex){
      message = ":" + modesClosure.exParser.getSentence();
    } else {
      message = "";
    }
    if (modesClosure.macroRecorder.isActive()){
      // are in macro mode
      message.append("recording @");
      message.push_back(modesClosure.macroRunner.getCurrReg());
    }
    windowsClosure.rootStatusBar.render();
  }
};

#endif