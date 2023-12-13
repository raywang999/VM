#ifndef SEARCH_PARSER_H
#define SEARCH_PARSER_H

#include <cctype>
#include "lib/command/parser/command_parser.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/command.h"
#include "include/utility.h"

class SearchParser: 
  public CommandParser<Search>, 
  public CommandRunner<SetMode> // set our type when setMode is run
{
  // holds the currently parsed search command 
  Search theCommand{};
  int cursorCol = 0;
  bool parse(const Keystroke& keystroke) override;
  void run(const SetMode* cmd) override;
  void doReset() override { theCommand = Search{}; cursorCol = 0; }
 public:
  const Search* getCommand() const {return &theCommand;};
  int getCol() const noexcept {return cursorCol; }
};

#endif

