#include "lib/buffer/fstream_lfb.h"

template<typename char_t> 
FstreamLFB<char_t>::FstreamLFB(const std::string& filename): 
  LinedFilebuf<char_t>(filename)
{
  using Base = LinedCharbuf<char_t>;
  std::basic_fstream<char_t> theFS(filename, std::ios_base::in);
  char_t ch;
  Base::insertLines(0,1);
  while (theFS.get(ch)){
    if (ch == '\n'){
      Base::insertLines(Base::countLines(),1);
    } else {
      Base::append(Base::countLines()-1, ch);
    }
  }
  if (Base::countLines() > 1) {
    // not an empty file, so last line was extraneous 
    Base::eraseLines(Base::countLines()-1,1);
  }
}

template<typename char_t>
void FstreamLFB<char_t>::persist() {
  // clear old content
  std::basic_ofstream<char_t> theFS(filename, std::ofstream::out | std::ofstream::trunc); 
  // write content
  for (auto ch: *this){ // iterate through our lined_charbuf
    theFS.put(ch);
  }
}

template<typename char_t> 
std::filesystem::perms FstreamLFB<char_t>::permissions() {
  return std::filesystem::status(filename).permissions();
}
