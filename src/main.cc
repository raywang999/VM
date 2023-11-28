#include "main.h"

int Main::main(){
  auto& rootWindow = windowsClosure.rootWindow;
  rootWindow.render();
  // loop while we haven't exited from rootWindow
  while (!modesClosure.exitedFromRoot){
    // read char and re-render
    keyboard.getNext();
    keyboard.notifyAll();
    refresh();
  }
  return 0;
}

int main(int argc, const char* argv[]){
  try {
    Main mainData(argc,argv);
    return mainData.main();
  } catch(...){
    return 1;
  }
}
