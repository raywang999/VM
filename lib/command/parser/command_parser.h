#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "include/resetable.h"
#include "lib/keystroke/keystroke_consumer.h"
#include "lib/keystroke/keystroke.h"
#include "lib/command/command_source.h"

class CommandParserBase:
  virtual public KeystrokeConsumer, 
  virtual public Resetable {
  // subclasses should override this to control how it parses inputs
  // - returns true if and only if the keystroke was valid 
  virtual bool parse(const Keystroke& ks) =0;
 public: 
  // consume a keystroke if parser is valid 
  // - if not, do nothing 
  // - if fail to parse, set state to invalid 
  void consume(const Keystroke& ks) final override;
};
template<typename CommandType>
  requires std::derived_from<CommandType, Command>
class CommandParser: 
  virtual public CommandParserBase,
  virtual public CommandSource<CommandType>
{ };

inline void CommandParserBase::consume(const Keystroke& ks){
  if (isValid()){
    set(parse(ks));
  }
}

#endif
