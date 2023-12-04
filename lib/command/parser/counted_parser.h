#ifndef COUNTED_PARSER_H
#define COUNTED_PARSER_H

#include <cctype>

#include "lib/command/parser/command_parser.h"
#include "lib/command/command.h"
#include "lib/keystroke/keystroke_consumer.h"

// helper class to parse optional multipliers
class CountedParser {
  // holds the currently parsed count 
  // defaults to -1 if no numeric keystrokes are passed 
  int theCount = -1;

  // whether the parser will accept numbers 
  // i.e. we haven't parsed any non-numbers yet
  bool valid = true;
  // whether we are parsing our first input 
  bool first = true;

 public: 
  void reset() { theCount = -1; valid = first = true; }
  int getCount() { return theCount; }
  // parses optional count. 
  // if keystroke is not a number, 
  // - If `first`, then set count to 1
  // - Set valid to false 
  // otherwise, keystroke is a number, so parse if valid 
  // returns true iff parse was successful
  bool parse(const Keystroke& keystroke);
};

#endif

