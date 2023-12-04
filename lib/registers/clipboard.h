#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <string>
#include <unordered_map>

class Clipboard {
  // stores the line(s) copied to each register
  // default is '\0'
  std::unordered_map<char, std::string> registers;
 public:
  void set(const std::string& str, char reg = '\0'){
    registers[reg] = str;
  }
  // cycle the items perm[n]->perm[0]->perm[1]->perm[2]...->perm[n-1]
  void cycle(const std::initializer_list<char>& perm){
    auto root = *perm.begin();
    for (auto ch: perm){
      std::swap(registers[root], registers[ch]);
    }
  }
};

#endif