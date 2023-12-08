#include "main.h"

int Main::main(){
  // loop while we haven't exited from rootWindow
  while (windowsClosure.rootWindow.getType() != WindowType::Closed){
    windowsClosure.activeWindow->render();
    statusBarClosure.renderStatusBar();
    cursorClosure.renderCursor();
    refresh();
    // read char and re-render
    keyboard.getNext();
    keyboard.notifyAll();
  }
  return 0;
}

int main(int argc, const char* argv[]){
    // Main mainData(argc,argv);
    // return mainData.main();
  try {
    Main mainData(argc,argv);
    return mainData.main();
  } catch(...){
    return 1;
  }
}
