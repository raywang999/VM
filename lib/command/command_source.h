#ifndef COMMAND_SOURCE_H
#define COMMAND_SOURCE_H

#include "include/subject.h"
#include "command.h"

class CommandSource: public Subject<Command*> {};

#endif