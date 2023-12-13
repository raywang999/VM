#ifndef MATCHER_RUNNER_H
#define MATCHER_RUNNER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "include/loc.h"
#include "lib/command/runner/command_runner.h"
#include "lib/history/history_manager.h"
#include "lib/window/window.h"
#include "matcher_trie.h"

// runs % command
class MatcherRunner: public CommandRunner<Movement> {
  Window*& activeWindow;
  // optimize % to only regenerate locations after edit
  HistoryManager& historyManager; 

  // class to maintain locations and their corresponding matches
  class Matcher {
    // charbuf from which we read
    const LinedCharbuf<char>& charbuf;
    Trie trie;
    std::vector<Loc> fileLoc; // location in file
    std::vector<Loc> pairLoc; // location to pair
    // invariant: the matched location for fileLoc[i] == pairLoc[i]
    // invariant: fileLoc is sorted in ascending order
    int prevEdit; // last edit that we generated on

    // locations of previous if group in the file
    std::vector<std::vector<size_t>> prevIfBlockInds;
    // fill fileloc with locations from beg to end of line 
    // also fills prevIfBlockInds are required
    void fillLine(LinedCharbuf<char>::const_iterator& beg);
    // match the indices of the previous if block with loc 
    void fillPair(Loc loc);
   public:
    Matcher() =default;
    Matcher(const LinedCharbuf<char>& charbuf): 
      charbuf{charbuf}
    {
      // initialize using the first edit
      genLocations(0);
    }
    // generate locations of fileLoc, pairLoc from a charbuf
    void genLocations(int edit); 
    // search for loc in fileLoc and return its corresponding pairLoc
    Loc getPair(Loc loc) const;
    int getEdit() const noexcept {return prevEdit;}
  };
  using MatcherManager = std::unordered_map<std::string, Matcher>;
  MatcherManager matcherManager;

 public:
  // run %
  void run(const Movement* cmd) override; 
  MatcherRunner(
    Window*& activeWindow,
    HistoryManager& historyManager
  ): 
    activeWindow{activeWindow},
    historyManager{historyManager}
  { }
};

#endif

