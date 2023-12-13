#ifndef ROOT_STATUS_H
#define ROOT_STATUS_H

#include <string>

enum class ErrorCode {
  nothing = 0,
  noFileName = 32,
  noWriteSinceLastChange = 37, 
  cantOpenFile = 484,
  patternNotFound = 486
};

// status bar on bottom left of the screen
// stores general information like ExLine message, error-codes
class RootStatus{
  ErrorCode errorCode{ErrorCode::nothing};
  std::string exMessage; // overrides normal mode/insert mode
 public: 
  void setError(ErrorCode error) noexcept {
    errorCode = error;
  }
  // set message. resets error code if clear == true
  void setMessage(const std::string& msg, bool clear = true) noexcept {
    exMessage = msg;
    if (clear){
      errorCode = ErrorCode::nothing;
    }
  }
  void reset() noexcept {exMessage.clear(); errorCode = ErrorCode::nothing;}
  ErrorCode getError() const noexcept {return errorCode;}
  const std::string& getMessage() const noexcept {return exMessage;}
};

#endif