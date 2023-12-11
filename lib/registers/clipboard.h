#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

#include "lib/buffer/lined_charbuf.h"
#include "lib/cursor/cursor.h"

class Clipboard {
 public:
  // data can either be chars copied from a line 
  // - hence pasting will run without adding new lines
  // or a multiplicity of copied lines 
  // - so pasting will paste starting on new line
  struct Data {
    bool startNewLine = false;
    std::string contents{};
    Data(bool startNewLine = false, const std::string& contents = {}): 
      startNewLine{startNewLine}, contents{contents} {}
  };
 private:
  // stores the line(s) copied to each register
  // default register is '\0'
  // note: for some reason vim pastes 'a' char when nothing yanked so 
  std::unordered_map<char, Data> registers{{'\0',{false,"a"}}};
 public:
  // copy without adding newlines
  void set(bool startNewLine, const std::string& contents, char reg = '\0'){
    registers[reg] = {startNewLine, contents};
  }
  // copy from linedcharbuf all contents between two cursor locations
  // - cursors can be any order, but should be valid locations in charbuf 
  void copyChars(
    const LinedCharbuf<char>& charbuf, 
    const Cursor& beg, 
    const Cursor& end, 
    char reg = '\0'
  ){
    std::string contents;
    // swap beginning cursor with end if beg is after end
    int begCol = beg.getCol(), begRow = beg.getRow();
    int endCol = end.getCol(), endRow = end.getRow();
    if (begRow > endRow || (begRow == endRow && begCol >= endCol)){
      std::swap(begCol, endCol);
      std::swap(begRow, endRow);
    }
    // iterate through charbuf
    for (
      auto it = charbuf.begin(begRow, begCol); 
      it.getLine() <= endRow && it.getCol() <= endCol; 
      ++it
    ){
      contents.push_back(*it);
    }
    registers[reg] = {false, std::move(contents)}; // add contents
  }
  // copy num lines from beg from charbuf
  // precondition: beg and num are valid locations in charbuf
  void copyLines(const LinedCharbuf<char>& charbuf, size_t beg, size_t num, char reg = '\0'){
    std::string contents;
    for (size_t i = 0; i < num; ++i){
      contents.append(charbuf.getLine(beg+i));
    }
    registers[reg] = {true, std::move(contents)};
  }
  // cycle the items perm[n]->perm[0]->perm[1]->perm[2]...->perm[n-1]
  void cycle(const std::initializer_list<char>& perm){
    auto root = *perm.begin();
    for (auto ch: perm){
      std::swap(registers[root], registers[ch]);
    }
  }

  const auto& get(char reg = '\0'){ return registers[reg]; }
};

#endif