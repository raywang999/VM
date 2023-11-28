#include <string>
#include <cctype>

#include "lib/command/command.h"
#include "lib/command/parser/ctrl_parser.h"

// if Key::Ctrl, finish parsing and broadcast
// otherwise, parse optional count
bool CtrlParser::parse(const Keystroke& keystroke) {
  if (keystroke.key == Key::Ctrl){
    theCommand.count = countedParser.getCount();
    theCommand.type = keystroke.value;
    notifyAll();
    return true;
  }
  return countedParser.parse(keystroke);
}

