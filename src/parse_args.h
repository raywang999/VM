#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <vector> 
#include <string>
#include <variant>

// collection of globals used by main.cc and its helpers

class TerminalArgs {
  void parse(size_t&i);
  void parseFlag(size_t&i);
 public:
  // files passed as cmdline args
  std::vector<std::string> files, args;
  // parse terminal args from main
  TerminalArgs(int argc, const char* argv[]){
    for (int i=1; i < argc; ++i){
      args.push_back(argv[i]);
    }
    parseArgs();
  }
  struct HighlightSyntax {};
  struct SplitScreen {};
  struct ShowColor{};
  struct EnableMacros{};
  struct EnableMultifile{};
  struct SetColorset{
    std::string colorset;
  };
  using Option = struct std::variant<
    HighlightSyntax, 
    SplitScreen, 
    ShowColor, 
    SetColorset, 
    EnableMacros, 
    EnableMultifile
  >;
  std::vector<Option> options;
  
  inline auto find(Option option){
    return std::find_if(options.begin(), options.end(), [option](const Option& other){
      return option.index() == other.index();
    });
  }

  inline bool hasOption(Option option) {
    return find(option) != options.end();
  }
  // preforms actions based on terminal supplied options
  void parseArgs();

};


#endif
