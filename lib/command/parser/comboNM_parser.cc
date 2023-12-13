#include "lib/command/parser/comboNM_parser.h"
#include "lib/command/command.h"

bool ComboNMParser::parse(const Keystroke& keystroke) {
  if (countedParser.parse(keystroke)) return true;
  // finished with multipler, parse the actual command
  if (keystroke.key == Key::Plain){
    if (parseNormal) { // check if d,y. If so, continue to parse movement
      if (!isNormDup(keystroke.value)) return false;
      theCommand.normal.count = countedParser.getCount();
      theCommand.normal.type = keystroke.value;
      parseNormal = false;
      return true;
    }
    // o.w. parse the movement
    movementParser.consume(keystroke);
    return movementParser.isValid();
  }
  // parsing failed
  return false;
}

void ComboNMParser::run(const Movement* cmd){
  theCommand.movement = *cmd;
  notifyAll();
}


