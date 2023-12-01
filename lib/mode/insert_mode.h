#ifndef MODE_INSERT_H
#define MODE_INSERT_H

#include <vector>

#include "mode.h"
#include "lib/command/parser/insert_parser.h"

// standard Insert Mode implementation 
class InsertMode: public Mode {
  InsertParser& parser;
  ModeManager& modeManager;
 public: 
  // create an InsertMode with an InsertParser that we use
  InsertMode(InsertParser& parser, ModeManager& manager): 
    Mode({&parser}), parser{parser}, modeManager{manager} {}
  // if `Esc` is pressed, emit 
  // - the child InsertParser's `Insert` command
  // - reset the parser
  void consume(const Keystroke& keystroke) override;
};

inline void InsertMode::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Esc) {
    parser.notifyAll();
    parser.reset();
    modeManager.setMode(ModeType::Normal);
  } else {
    Mode::consume(keystroke); // forward the keystroke to the parsers and consumers
  }
}

#endif
