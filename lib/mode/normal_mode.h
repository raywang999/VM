#ifndef MODE_NORMAL_H
#define MODE_NORMAL_H

#include <vector>

#include "mode.h"
#include "lib/command/runner/parser_group.h"

// standard Normal Mode implementation 
class NormalMode: public Mode {
  ParserGroup& parserGroup;
 public: 
  NormalMode(ParserGroup& parserGroup): parserGroup{parserGroup} {}
  // if `Esc` is pressed, reset all normalParsers
  void consume(const Keystroke& keystroke) override;
};

inline void NormalMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    parserGroup.reset(); // reset all parsers
  } else {
    Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
  }
}

#endif
