#ifndef ROOT_STATUS_BAR_H
#define ROOT_STATUS_BAR_H

#include <string>

enum class ErrorCode {
  nothing = 0,
  noWriteSinceLastChange = 37
};

// status bar on bottom left of the screen
// stores general information like ExLine message, error-codes
struct RootStatusBar{
  ErrorCode errorCode{ErrorCode::nothing};
  std::string message;
  bool recordingMacro = false;
};

#endif