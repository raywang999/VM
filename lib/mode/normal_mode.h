#ifndef MODE_NORMAL_H
#define MODE_NORMAL_H

#include <vector>

#include "mode.h"
#include "lib/command/parser/normal_parser.h"

// standard Insert Mode implementation 
class NormalMode: public Mode {
  NormalParser& parser;
 public: 
  NormalMode(NormalParser& parser): Mode({&parser}), parser{parser} {}
  // if `Esc` is pressed, reset all parsers
  void consume(const Keystroke& keystroke) override;
};

inline void NormalMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    parser.reset();
    setMode(ModeType::Normal);
    CommandSource::notifyAll();
  }
  Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
}

#endif
