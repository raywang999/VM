#include <iostream>

#include "main.h"

void printHelp(std::ostream& ostream){
  ostream << "usage: ./vm [options] files\n\n";
  ostream << "--- options ---\n";
  ostream << "--show-color\n";
  ostream << "shows colors. Note: doesn't work unless a color-set is specified\n\n";
  ostream << "--color-set \"colorset\" \n";
  ostream << "Specify a colorset. Options include:\n";
  ostream << "standard\n";
  ostream << '\n';
}

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
  bool showHelp = false;
  try {
    Main mainData(argc,argv);
    if (mainData.terminalArgs.hasOption(TerminalArgs::ShowHelp{})){
      showHelp = true;
    } else {
      return mainData.main();
    }
  } catch(...){
    return 1;
  }
  if (showHelp){
    printHelp(std::cout);
  }
  return 0;
}
