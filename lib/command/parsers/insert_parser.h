#ifndef INSERT_PARSER_H
#define INSERT_PARSER_H

#include <cctype>
#include <memory>

#include "../command_parser.h"
#include "../commands/insert_command.h"

class InsertParser: public CommandParser{
  unique_ptr<Command> theCommand{nullptr}; 
  bool parseKeystroke(Keystroke& keystroke){
    // normal characters should be turned into inserts
    if (isalphanum(keystroke)){
      theCommand = make_unique(InsertCommand{keystroke});
      return true;
    }

  }
};

#endif

