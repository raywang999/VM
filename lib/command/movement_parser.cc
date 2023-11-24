#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/command.h"
#include "lib/command/movement_parser.h"

// set storing which command types are terminals, i.e. don't need extra seek
std::unordered_set<int> terminalTypes{
  'b', 'h', 'j', 'k', 'l', 'n', 'w', 
  'F', 'N', '^', '$', '0', '%', ';'
};

bool MovementParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Plain){
    if (parseStatus == First){
      // if 0, then this is the `0` movement, not a count
      if (keystroke.value == '0'){
        theCommand.count = 1; 
        theCommand.type = '0';
        notifyAll();
        return true;
      }
      // o.w. parse a possible count 
      parseStatus = Count;
      if (isdigit(keystroke.value)){
        // start parsing a count
        theCommand.count = keystroke.value-'0';
        return true;
      } 
      // if no count, consider as if we were parsing a count 1, and continue from below
      theCommand.count = 1;
    } 
    if (parseStatus == Count){
      // we were parsing a count before now
      if (isdigit(keystroke.value)){
        // continue parsing a count 
        theCommand.count = theCommand.count*10+keystroke.value-'0';
        return true;
      } 
      // otherwise, finished parsing count, parse the type 
      parseStatus = Type;
      theCommand.type = keystroke.value;
      if (terminalTypes.count(keystroke.value)){
        // don't need extra seek, i.e. we're done parsing 
        notifyAll();
        return true;
      }
      return theCommand.type == 'f' || theCommand.type == 'F';
    }
    if (parseStatus == Type){
      // parse commands like f_, F_, 
      theCommand.seek = keystroke.value;
      notifyAll();
      return true;
    }
  }

  // parsing failed
  return false;
}

