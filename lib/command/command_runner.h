#ifndef COMMAND_RUNNER_H
#define COMMAND_RUNNER_H

#include "include/observer.h"
#include "command.h"

class CommandRunner: public Observer<Command> { };

#endif
