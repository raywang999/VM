#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "keystroke_consumer.h"
#include "command_source.h"


class Command {

};

class InvertibleCommand: public Command{
 public: 
  virtual UndoableCommand()
};
class CommandSource: public Subject<Command> {};

class CommandParser: public KeystrokeConsumer, public CommandSource {
  // Subclasses should override this method on valid input keystrokes 
  // - if keystroke is parseable, parse it and return true;
  // - otherwise, subclass should do nothing and return false 
  // this class will mark itself invalid
  virtual bool parseKeystroke(Keystroke& keystroke) =0;
  bool valid = true;
 public: 
  bool isValid() const {return isValid; }
  void reset() {valid = false;}

  // calls subclass's parseKeystroke() and marks this->valid accordingly
  void notify(KeystrokeSource& source) override;
};

inline void CommandParser::notify(KeystrokeSource& source){
  // if not valid, don't do anything
  // otherwise, check if subclass can parse the keystroke
  if (valid && !parseKeystroke(source.getState())){
    // input keystroke is not parseable, set state to invalid
    valid = false;
  }
}

#endif


