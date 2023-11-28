#ifndef MODE_NORMAL_H
#define MODE_NORMAL_H

#include <vector>

#include "mode.h"
#include "lib/command/parser/normal_parser.h"
#include "lib/command/runner/normal_runner.h"

// standard Insert Mode implementation 
class NormalMode: public Mode {
  NormalParser& parser;
 public: 
  // create an InsertMode with an InsertParser that we use
  InsertMode(InsertParser& parser): Mode({&parser}), parser{parser} {}
  // create an InsertMode with an InsertParser that we use
  InsertMode(InsertParser& parser, const std::initializer_list<KeystrokeConsumer*>& consumers): 
    Mode(consumers), parser{parser}
  {
    Mode::attach_consumer(&parser);
  }
  // if `Esc` is pressed, emit 
  // - the child InsertParser's `Insert` command
  // - a `SetMode` command to set to Normal 
  void consume(const Keystroke& keystroke) override;
};

inline void NormalMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    parser.notifyAll();
    parser.reset();
    setMode(ModeType::Normal);
    CommandSource::notifyAll();
  }
  Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
}

#endif
