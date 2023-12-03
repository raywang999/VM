#ifndef INSERT_PARSER_H
#define INSERT_PARSER_H

#include "lib/command/parser/command_parser.h"
#include "lib/command/command.h"

class InsertParser: public CommandParser<Insert>{
  // holds the currently parsed insert sequence 
  Insert theCommand{1,std::string{}};
  bool parse(const Keystroke& keystroke) override{
    // only Plain characters should be turned into PartialInserts
    if (keystroke.key == Key::Plain){
      theCommand.sentence.push_back(keystroke.value);
    } else if (keystroke.key == Key::Arrow){
      doReset();
    } else if (keystroke.key == Key::Esc){
      notifyAll();
    } else {
      return false;
    }
    return true;
  }
  void doReset() override { theCommand = Insert{1,std::string{}};}
 public:
  const Insert* getCommand() const {return &theCommand;};
  void setCount(int count) noexcept {theCommand.count = count;}
  void setMode(char mode) noexcept {theCommand.mode = mode;}
};

#endif

