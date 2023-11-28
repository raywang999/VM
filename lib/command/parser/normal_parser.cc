#include <string>
#include <cctype>
#include <unordered_set>

#include "lib/command/parser/normal_parser.h"
#include "lib/command/command.h"

// returns true for double operations 
bool isNormDup(int ch){
  return ch == 'c' || ch == 'd' || ch == 'y';
}

// set storing which command types are terminals, i.e. don't need extra data
const std::unordered_set<int> normalTerminalTypes{
  'a', 'i', 'o', 'p', 's', 'u', 'x', 
  'A', 'I', 'J', 'O', 'P', 'R', 'S', 'X', '.'
};


bool NormalParser::parse(const Keystroke& keystroke) {
  if (countedParser.parse(keystroke)) return true;
  // finished with optional multipler, parse the actual command
  theCommand.count = countedParser.getCount();
  if (keystroke.key == Key::Plain){
    if (parseData){
      // parse second part of cc, dd, yy
      // ignore d[any motion] since those are CombNM, not basic Normal 
      theCommand.data = keystroke.value;
      if (theCommand.type == theCommand.data){
        // we have a dd, cc, yy
        notifyAll();
        return true;
      }
      return false;
    }
    // otherwise, we are at first part of command
    theCommand.type = keystroke.value;
    if (normalTerminalTypes.count(keystroke.value)){
      // command is single char, don't need extra data, we're done parsing 
      notifyAll();
      return true;
    }
    // if not terminal type, then must be either c,d,y
    parseData = true; // wait for the second part
    return isNormDup(theCommand.type); // check if command is cc,dd,yy
  }
  // parsing failed
  return false;
}


