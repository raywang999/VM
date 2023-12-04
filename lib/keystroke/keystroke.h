#ifndef KEYSTROKE_H
#define KEYSTROKE_H

/*
 *
 * Plain        Any alphanumeric, punctuation, space character. I.e. normal char
 * Ctrl         Ctrl character. value should be set to the (lowercase) ? in ctrl+?
 *              where ctrl+? is the corresponding ctrl sequence
 * Arrow        Any arrow key. Value will be the direction (udlr) for up, down, left, right
 * Esc          Escape key
 * Backspace    Backspace key
 * Del          Del key
 * Other        Anything not in the above. Value will be set to the given input
 */

enum class Key: char{
  Plain, Ctrl, Arrow, Esc, Backspace, Del, Other
};

struct Keystroke {
  Key key;
  int value;                 // value if relevant 
};

#endif

