#ifndef SETMODE_PARSER_H
#define SETMODE_PARSER_H

#include <unordered_set>

#include "lib/command/runner/command_runner.h"
#include "lib/command/parser/command_parser.h"
#include "lib/command/parser/counted_parser.h"
#include "lib/command/parser/movement_parser.h"
#include "lib/command/command.h"

// parse e.g. A,I,i,o,O,c_
class SetModeParser: 
  public CommandParser<SetMode>,
  public CommandRunner<Movement>
{
  CountedParser countedParser;
  // basic A,I,i,etc.
  SetMode basicSetMode{};
  CM comboSetMode{}; // c_ type
  MovementParser movementParser; // used to parse CM
  bool checkCC = false;
  bool useCombo = false;

  // set of all basic setMode types
  inline static const std::unordered_set<char> terminalTypes{
    'i', 'a', 'A', 'R', ':', 'S', 's', 'I', 'O', 'o'
  };

  bool parse(const Keystroke& keystroke) override;
  void doReset() override { 
    movementParser.reset();
    basicSetMode = SetMode{}; 
    comboSetMode = CM{}; 
    countedParser.reset();
    useCombo = false;
    checkCC = false;
  }
  void run(const Movement* cmd) override;
 public: 
  // listen for CM's movement
  SetModeParser() {movementParser.attach(this);}
  const SetMode* getCommand() const noexcept override {
    return useCombo ? &comboSetMode : &basicSetMode;
  };
};

#endif

