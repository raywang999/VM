#include <stdio.h>
#include <ncurses.h>
#include <cassert>

#include "lib/keystroke/uwse_keyboard.h"

bool operator==(const Keystroke& a, const Keystroke& b){
  return a.key == b.key && a.value == b.value;
}

void test(Keystroke ks, UWSEKeyboard& keyboard){
  keyboard.getNext();
  assert(ks == keyboard.getState());
}


int main(){
  initscr();
	clear();
	noecho();
  keypad(stdscr, TRUE);
  UWSEKeyboard keyboard{};
  test(Keystroke{Key::Plain, 'a'}, keyboard);
  test(Keystroke{Key::Plain, '-'}, keyboard);
  test(Keystroke{Key::Plain, '_'}, keyboard);
  test(Keystroke{Key::Plain, '\n'}, keyboard);
  //test(Keystroke{Key::Esc}, keyboard);
  endwin();
}

