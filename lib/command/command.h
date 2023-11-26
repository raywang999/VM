#ifndef COMMAND_STRUCT_H
#define COMMAND_STRUCT_H

// variant used for all commands (Ex, Normal, Replace, Insert)
// - can be extended for other uses, like extended normal commands

#include <variant> 
#include <string>

#include "lib/mode/modetype.h"

// basic normal mode command 
// - e.g. 5x, rx, s, i, 3u, 5a, 2p, 2yy, 3dd
struct Normal {
  int count;
  char type;
  char data; // optional e.g. 5rx
};

// normal mode movement 
// - arrow keys will get translated to corresponding hjkl
// - e.g. 5l, 3fa, 2b, w
struct Movement {
  int count;
  char type;
  // optional e.g. 'a' if the command is fa
  char seek; 
};

// ctrl commands. E.g. Ctrl+f 
struct Ctrl{
  int count;
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
struct Insert{
  int count;
  std::string sentence;
};

// a single modification during insert mode
struct PartialInsert{
  char data;
};

// Replace mode command. I.e. a chain of partial replaces
struct Replace{
  int count;
  std::string sentence;
};

// a single replace
struct PartialReplace{
  char data;
};

// tells ModeManager to switch to a mode
struct SetMode{
  ModeType mode;
};

// Command to write/play macro at a register
struct Macro{
  int count;
  // macro register (between 0-9a-zA-Z) to write
  char reg;  
  char type; // q for write, @ for read
};


using Command = std::variant<
  Normal, 
  Movement, 
  Ctrl, 
  ComboNM, 
  Ex, 
  Insert, 
  PartialInsert, 
  Replace, 
  PartialReplace, 
  SetMode, 
  Macro
>;
#endif

