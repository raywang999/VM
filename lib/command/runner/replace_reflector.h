#ifndef REPLACE_REFLECTOR_H
#define REPLACE_REFLECTOR_H

#include "lib/window/window.h"
#include "lib/keystroke/keystroke_consumer.h"
#include "lib/buffer/file_manager.h"
#include "lib/tab/tab.h"

// reflects inserts into the currently active LinedFilebuf
class ReplaceReflector: public KeystrokeConsumer{
  Window*& activeWindow;
 public: 
  ReplaceReflector(Window*& window): activeWindow{window} {}
  // if any Plain key is pressed, replcae it into the LinedFilebuf
  void consume(const Keystroke& keystroke) override;
};

inline void ReplaceReflector::consume(const Keystroke& keystroke){
  auto& activeTab = activeWindow->getTabManager().curr();
  auto& filebuf = activeTab.getFilebuf();
  auto cursor = activeTab.getCursor();
  auto curRow = cursor.getRow(), curCol = cursor.getCol();
  if (keystroke.key == Key::Plain) {
    filebuf.erase(curRow, curCol, 1);
    filebuf.insert(curRow, curCol, keystroke.value);
    cursor.setCol(cursor.getCol()+1);
    if (keystroke.value == '\n') {
      cursor.translate(curRow+1,0);
    }
  }
  activeTab.setCursor(cursor);
}

#endif
