#ifndef INSERT_REFLECTOR_H
#define INSERT_REFLECTOR_H

#include <vector>

#include "lib/window/window.h"
#include "lib/keystroke/keystroke_consumer.h"
#include "lib/buffer/file_manager.h"
#include "lib/tab/tab.h"

// reflects inserts into the currently active LinedFilebuf
class InsertReflector: public KeystrokeConsumer{
  Window*& activeWindow;
 public: 
  InsertReflector(Window*& window): activeWindow{window} {}
  // if any Plain key is pressed, insert it into the LinedFilebuf
  void consume(const Keystroke& keystroke) override;
};

inline void InsertReflector::consume(const Keystroke& keystroke){
  if (keystroke.key == Key::Plain) {
    auto& activeTab = activeWindow->getTabManager().curr();
    auto& filebuf = activeTab.getFilebuf();
    auto cursor = activeTab.getCursor();
    filebuf.insert(cursor.getRow(), cursor.getCol(), std::string(1,keystroke.value));
    cursor.setCol(cursor.getCol()+1);
    activeTab.setCursor(cursor);
    activeWindow->render();
  }
}

#endif
