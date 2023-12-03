#ifndef MACROS_REGISTER_H
#define MACROS_REGISTER_H

#include <unordered_map>
#include <vector>

#include "lib/command/command.h"
#include "lib/keystroke/keystroke.h"

// stores the sequence of commands into a Macro
using MacrosRegister = std::unordered_map<char, std::vector<Keystroke>>;

#endif