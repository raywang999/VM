#ifndef MATCHER_TRIE_H
#define MATCHER_TRIE_H

#include <string>
#include <memory>
#include <unordered_map>

#include "include/resetable.h"
#include "include/loc.h"
#include "lib/command/runner/command_runner.h"
#include "lib/history/history_manager.h"
#include "lib/window/window.h"

// creates a simple DFA constructed via strings and ids
// the count reperesetns how many characters to include in the match 
// -1 for the rest of the line
class Trie: public Resetable{
 public:
  struct Node{
    // type of the current Node
    // parsing - not yet known, need more characters
    enum class Type: char{
      Parsing, Invalid, 
      IF, ELIF, ELSE, ENDIF, DEFINE,
      LRP='(', RRP=')', LSP='[', RSP=']', LPP='{', RPP='}'
    };
    std::unordered_map<char,std::unique_ptr<Node>> next;
    Type type;
    void add(const std::string& str, Type type, size_t ind=0){
      if (ind >= str.size()) {
        this->type = type;
        return;
      }
      this->type = Type::Parsing;
      if (!next.count(str[ind])){
        next.insert({str[ind], std::make_unique<Node>()});
      }
      next[str[ind]]->add(str,type,ind+1);
    }
  };
 private:
  Node rootNode;
  Node* currNode = &rootNode;
  void doReset() override {currNode = &rootNode;}
 public:
  // construct the Trie
  Trie(){
    using Type = Node::Type;
    rootNode.add("#if",Type::IF);
    rootNode.add("#elif",Type::ELIF);
    rootNode.add("#else",Type::ELSE);
    rootNode.add("#endif",Type::ENDIF);
    rootNode.add("#define",Type::DEFINE);
    rootNode.add("{",Type::LPP);
    rootNode.add("}",Type::RPP);
    rootNode.add("(",Type::LRP);
    rootNode.add(")",Type::RRP);
    rootNode.add("[",Type::LSP);
    rootNode.add("]",Type::RSP);
  }
  // add a string to the dfa
  void add(const std::string& str, Node::Type type){
    rootNode.add(str,type,0);
  }
  Node::Type getType() const noexcept {return currNode->type;}
  // returns true iff we can step successfully via ch
  Node::Type step(char ch){
    if (currNode->next.count(ch)){
      currNode = currNode->next[ch].get();
      return currNode->type;
    }
    return Node::Type::Invalid;
  }
};

#endif

