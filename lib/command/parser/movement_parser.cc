#include <string>
#include <cctype>

#include "lib/command/command.h"
#include "lib/command/parser/movement_parser.h"

bool MovementParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Plain){
    if (first){ // if first is 0, then this is the `0` movement, not a count
      if (keystroke.value == '0'){
        theCommand.count = 1; 
        theCommand.type = '0';
        notifyAll();
        return true;
      }
    }
    // otherwise, try parsing count 
    if (countedParser.parse(keystroke)) return true;
    // finished with optional multipler, parse the actual command
    theCommand.count = countedParser.getCount();
    if (parseSeek){ // parse the second part of f_, F_
      theCommand.seek = keystroke.value;
      notifyAll();
      return true;
    }
    // otherwise, we are in the first part 
    theCommand.type = keystroke.value;
    if (terminalTypes.count(keystroke.value)){
      // don't need extra seek, i.e. we're done parsing 
      notifyAll();
      return true;
    }
    // we need to parse a second part later
    parseSeek = true;
    return theCommand.type == 'f' || theCommand.type == 'F';
  }

  // parsing failed
  return false;
}

