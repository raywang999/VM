#ifndef COMMAND_STRUCT_H
#define COMMAND_STRUCT_H

// command heirarchy for vim (Ex, Normal, Replace, Insert)
// - can be extended for other uses, like extended normal commands

#include <string>

#include "lib/mode/mode.h"

// empty class to denote top of Command heirarchy 
struct Command { 
  virtual ~Command(){}
};

// command to represent optional multipliers 
struct Counted: public Command {
  int count;
};

// basic normal mode command 
// - e.g. 5x, rx, s, i, 3u, 5a, 2p, 2yy, 3dd
struct Normal: public Counted{
  char type;
  char data; // optional e.g. 5rx
};

// normal mode movement 
// - arrow keys will get translated to corresponding hjkl
// - e.g. 5l, 3fa, 2b, w
struct Movement: public Counted{
  char type;
  // optional e.g. 'a' if the command is fa
  char seek; 
};

// ctrl commands. E.g. Ctrl+f 
struct Ctrl: public Counted {
  char type; 
};

// combination of a normal and movement 
// E.g. d3w, 2y3l
struct ComboNM{
  Normal normal;
  Movement movement;
};

// Ex mode commands. I.e. :w, :wq
struct Ex{
  std::string sentence;
};

// Insert mode command. I.e. a chain of partial inserts
struct Insert: public Counted{
  std::string sentence;
};

// a single modification during insert mode
struct PartialInsert: public Counted{
  char data;
};

// Replace mode command. I.e. a chain of partial replaces
struct Replace: public Counted{
  std::string sentence;
};

// a single replace
struct PartialReplace: public Command{
  char data;
};

// tells ModeManager to switch to a mode
struct SetMode: public Command{
  Mode mode;
};

// Command to write/play macro at a register
struct WriteMacro: public Counted {
  // macro register (between 0-9a-zA-Z) to write
  char reg;  
};
struct ReadMacro: public Counted {
  char reg;  
};


#endif
