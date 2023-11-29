#ifndef COMMAND_STRUCT_H
#define COMMAND_STRUCT_H

// Command Hierarchy

#include <variant> 
#include <string>
#include <vector>

#include "lib/mode/modetype.h"

struct Command{
  virtual ~Command()=0;
};
inline Command::~Command(){}

// basic normal mode command 
// - e.g. 5x, rx, s, i, 3u, 5a, 2p, 2yy, 3dd
struct Normal: public Command {
  int count;
  char type; // one of a,c,d,o,p,r,s,u,x,y,A,I,J,O,P,R,S,X,.
  char data; // optional e.g. the 'x' in rx
  Normal(int count=0, char type=0, char data=0): 
    count{count}, type{type}, data{data} {}
};

// normal mode movement 
// - arrow keys will get translated to corresponding hjkl
// - e.g. 5l, 3fa, 2b, w
struct Movement: public Command {
  int count;
  char type;
  // optional e.g. 'a' if the command is fa
  char seek; 
  Movement(int count=0, char type=0, char seek=0): 
    count{count}, type{type}, seek{seek} {}
};

// ctrl commands. E.g. Ctrl+f 
struct Ctrl: public Command {
  int count;
  char type; 
  Ctrl(int count=0, char type=0): 
    count{count}, type{type}{}
};

// combination of a normal and movement 
// E.g. d3w, 2y3l
struct ComboNM: public Command {
  Normal normal;
  Movement movement;
};

// Ex mode commands. I.e. :w, :wq
struct Ex: public Command {
  std::string sentence;
};

// Insert mode command. I.e. a chain of partial inserts
struct Insert: public Command {
  int count;
  std::string sentence;
  Insert(int count = 0, const std::string& sentence = ""): 
    count{count}, sentence{sentence} {}
};

// Replace mode command. I.e. a chain of partial replaces
struct Replace: public Command {
  int count;
  std::string sentence;
};

// tells ModeManager to switch to a mode
struct SetMode: public Command {
  ModeType mode;
  SetMode(ModeType mode = ModeType::Normal): mode{mode} {}
};

// Command to write/play macro at a register
struct Macro: public Command {
  int count;
  // macro register (between 0-9a-zA-Z) to write
  char reg;  
  // q for write, @ for read
  // note: multiplier in front of a write does nothing
  char type; 
  Macro(int count = 0, char reg =0, char type=0): 
    count{count}, reg{reg}, type{type} {}
};

// a sequence of commands
struct Sequence: public Command {
  // the sequence of commands in chronological order
  std::vector<Command*> theSequence;
};

#endif

