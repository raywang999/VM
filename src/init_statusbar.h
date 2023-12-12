#ifndef INIT_STATUSBAR_H
#define INIT_STATUSBAR_H

#include "init_windows.h"
#include "init_modes/init_modes.h"
#include "init_cursor.h"

struct StatusBarClosure {
  WindowsClosure& windowsClosure;
  ModesClosure& modesClosure;

  StatusBarClosure(WindowsClosure& windowsClosure, ModesClosure& modesClosure): 
    windowsClosure{windowsClosure}, modesClosure{modesClosure} {}
  
  // set the required text for the root StatusBar and render
  void renderStatusBar(){ 
    auto mode = modesClosure.rootModeManager.getMode();
    auto& message = windowsClosure.rootStatusRender.content;
    auto& rootStatus = windowsClosure.rootStatus;
    auto error = rootStatus.getError();
    const auto& exMessage = rootStatus.getMessage();
    windowsClosure.rootStatusRender.showerror = false;
    if (mode == ModeType::Ex){
      // show the currently parsed Ex Command
      rootStatus.reset();
      message = ":" + modesClosure.exParser.getSentence();
    } else if (error != ErrorCode::nothing){
      if (error == ErrorCode::noWriteSinceLastChange){
        message = "E37: No write since last change (add ! to override)";
      } else if (error == ErrorCode::noFileName){
        message = "E32: No file name";
      }
      windowsClosure.rootStatusRender.showerror = true;
    } else if (exMessage.size()) { 
      // show the exMessage 
      message = exMessage;
    } else { // nothing special, so show the mode 
      if (mode == ModeType::Insert){
        message = "-- INSERT --";
      } else if (mode == ModeType::Replace){
        message = "-- REPLACE --";
      } else {
        message = "";
      }
      if (modesClosure.macroRecorder.isActive()){
        // are in macro mode
        message.append("recording @");
        message.push_back(modesClosure.macroRunner.getCurrReg());
      }
    }
    windowsClosure.rootStatusRender.render();
  }
};

#endif