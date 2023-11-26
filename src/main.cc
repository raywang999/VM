#include "parse_args.h"

#include "include/ncursespp.h"
#include "include/ncolors.h"
#include "lib/buffer/fstream_lfb.h"
#include "lib/keystroke/uwse_keyboard.h"
#include "lib/window/ncwindow.h"
#include "lib/tab/tabmanager.h"
#include "lib/tab/tab.h"

int main(int argc, const char* argv[]){
  Main mainData{};
  // parse terminal args
  for (int i=1; i < argc; ++i){
    mainData.args.push_back(argv[i]);
  }
  mainData.parseArgs();

  // initialize ncurses
  initscr();
  cbreak();
  keypad(stdscr, true);
  int screenHeight, screenWidth;
  ncurses::getwindowhw(screenHeight, screenWidth);

  // show colors
  if (mainData.hasOption(Main::ShowColor{})){
    start_color();
  }
  // use a colorset
  if (mainData.hasOption(Main::SetColorset{})){
    auto it = mainData.find(Main::SetColorset{});
    auto colorset = std::get<Main::SetColorset>(*(it));
    ncurses::colorset::colorsetmaps[colorset.colorset]();
  }

  // get files we edit from command line arguments
  std::string filename = "tmp.txt"; 
  if (mainData.files.size()){
    filename = mainData.files[0];
  }
  FstreamLFB<char> rootLinedFilebuf(filename);

  TabManager rootTabManager;
  rootTabManager.emplace_back(rootLinedFilebuf);
  StyleManager rootStyleManager;

  // create a ncurses window
  NCWindow rootWindow{rootTabManager, rootStyleManager};

  rootWindow.resize(screenHeight, screenWidth);
  rootWindow.translate(0,0);
  rootWindow.render();
  refresh();
  getch();

  endwin();
}
