#include <include/ncursespp.h> 
#include <cctype>
#include <unordered_map>

#include "lib/keystroke/uwse_keyboard.h"
#include "lib/keystroke/keystroke.h"

// map of CSSE's ncurses keyboard input `int`s to corresponding `Keystroke`s
// - excluding Plain characters (i.e. isgraph chars)
static std::unordered_map<int, Keystroke> toKS{
  {KEY_DOWN, Keystroke{Key::Arrow, 'd'}},
  {KEY_UP, Keystroke{Key::Arrow, 'u'}},
  {KEY_LEFT, Keystroke{Key::Arrow,'l'}},
  {KEY_RIGHT, Keystroke{Key::Arrow,'r'}},
  {KEY_BACKSPACE, Keystroke{Key::Backspace}},
  // not sure what ncurses maps these to 
  // so just used integers given in student environment 
  {330, Keystroke{Key::Del}},
  {27, Keystroke{Key::Esc}},
  {2, Keystroke{Key::Ctrl, 'b'}},
  {4, Keystroke{Key::Ctrl, 'd'}},
  {6, Keystroke{Key::Ctrl, 'f'}},
  {7, Keystroke{Key::Ctrl, 'g'}},
  {21, Keystroke{Key::Ctrl, 'u'}},
  {23, Keystroke{Key::Ctrl, 'w'}},
  {18, Keystroke{Key::Ctrl, 'r'}}
};

Keystroke UWSEKeyboard::getKeystroke() const {
  // lookup the type in toKS
  if (toKS.count(currInput)){
    return toKS[currInput];
  }
  if (isgraph(currInput) || isspace(currInput)){
    return Keystroke{Key::Plain, currInput};
  }
  // lookup not found, so return it as an Other type
  return Keystroke{Key::Other, currInput};
}

void UWSEKeyboard::getNext() {
  currInput = getch();
}

