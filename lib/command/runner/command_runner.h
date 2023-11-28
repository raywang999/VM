#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include "include/observer.h"
#include "lib/command/command.h"

using CommandRunner = Observer<Command*>;

#endif
