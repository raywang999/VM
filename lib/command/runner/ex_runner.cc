#include "ex_runner.h"
#include <sstream>

bool ExRunner::write(const std::vector<std::string>& args){
  auto* filebuf = &activeWindow->getTabManager().curr().getFilebuf();
  std::string filename;
  if (args.size() == 1){  // use filebuf's filename
    filename = filebuf->getFilename();
  } else {
    // user did supply a filename
    filename = args[1];
    filebuf = fileManager.open(args[1]).get();
    historyManager.copy(filebuf->getFilename(), filename);
  }
  if (filename.empty()){ // filename is not valid 
    rootStatus.setError(ErrorCode::noFileName);
    return false;
  }  else {
    // save file and udpate history 
    filebuf->persist();
    historyManager.setDiffCnt(filename);
  }
  return true;
}

void ExRunner::run(const Ex* insert){
  const auto&args = insert->args;
  if (args.empty()) return; // do nothing
  if (args[0] == "w"){
    write(args);
  } else if (args[0] == "q"){
    auto& filebuf = activeWindow->getTabManager().curr().getFilebuf();
    if (historyManager.getDiffCnt(filebuf.getFilename())){
      // warn unsaved changes
      rootStatus.setError(ErrorCode::noWriteSinceLastChange);
    } else {
      activeWindow->close();
    }
  } else if (args[0] == "q!"){ // close the window without saving
    activeWindow->close();
  } else if (args[0] == "wq"){
    if (write(args)) activeWindow->close();
  }
  modeManager.setMode(ModeType::Normal);
}

