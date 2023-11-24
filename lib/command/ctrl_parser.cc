#include <string>
#include <cctype>

#include "lib/command/command.h"
#include "lib/command/ctrl_parser.h"

// if digit, change count 
// otherwise, if Key::Ctrl, finish parsing and broadcast
bool CtrlParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Ctrl){
    theCommand.type = keystroke.value;
    notifyAll();
    return true;
  }
  if (keystroke.key == Key::Plain && isdigit(keystroke.value)){
    if (parseStatus == First){
      parseStatus = Count;
      theCommand.count = 0;
    }
    if (parseStatus == Count){
      // we were parsing a count before now
      if (isdigit(keystroke.value)){
        // continue parsing a count 
        theCommand.count = theCommand.count*10+keystroke.value-'0';
        return true;
      } 
    }
  }

  // parsing failed
  return false;
}

