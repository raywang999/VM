#include <cctype>

#include "lib/command/command.h"
#include "lib/command/macro_parser.h"

// first read an optional count
// then read a `q`, then read a register 
bool ReadMacroParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Plain){
    if (parseStatus == First){
      if (isdigit(keystroke.value)){
        theCommand.count = keystroke.value - '0';
        return true;
      }
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

