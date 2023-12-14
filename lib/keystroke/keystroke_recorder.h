#ifndef COMMAND_RECORDER_H
#define COMMAND_RECORDER_H

#include <vector>
#include "include/resetable.h"
#include "keystroke_source.h"
#include "keystroke_consumer.h"

// records the commands run so that they are accurrately played through Macros and Undo/Redo
// note: since the input commands expire, we need to copy them all
class KeystrokeRecorder: 
  public KeystrokeConsumer, 
  public Resetable
{
  std::vector<Keystroke> keystrokes;
  bool active = false; // whether we listen for keystrokes 
  void doReset() override {active = false; keystrokes.clear(); }
 public:
  void consume(const Keystroke& key) override {
    if (active){ 
      keystrokes.push_back(key); 
    }
  }
  void setActive(bool type) noexcept {active = type;}
  bool isActive() const noexcept {return active;}
  
  const std::vector<Keystroke>& getKeystrokes() const {return keystrokes;}
};

#endif

