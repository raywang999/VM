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
  } else if (keystroke.key == Key::Arrow){
    int dr=0,dc=0;
    if (keystroke.value == 'l'){--dc;}
    else if (keystroke.value == 'r'){++dc;}
    else if (keystroke.value == 'u'){++dr;}
    else {--dr;}
    cursor.translate(cursor.getRow()+dr, cursor.getCol()+dc);
  } else if (keystroke.key == Key::Backspace){
    if (cursor.getCol() > 0){
      cursor.setCol(cursor.getCol()-1);
      filebuf.erase(cursor.getRow(), cursor.getCol(), 1);
    }
  }
  activeTab.setCursor(cursor);
}

#endif
