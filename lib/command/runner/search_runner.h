#ifndef SEARCH_RUNNER_H
#define SEARCH_RUNNER_H

#include <string>
#include <vector>

#include "include/resetable.h"
#include "lib/command/runner/movement_runner.h"
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"
#include "lib/statusbar/root_status.h"
#include "lib/mode/mode_manager.h"

// runs searching command 
// e.g. n, N, ?, /
class SearchRunner: 
  public CommandRunner<Movement>, // listen for n,N
  public CommandRunner<Search>  // listen for parsed ?, /
{
  Window*& activeWindow;
  RootStatus& rootStatus;
  ModeManager& rootModeManager;

  bool reverse = false; // whether to search in reverse

  // class to match needle to include::findNth
  class Matcher: public Resetable {
    std::string needle;
    std::vector<int> lps;
    size_t curri=0; // current index in lps
    void doReset() override {curri = 0;};
   public:
    // note: give placeholder needle to prevent searching for empty string
    Matcher(const std::string& needle = "a");
    bool operator==(char ch);
    const std::string& getNeedle() const noexcept {return needle;}
  };

  Matcher matcher;
  Matcher rmatcher; // reverse matcher

 public:
  // set the needle as required, and direction of search
  void run(const Search* cmd) override; 
  // run n, N
  void run(const Movement* cmd) override; 
  SearchRunner(
    Window*& activeWindow, 
    RootStatus& rootStatus, 
    ModeManager& rootModeManager
  ): 
    activeWindow{activeWindow}, 
    rootStatus{rootStatus},
    rootModeManager{rootModeManager}
  { }
};

#endif

