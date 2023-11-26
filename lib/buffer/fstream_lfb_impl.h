#include "lib/buffer/fstream_lfb.h"

template<typename char_t> 
FstreamLFB<char_t>::FstreamLFB(const std::string& filename): 
  LinedFilebuf<char_t>(filename)
{
  std::basic_fstream<char_t> theFS(filename, std::ios_base::in);
  char_t ch;
  if (theFS.get(ch)){
    // the file isn't empty
    LinedCharbuf<char_t>::insert_lines(0,1);
    if (ch != '\n'){
      LinedCharbuf<char_t>::append(0,ch);
    }
  }
  while (theFS.get(ch)){
    if (ch == '\n'){
      LinedCharbuf<char_t>::insert_lines(LinedCharbuf<char_t>::countLines(),1);
    } else {
      LinedCharbuf<char_t>::append(LinedCharbuf<char_t>::countLines()-1, ch);
    }
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
