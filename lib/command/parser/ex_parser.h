#ifndef EX_PARSER_H
#define EX_PARSER_H

#include <cctype>
#include "lib/command/parser/command_parser.h"
#include "lib/command/command.h"
#include "include/utility.h"

class ExParser: public CommandParser<Ex>{
  // holds the current sentence
  std::string sentence;
  // holds the currently parsed ex command 
  Ex theCommand{};
  int cursorCol = 0;
  bool parse(const Keystroke& keystroke) override{
    // only Plain characters should be turned into Ex
    if (keystroke.key == Key::Plain){
      if (keystroke.value == '\n'){
        theCommand = Ex{sentence};
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
  void doReset() override { theCommand = Ex{}; cursorCol = 0; sentence.clear(); }
 public:
  const Ex* getCommand() const {return &theCommand;};
  const std::string& getSentence() const {return sentence;};
  int getCol() const noexcept {return cursorCol; }
};

#endif

