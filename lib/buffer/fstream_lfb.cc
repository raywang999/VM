#include "lib/buffer/fstream_lfb.h"

template<typename char_t> 
FstreamLFB<char_t>::FstreamLFB(const std::string& filename): 
  filename{filename}, 
{
  std::basic_fstream<char_t> theFS(filename, std::ios_base::in);
  char_t ch;
  if (theFS.get(ch)){
    // the file isn't empty
    insert_lines(0,1);
    if (ch != '\n'){
      append(0,ch);
    }
  }
  while (theFS.get(ch)){
    if (ch == '\n'){
      insert_lines(getLines(),1);
    } else {
      append(getLines()-1, ch);
    }
  }
}

template<typename char_t>
void FstreamLFB<char_t>::persist() {
  // clear old content
  std::basic_ofstream theFS(filename, std::ofstream::out | std::ofstream::trunc); 
  // write content
  for (auto ch: *this){ // iterate through our lined_charbuf
    theFS.put(ch);
  }
}

template<typename char_t> 
std::filesystem::perms FstreamLFB<char_t>::permissions() {
  return std::filesystem::status(filename).permissions();
}
