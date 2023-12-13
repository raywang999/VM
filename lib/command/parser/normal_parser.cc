#include <string>
#include <cctype>

#include "lib/command/parser/normal_parser.h"
#include "lib/command/command.h"


bool NormalParser::parse(const Keystroke& keystroke) {
  if (countedParser.parse(keystroke)) return true;
  // finished with optional multipler, parse the actual command
  theCommand.count = countedParser.getCount();
  if (keystroke.key == Key::Plain){
    if (parseData){
      // parse second part of r_, dd, yy
      // ignore d[any motion] since those are CombNM, not basic Normal 
      theCommand.data = keystroke.value;
      if (theCommand.type == theCommand.data || theCommand.type == 'r'){ 
        // we have a dd, yy, or r_
        notifyAll();
        return true;
      }
      return false;
    }
    // otherwise, we are at first part of command
    theCommand.type = keystroke.value;
    if (terminalTypes.count(keystroke.value)){
      // command is single char, don't need extra data, we're done parsing 
      notifyAll();
      return true;
    }
    // if not terminal type, then must be either d, y, r
    parseData = true; // wait for the second part
    return isNormDup(theCommand.type); // check if command type is d,y,r
  }
  // parsing failed
  return false;
}


