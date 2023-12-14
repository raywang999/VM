#include <string>
#include <filesystem>

#include "ctrl_runner.h"

std::string CtrlRunner::printFilename() const{
  const auto& filename = activeWindow->getTabManager().curr().getFilebuf().getFilename();
  if (filename.empty()){ // if file doesn't have a name, use [No Name] 
    return "[No Name]";
  }
  return filename;
}
std::string CtrlRunner::printCursor() const {
  const auto& tab = activeWindow->getTabManager().curr();
  const auto& filebuf = tab.getFilebuf();
  auto cursor = tab.getCursor();
  double linecnt = static_cast<double>(filebuf.countLines());
  int position = static_cast<int>(std::round((cursor.getRow()+1)*100/linecnt));
  return "--" + std::to_string(position) + "%--";
}

std::string CtrlRunner::printFileStatus() {
  std::string status; // result
  const auto& filebuf = activeWindow->getTabManager().curr().getFilebuf();
  const auto& filename = filebuf.getFilename();
  // calculated if we modified the file
  auto savedEdit = historyManager.getSavedEdit(filename);
  auto currEdit = historyManager.getTree(filename).getCurr();
  if (savedEdit != currEdit){ 
    status = "[Modified]";
  } 
  // calculate if file is new
  if (!std::filesystem::exists(filename)){
    status += "[New]"; 
  }
  return status;
}

std::string CtrlRunner::printLineCount() const {
  const auto& filebuf = activeWindow->getTabManager().curr().getFilebuf();
  return pluralize(filebuf.countLines(), "line");
}

void CtrlRunner::run(const Ctrl* cmd){
  auto& tab = activeWindow->getTabManager().curr();
  if (cmd->type == 'b' || cmd->type == 'f'){ 
    // scroll count 'page's back/forwards
    auto count = normalizeCount(cmd->count);
    int delta = count * (activeWindow->getHeight()-2);
    if (cmd->type == 'f'){
      tab.setTopLine(tab.getTopLine()+delta);
    } else {
      tab.setTopLine(tab.getTopLine()-delta);
    }
  } else if (cmd->type == 'u' || cmd->type == 'd') { 
    // scroll window by `CtrlRunner::scroll` lines up/down
    if (cmd->count != -1) {  // set scroll to count first if it is given
      scroll = cmd->count;
    }
    int newline = static_cast<int>(tab.getTopLine());
    if (cmd->type == 'u'){
      newline = newline - scroll;
    } else {
      newline = newline + scroll;
    }
    tab.setTopLine(newline);
  } else if (cmd->type == 'g') {
    // show file-name, file-status, # of lines, then cursor position in file
    rootStatus.setMessage(
      printFilename() + " " + 
      printFileStatus() + " " + 
      printLineCount() + " " + 
      printCursor()
    );
  }
}

