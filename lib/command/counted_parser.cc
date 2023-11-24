#include <cctype>

#include "lib/command/command.h"
#include "lib/command/counted_parser.h"

bool CountedParser::parse(const Keystroke& keystroke) {
  if (!valid) return false;
  // parse the count 
  if (keystroke.key == Key::Plain && isdigit(keystroke.value)){
    if (first){ // initial setup 
      first = false;
      theCount = 0;
    }
    theCount = theCount*10+keystroke.value-'0';
    return true;
  }
  // not a digit, so fail and set theCount to 1 if `first==true`
  if (first){ theCount = 1; }
  return valid = false;
}

