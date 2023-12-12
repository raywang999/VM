#include <cctype>

#include "ex_runner.h"

bool ExRunner::write(const std::vector<std::string>& args){
  auto* filebuf = &activeWindow->getTabManager().curr().getFilebuf();
  std::string filename;
  bool isNewFile = false;
  if (args.size() == 1){  // use filebuf's filename
    filename = filebuf->getFilename();
  } else {
    // user did supply a filename
    filename = args[1];
    isNewFile = !fileManager.isOpen(args[1]);
    filebuf = fileManager.open(args[1]).get();
    historyManager.copy(filebuf->getFilename(), filename);
  }
  if (filename.empty()){ // filename is not valid 
    rootStatus.setError(ErrorCode::noFileName);
    return false;
  }  else {
    // save file and udpate history 
    filebuf->persist();
    historyManager.persist(filename);
  }
  rootStatus.setMessage(
    "\"" + filename + "\" " + 
    (isNewFile ? " [New]" : "") + 
    std::to_string(filebuf->countLines()) + "L, " + 
    std::to_string(filebuf->countBytes()) + "B " + 
    "written"
  );
  return true;
}

void ExRunner::run(const Ex* cmd){
  const auto&args = cmd->args;
  if (args.empty()) return; // do nothing
  if (args[0] == "w"){
    write(args);
  } else if (args[0] == "q"){
    auto& filebuf = activeWindow->getTabManager().curr().getFilebuf();
    const auto& filename = filebuf.getFilename();
    auto savedEdit = historyManager.getSavedEdit(filename);
    auto currEdit = historyManager.getTree(filename).getCurr();
    if (savedEdit != currEdit){
      // warn unsaved changes
      rootStatus.setError(ErrorCode::noWriteSinceLastChange);
    } else {
      activeWindow->close();
    }
  } else if (args[0] == "q!"){ // close the window without saving
    activeWindow->close();
  } else if (args[0] == "wq"){
    if (write(args)) activeWindow->close();
  } else if (args[0] == "$"){ // go to last line
    auto& tab = activeWindow->getTabManager().curr();
    tab.setCursor(Cursor{tab.getFilebuf().countLines()-1,0}, true);
  } else if (is_natural(args[0])) { // go to line #x
    int x = std::stoi(args[0]);
    auto& tab = activeWindow->getTabManager().curr();
    // fit 1 <= x <= # of lines in file
    x = fit(1,tab.getFilebuf().countLines(),x);
    tab.setCursor({x-1,0}, true);
  }
  modeManager.setMode(ModeType::Normal);
}

