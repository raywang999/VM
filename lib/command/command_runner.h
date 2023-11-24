#ifndef COMMAND_SOURCE_H
#define COMMAND_SOURCE_H

#include "include/observer.h"
#include "command.h"

class CommandRunner: public Observer<Command*> {};

#endif
