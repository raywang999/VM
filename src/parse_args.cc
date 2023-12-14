#include <map>

#include "parse_args.h"

void TerminalArgs::parseFlag(size_t& i){ 
  const auto& flag = TerminalArgs::args[i];
  if (flag == "--highlight-syntax"){
    TerminalArgs::options.push_back(TerminalArgs::HighlightSyntax{});
  } else if (flag == "--help" || flag == "-h"){
    TerminalArgs::options.push_back(TerminalArgs::ShowHelp{});
  } else if (flag == "--enable-macros"){
    TerminalArgs::options.push_back(TerminalArgs::EnableMacros{});
  } else if (flag == "--show-color"){
    TerminalArgs::options.push_back(TerminalArgs::ShowColor{});
  } else if (flag == "--color-set"){
    std::string colorset = TerminalArgs::args[++i];
    TerminalArgs::options.push_back(TerminalArgs::SetColorset{colorset});
  } 
}


void TerminalArgs::parse(size_t& i){
  if (args[i][0] == '-'){
    parseFlag(i);
  } else {
    files.push_back(args[i]);
  }
}


// preforms actions based on terminal supplied options
void TerminalArgs::parseArgs(){
  for (size_t i=0; i < args.size();++i){
    parse(i);
  }
}

