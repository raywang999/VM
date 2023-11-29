#ifndef MODE_MODESTRUCT_H
#define MODE_MODESTRUCT_H

#include <vector>

#include "modetype.h"
#include "include/subject.h"
#include "include/observer.h"
#include "lib/command/command_source.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/parser/command_parser.h"

// Groups together the keystroke consumers, CommandParsers, and CommandRunners for a Mode
// - forwards keystrokes from the attached source to the keystroke consumers
class Mode: 
  virtual public KeystrokeConsumer,
  virtual public CommandSource<SetMode>
{
  // a changeMode command for our parent ModeManager to run
  SetMode theMode;
  std::vector<KeystrokeConsumer*> consumers;
 protected: 
 public: 
  Mode() =default;
  // construct a Mode with a collection of KeystrokeConsumers
  Mode(const std::initializer_list<KeystrokeConsumer*>& consumers); 

  // add a KeystrokeConsumer to the ones we own 
  // once attached, any incoming keystrokes will be forwarded to them
  void attach_consumer(KeystrokeConsumer* consumer){consumers.push_back(consumer);}
  
  // add a CommandRunner to listen to our emmitted setMode events
  void attach_runner(CommandRunner<SetMode>* runner) {CommandSource::attach(runner);};

  void consume(const Keystroke& keystroke); 

  const SetMode* getCommand() const override {return &theMode; }

  // forward a SetMode command to the parent ModeManager
  void setMode(ModeType mode) noexcept {theMode.mode = mode;}
};

inline Mode::Mode(const std::initializer_list<KeystrokeConsumer*>& consumers): 
  consumers{consumers.begin(), consumers.end()} {}

inline void Mode::consume(const Keystroke& keystroke){
  for (auto consumer: consumers){
    consumer->consume(keystroke);
  }
}

#endif
