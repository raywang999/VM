#ifndef MODE_NORMAL_H
#define MODE_NORMAL_H

#include <vector>

#include "mode.h"
#include "lib/command/parser/normal_parser.h"
#include "lib/command/parser/movement_parser.h"

// standard Normal Mode implementation 
class NormalMode: public Mode {
  NormalParser& normalParser;
  MovementParser& movementParser;
 public: 
  NormalMode(NormalParser& normalParser, MovementParser& movementParser): 
    Mode({&normalParser, &movementParser}), normalParser{normalParser}, movementParser{movementParser} {}
  // if `Esc` is pressed, reset all normalParsers
  void consume(const Keystroke& keystroke) override;
  void reset() { normalParser.reset(); movementParser.reset(); }
};

inline void NormalMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    reset(); // reset all parsers
  } else {
    Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
  }
}

#endif
