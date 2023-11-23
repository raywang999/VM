#ifndef INSERT_PARSER_H
#define INSERT_PARSER_H

#include <string>

#include "lib/command/command_parser.h"
#include "lib/command/command.h"

class InsertParser: public CommandParser{
  // holds the currently parsed insert sequence 
  Insert theCommand{std::string{}};
  bool parse(const Keystroke& keystroke) override{
    // only Plain characters should be turned into PartialInserts
    if (keystroke.key == Key::Plain){
      theCommand.sentence.push_back(keystroke.value);
      return true;
    }
  }
  void doReset() override { theCommand = Insert{std::string{}};}
  Command getState() const override {return theCommand;};
};

#endif

