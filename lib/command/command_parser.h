#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "lib/keystroke/keystroke_consumer.h"
#include "lib/keystroke/keystroke.h"
#include "command_source.h"

class CommandParser: virtual public KeystrokeConsumer, virtual public CommandSource {
  // subclasses should override this to control how it parses inputs
  // - returns true if and only if the keystroke was valid 
  virtual bool parse(const Keystroke& ks) =0;
  // give subclass a way to reset its internal state, if necessary
  virtual void doReset(){};
  // parser is in a valid state. I.e. can parse more keystrokes
  bool valid = true;
 public: 
  // reset parser to starting state 
  void reset() {valid = true; doReset();}
  // consume a keystroke if parser is valid 
  // - if not, do nothing 
  // - if fail to parse, set state to invalid 
  void consume(const Keystroke& ks) override;
  bool isValid() const {return valid; }
  using CommandSource::attach;
};

inline void CommandParser::consume(const Keystroke& ks){
  if (valid){
    valid = parse(ks);
  }
}

#endif
