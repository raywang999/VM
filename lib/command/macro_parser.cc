#include <cctype>

#include "lib/command/command.h"
#include "lib/command/macro_parser.h"

// first read an optional count
// then read a `q`, then read a register 
bool MacroParser::parse(const Keystroke& keystroke) {
  if (countedParser.parse(keystroke)) return true;
  theMacro.count = countedParser.getCount();
  if (keystroke.key == Key::Plain){
    if (readRegister){ // parse the second part (the register)
      if (isalnum(keystroke.value)){
        theMacro.reg = keystroke.value;
        notifyAll();
        return true;
      }
      return false;
    }
    // otherwise, parse q or @
    theMacro.type = keystroke.value;
    readRegister = true;
    return keystroke.value == 'q' || keystroke.value == '@';
  }

  // parsing failed
  return false;
}

