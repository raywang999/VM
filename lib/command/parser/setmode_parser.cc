#include <string>
#include <cctype>

#include "lib/command/parser/setmode_parser.h"
#include "lib/command/command.h"

bool SetModeParser::parse(const Keystroke& keystroke) {
  if (countedParser.parse(keystroke)) return true;
  // finished with optional multipler, parse the actual command
  basicSetMode.count = countedParser.getCount();
  if (keystroke.key == Key::Plain){
    if (checkCC){  // check if we parsed a cc command
      if (keystroke.value == 'c') { // turn cc into S and notify
        basicSetMode.type = 'S'; 
        notifyAll();
        return true;
      } else { // not a cc, but could be a c_movement
        checkCC = false; 
        useCombo = true;
      }
    }
    if (useCombo){ // parse the movemnt 
      // note: if movementParser finishes, it will notify us, and call our run
      movementParser.consume(keystroke);
    } else { // otherwise, check if terminal
      basicSetMode.type = keystroke.value;
      if (terminalTypes.count(keystroke.value)){ // we are done
        notifyAll();
        return true;
      } else if (keystroke.value == 'c') {  // handle for c, c_
        checkCC = true;
        return true;
      } else {
        return false;
      }
    }
  }
  // parsing failed
  return false;
}

void SetModeParser::run(const Movement* cmd) {
  comboSetMode.movement = *cmd;
  notifyAll();
}


