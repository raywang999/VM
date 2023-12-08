#ifndef UNDO_RUNNER_H
#define UNDO_RUNNER_H

#include <chrono> 
#include <sstream>
#include <iomanip>

#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/mode/mode_manager.h"
#include "lib/history/history_manager.h"
#include "lib/statusbar/root_status.h"

// only runs u and Ctrl-R commands
class UndoRunner: 
  public CommandRunner<Normal>,
  public CommandRunner<Ctrl>
{
  Window*& activeWindow;
  ModeManager& modeManager;
  HistoryManager& historyManager;
  RootStatus& rootStatus;
  // returns string form to represent number of lines more/less
  static std::string printLineChange(int changes) {
    std::string res = std::to_string(changes);
    res += (changes > 0 ? " more " : " less "); 
    res += "line";
    if (changes>1 || changes < -1) {res.push_back('s');}
    return res;
  }
  // returns string form to represent number of changes
  static std::string printChanges(int changes) {
    if (changes == 1){return "1 change";}
    return std::to_string(changes) + " changes";
  }

  // returns x seconds ago, or timestamp, as relevant
  static std::string printTime(HistoryTree::Node::timestamp_t time) {
    using namespace std::chrono;
    auto elapsedSeconds = duration_cast<seconds>(system_clock::now() - time);
    auto secondsInt = elapsedSeconds.count() * seconds::period::num / seconds::period::den;
    if (secondsInt > 99){ // use the timestamp
      std::time_t t = system_clock::to_time_t(time);
      auto tm = *std::localtime(&t);  
      std::ostringstream oss;
      oss << std::put_time(&tm, "%H-%M-%S");
      return oss.str();
    } else { // use seconds ago
      return 
        std::to_string(secondsInt)
        + (secondsInt > 1 ? " second" : " seconds")
        + " ago";
    }
  }

  // formats the change message, using "before" or "after"
  void setChangeMessage(int cntChanges, int startLineCnt, const HistoryTree::Node* node, bool before) {
    const auto& filebuf = activeWindow->getTabManager().curr().getFilebuf();
    int lineDiff = static_cast<int>(filebuf.countLines()) - startLineCnt;
    auto message = ((lineDiff != 0) ? printLineChange(lineDiff) : printChanges(cntChanges));
    message += (before ? "; before" : "; after"); 
    message += " #" + std::to_string(node->edit) + "  " + printTime(node->timestamp);
    rootStatus.setMessage(message);
  }

  void persistChange(){
    auto& tab = activeWindow->getTabManager().curr();
    auto& filebuf = tab.getFilebuf();
    const auto& node = historyManager.getTree(filebuf.getFilename()).getCurrNode();

    // update filebuf's contents with current node's filecontents
    filebuf.eraseLines(0,-1);
    filebuf.insertLines(0,1);
    filebuf.insert(0,0,node.contents);
    filebuf.eraseLines(filebuf.countLines()-1,1); // erase trailing newline
  }

 public:
  void run(const Normal* normal) override; 
  void run(const Ctrl* ctrl) override;
  UndoRunner(
    Window*& activeWindow, 
    ModeManager& modeManager, 
    HistoryManager& historyManager,
    RootStatus& rootStatus
  ): 
    activeWindow{activeWindow}, 
    modeManager{modeManager}, 
    historyManager{historyManager},
    rootStatus{rootStatus}
  {}
};

#endif

