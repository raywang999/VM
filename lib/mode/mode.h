#ifndef MODE_MODESTRUCT_H
#define MODE_MODESTRUCT_H

#include <vector>

#include "lib/keystroke/keystroke_consumer.h"

// Groups together the keystroke consumers, CommandParsers, and CommandRunners for a Mode
// - forwards keystrokes from the attached source to the keystroke consumers
class Mode: public KeystrokeConsumer {
  std::vector<KeystrokeConsumer*> consumers;
 protected: 
 public: 
  Mode() =default;
  // construct a Mode with a collection of KeystrokeConsumers
  Mode(const std::initializer_list<KeystrokeConsumer*>& consumers); 

  // add a KeystrokeConsumer to the ones we own 
  // once attached, any incoming keystrokes will be forwarded to them
  void attach_consumer(KeystrokeConsumer* consumer){consumers.push_back(consumer);}
  
  // forwards keystroke to consumers
  void consume(const Keystroke& keystroke); 
};

inline Mode::Mode(const std::initializer_list<KeystrokeConsumer*>& consumers): 
  consumers{consumers.begin(), consumers.end()} {}

inline void Mode::consume(const Keystroke& keystroke){
  for (auto consumer: consumers){
    consumer->consume(keystroke);
  }
  if (keystroke.key == Key::Esc){

  }
}

#endif
