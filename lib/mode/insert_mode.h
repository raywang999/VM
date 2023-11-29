#ifndef MODE_INSERT_H
#define MODE_INSERT_H

#include <vector>

#include "mode.h"
#include "lib/command/parser/insert_parser.h"

// standard Insert Mode implementation 
class InsertMode: public Mode {
  InsertParser& parser;
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

inline void InsertMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    parser.notifyAll();
    setMode(ModeType::Normal);
    CommandSource::notifyAll();
  }
  Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
}

#endif
