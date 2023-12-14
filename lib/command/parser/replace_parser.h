#ifndef REPLACE_PARSER_H
#define REPLACE_PARSER_H

#include "lib/command/parser/command_parser.h"
#include "lib/command/command.h"

class ReplaceParser: public CommandParser<Replace>{
  // holds the currently parsed insert sequence 
  Replace theCommand{1, std::string{}};
  bool parse(const Keystroke& keystroke) override{
    auto& sentence = theCommand.sentence;
    // only Plain characters should be turned into PartialReplaces
    if (keystroke.key == Key::Plain){
      sentence.push_back(keystroke.value);
    } else if (keystroke.key == Key::Arrow){
      // arrow key discards the type of insert, and restarts parsing
      doReset();
    } else if (keystroke.key == Key::Esc){
      notifyAll();
      doReset();
    } else if (keystroke.key == Key::Backspace){
      if (sentence.size()){
        sentence.pop_back();
      }
    } else {
      return false;
    }
    return true;
  }
  void doReset() override { theCommand = Replace{1,std::string{}};}
 public:
  const Replace* getCommand() const {return &theCommand;};
  void setCount(int count) noexcept {theCommand.count = count;}
};

#endif

  