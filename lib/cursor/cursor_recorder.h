#ifndef CURSOR_RECORDER_H
#define CURSOR_RECORDER_H

#include "lib/window/window.h"
#include "lib/command/runner/command_runner.h"
#include "lib/command/runner/normal_runner.h"

class CursorRecorder: 
  public CommandRunner<Insert>,
  public CommandRunner<Replace>,
  public CommandRunner<Command>
{
  Window*& activeWindow;
  Cursor cursor;
  void update() { cursor = activeWindow->getTabManager().curr().getCursor(); }
 public:
  CursorRecorder(Window*& activeWindow): activeWindow{activeWindow} {}

  // if Insert, the cursor should return to how it was before the insert
  void run(const Insert* cmd) override { }
  // if Replace, the cursor should return to how it was before the replace
  void run(const Replace* cmd) override { }
  // otherwise, save cursor
  void run(const Command* cmd) override { update(); }
  const Cursor& getCursor() const noexcept {return cursor; }
};

#endif