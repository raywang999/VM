#ifndef MACROS_REGISTER_H
#define MACROS_REGISTER_H

#include <unordered_map>
#include "lib/command/command.h"

// stores the sequence of commands into a Macro
using MacrosRegister = std::unordered_map<char, Sequence>;

#endif