#ifndef INSERT_PARSER_H
#define INSERT_PARSER_H

#include <string>

#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/command.h"

class InsertParser: public CommandParser<Insert>{
  // holds the currently parsed insert sequence 
  Insert theCommand{1,std::string{}};
  bool parse(const Keystroke& keystroke) override{
    // only Plain characters should be turned into PartialInserts
    if (keystroke.key == Key::Plain){
      theCommand.sentence.push_back(keystroke.value);
      return true;
    }
    if (keystroke.key == Key::Esc){
      notifyAll();
      return true;
    }
    return false;
  }
  void doReset() override { theCommand = Insert{1,std::string{}};}
 public:
  const Insert* getCommand() const {return &theCommand;};
  void setCount(int count) noexcept {theCommand.count = count;}
};

#endif

