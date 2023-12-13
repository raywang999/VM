
#include "search_parser.h"
#include "lib/command/parser/command_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/command.h"
#include "include/utility.h"

bool SearchParser::parse(const Keystroke& keystroke) {
  std::string& sentence = theCommand.needle;
  // only Plain characters should be turned into Search
  if (keystroke.key == Key::Plain){
    if (keystroke.value == '\n'){
      notifyAll();
      reset();
    } else {
      sentence.insert(sentence.begin() + cursorCol, keystroke.value);
      ++cursorCol;
    }
  } else if (keystroke.key == Key::Arrow){
    if (keystroke.value == 'l')
      cursorCol = fit(0,sentence.size(), cursorCol-1);
    else if (keystroke.value == 'r')
      cursorCol = fit(0,sentence.size(), cursorCol+1);
  } else if (keystroke.key == Key::Backspace){
    if (cursorCol){
      sentence.erase(sentence.begin()+cursorCol-1);
      --cursorCol;
    }
  } else if (keystroke.key == Key::Esc){
    reset();
  } else {
    return false;
  } 
  return true;
}


void SearchParser::run(const SetMode* cmd) {
  theCommand.needle.clear();
  theCommand.type = cmd->type;
  cursorCol = 0;
}

