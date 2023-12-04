#ifndef ROOT_STATUS_BAR_H
#define ROOT_STATUS_BAR_H

#include <string>

enum class ErrorCode {
  nothing = 0,
  noFileName = 32,
  noWriteSinceLastChange = 37
};

// status bar on bottom left of the screen
// stores general information like ExLine message, error-codes
class RootStatus{
  ErrorCode errorCode{ErrorCode::nothing};
  std::string message;
  bool recordingMacro = false;
 public: 
  void setError(ErrorCode error) noexcept {
    errorCode = error;
    message.clear();
  }
  void setMessage(const std::string& msg) noexcept {
    message = msg;
    errorCode = ErrorCode::nothing;
  }
  void setRecording(bool rec) noexcept {recordingMacro = rec;}
  ErrorCode getError() const noexcept {return errorCode;}
  const std::string& getMessage() const noexcept {return message;}
  bool getRecording() const noexcept {return recordingMacro;}
};

#endif