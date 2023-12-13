#include <stack>

#include "include/utility.h"
#include "matcher_runner.h"

void MatcherRunner::Matcher::fillLine(LinedCharbuf<char>::const_iterator& beg){
  prevIfBlockInds.emplace_back();
  auto& back = prevIfBlockInds.back();
  while (*beg != '\n'){
    back.push_back(fileLoc.size());
    fileLoc.push_back(beg.getLoc());
    pairLoc.push_back(beg.getLoc());
    ++beg; 
  }
}

void MatcherRunner::Matcher::fillPair(Loc loc){
  if (prevIfBlockInds.size()){
    for (auto ind: prevIfBlockInds.back()){
      pairLoc[ind] = loc;
    }
    prevIfBlockInds.pop_back();
  }
}

void MatcherRunner::Matcher::genLocations(int edit){
  prevEdit = edit;
  // iterator through charbuf, creating linelocs and their pairlocs
  auto prev = charbuf.begin(); // most recent unadded location
  auto curr = prev; // current location
  auto end = charbuf.end();
  Loc prevIfBlock; // location of previous If block
  prevIfBlockInds.clear(); // clear previous block indices
  fileLoc.clear(); pairLoc.clear();
  std::stack<size_t> leftParens; // index of previous left paren in fileLoc
  // loop through all chars
  using Type = Trie::Node::Type;
  while (curr != end){
    auto ch = *curr; ++curr;
    switch(trie.step(ch)){ // fill in locations based on what we parsed
      case Type::LPP: 
      case Type::LRP: 
      case Type::LSP:  
        // give matching right paren a index to match
        leftParens.push(fileLoc.size());
        pairLoc.emplace_back(0,0);
        // add new loc to linelocs
        fileLoc.push_back(prev.getLoc());
        prev = curr;
        trie.reset();
        break;
      case Type::RPP: 
      case Type::RRP: 
      case Type::RSP:  
        if (leftParens.size()){ // check if left exists
          auto curLoc = prev.getLoc();
          auto prevind = leftParens.top();
          leftParens.pop();
          // match prev lineloc with curr
          pairLoc[prevind] = curLoc;
          // match curr with prev, if it exists
          pairLoc.push_back(fileLoc[prevind]);
          fileLoc.push_back(curLoc);
        } 
        prev = curr;
        trie.reset();
        break;
      case Type::Invalid:
        prev = curr;
        trie.reset();
        break;
      case Type::IF: // start lineLocs
        prevIfBlock = prev.getLoc();
        fillLine(prev);
        curr = ++prev;
        trie.reset();
        break;
      case Type::ELIF: 
        // match prev lineLocs with current loc, 
        // and start new lineLocs
      case Type::ELSE: // same as ELIF
        fillPair(prev.getLoc());
        fillLine(prev);
        curr = ++prev;
        trie.reset();
        break;
      case Type::ENDIF: 
        // match prev lineLocs with current loc
        fillPair(prev.getLoc());
        // match current lineLocs with first if block
        fillLine(prev);
        fillPair(prevIfBlock);
        curr = ++prev;
        trie.reset();
        break;
      case Type::Parsing: // do nothing
        curr = curr;
        break;
      default: 
        prev = curr;
        break;
    }
  }
}

Loc MatcherRunner::Matcher::getPair(Loc loc) const{
  if (fileLoc.empty()) return loc;
  // binary search for location 
  int lo = -1, hi = static_cast<int>(fileLoc.size())-1;
  while (lo+1 < hi){
    int mi = (lo+hi)/2;
    if (fileLoc[mi] >= loc) {hi = mi;}
    else {lo = mi;}
  }
  return pairLoc[hi];
}

void MatcherRunner::run(const Movement* cmd) {  
  if (cmd->type != '%') return; 
  auto& tab = activeWindow->getTabManager().curr();
  const auto& filebuf = tab.getFilebuf();
  const auto& filename = filebuf.getFilename();
  // check if locations need to be regenerated
  if (!matcherManager.count(filename)){
    matcherManager.emplace(filename, filebuf);
  }
  auto& matcher = matcherManager.at(filename);
  auto currEdit = historyManager.getTree(filebuf.getFilename()).getCurr();
  if (matcher.getEdit() != currEdit){ // if different, regenerate locations
    matcher.genLocations(currEdit);
  }
  // find the paired location
  auto cursor = tab.getCursor();
  auto curLoc = cursor.getLoc();
  auto newLoc = matcher.getPair(curLoc);
  // move cursor to paried location
  if (curLoc != newLoc){
    cursor.translate(newLoc.line, newLoc.col);
    tab.setCursor(cursor, true);
  }
}
