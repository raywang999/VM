#include <map>

#include "parse_args.h"

void Main::parseFlag(size_t& i){ 
  const auto& flag = Main::args[i];
  if (flag == "--highlight-syntax"){
    Main::options.push_back(Main::HighlightSyntax{});
  } else if (flag == "--enable-macros"){
    Main::options.push_back(Main::EnableMacros{});
  } else if (flag == "--multi-file"){
    Main::options.push_back(Main::EnableMultifile{});
  } else if (flag == "--show-color"){
    Main::options.push_back(Main::ShowColor{});
  } else if (flag == "--color-set"){
    std::string colorset = Main::args[++i];
    Main::options.push_back(Main::SetColorset{colorset});
  } 
}


void Main::parse(size_t& i){
  //static DfaStep next[256];
  if (args[i][0] == '-'){
    parseFlag(i);
  } else {
    files.push_back(args[i++]);
  }
}


// preforms actions based on terminal supplied options
void Main::parseArgs(){
  for (size_t i=0; i < args.size();++i){
    parse(i);
  }
}
