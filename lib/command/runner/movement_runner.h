#ifndef MOVEMENT_RUNNER_H
#define MOVEMENT_RUNNER_H

#include <cctype>
#include "lib/command/runner/command_runner.h"
#include "lib/window/window.h"

// takes a basic Movement mode Command and runs it
class MovementRunner: public CommandRunner<Movement>{
  Window*& activeWindow;
  // the previous position of the cursor's column 
  // used when jumping lines with different column sizes
  // only changed when a non-Ctrl command, and non j,k command is run 
  int prevCursorCol=0;
  bool usePrev = true;

  // const forward iterator
  using CI = LinedCharbuf<char>::const_iterator; 
  // const reverse iterator
  using CRI = LinedCharbuf<char>::const_reverse_iterator;

  // helper functions 


  //  set cursor to pos, going to the end of the charbuf if pos == end()
  void setCursor(CI pos, CI end){
    auto& tab = activeWindow->getTabManager().curr();
    const auto& filebuf = tab.getFilebuf();
    auto cursor = tab.getCursor();
    if (pos != end){ // Nth word was found
      cursor.translate(pos.getLine(), pos.getCol());
    } else { // go to the end of the file
      auto linecnt = filebuf.countLines();
      auto linesize = filebuf.getLine(linecnt-1).size();
      cursor.translate(linecnt-1,linesize <= 1 ? 0 : linesize-2);
    }
    tab.setCursor(cursor); 
  }
  //  set cursor to pos, going to the end of the charbuf if pos == end()
  void setCursor(CRI pos, CRI end){
    auto& tab = activeWindow->getTabManager().curr();
    auto cursor = tab.getCursor();
    if (pos != end){ // Nth word was found. 
      --pos; // we seeked one past the end for reverse functions
      cursor.translate(pos.getLine(), pos.getCol());
    } else { // go to the start of the file
      cursor.translate(0,0);
    }
    tab.setCursor(cursor); 
  }

 public:
  // tell next movement not to use the previous cursor col
  void unsetPrev() noexcept {usePrev = false;}
  // the movement must be one of hjklbfwF^$0%
  void run(const Movement* movement); 
  MovementRunner(Window*& activeWindow): 
    activeWindow{activeWindow}{}

  // predicate to chunk sequences delimited by Delim
  template<typename Impl>
  struct Chunk {
    char prev; 
    
    // set initial value of prev
    Chunk(char prev = '\0'): prev{prev} {} 

    // return Impl::operator==(ch), and set prev = ch
    bool operator==(char ch) {
      bool res = static_cast<Impl*>(this)->doCheck(ch);
      prev = ch;
      return res;
    }
  };
  // class for w. Matches iff at least one of the following: 
  // - prev == space, ch == non-space
  // - prev == alphanum, ch == punctuation
  // - prev == punctuation, ch == alphanum
  class Chunkw: public Chunk<Chunkw> {
   public: 
    Chunkw(): Chunk{'a'} {} // set initial prev with non-blank 
    bool doCheck(char ch){ 
      return 
        (isspace(prev) && !isspace(ch)) ||
        (isalnum(prev) && ispunct(ch))  ||
        (ispunct(prev) && isalnum(ch));
    }
  };
  // class for b. Matches iff at least one of the following: 
  // - prev == non-space, ch == space
  // - prev == alphanum, ch == punctuation
  // - prev == punctuation, ch == alphanum
  class Chunkb: public Chunk<Chunkb> {
   public: 
    Chunkb(): Chunk{' '} {} // set initial prev with blank 
    bool doCheck(char ch){ 
      return 
        (isspace(ch) && !isspace(prev)) ||
        (isalnum(prev) && ispunct(ch)) ||
        (ispunct(prev) && isalnum(ch));
    }
  };

  // class for W  Matches iff prev == space, ch == non-space
  class ChunkW: public Chunk<ChunkW> {
   public: 
    ChunkW(): Chunk{'a'} {} // set initial prev with non-blank 
    bool doCheck(char ch){ 
      return isspace(prev) && !isspace(ch);
    }
  };
};

#endif

