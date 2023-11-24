#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"
#include "lib/command/normal_parser.h"

// set storing which command types are terminals, i.e. don't need extra data
std::unordered_set<int> terminalTypes{
  'a', 'i', 'o', 'p', 's', 'u', 'x', 
  'A', 'I', 'J', 'O', 'P', 'R', 'S', 'X', '.'
};

// returns true for double operations 
bool isNormDup(int ch){
  return ch == 'c' || ch == 'd' || ch == 'y';
}

bool NormalParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Plain){
    if (parseStatus == First){
      // parse a possible count 
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
        // don't need extra data, i.e. we're done parsing 
        notifyAll();
        return true;
      }
      // if not terminal type, then must be either c,d,y
      return isNormDup(theCommand.type);
    }
    if (parseStatus == Type){
      // parse commands like cc, dd, yy
      // ignore d[any motion] since those are CombNM, not basic Normal 
      theCommand.data = keystroke.value;
      if (theCommand.type == theCommand.data){
        // we have a dd, cc, yy
        notifyAll();
        return true;
      }
    }
  }

  // parsing failed
  return false;
}
