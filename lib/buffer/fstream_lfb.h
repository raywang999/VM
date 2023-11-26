#ifndef FSTREAM_LINED_FILBUF_H
#define FSTREAM_LINED_FILBUF_H

#include <fstream>

#include "lib/buffer/lined_filebuf.h"

template<typename char_t> 
class FstreamLFB: public LinedFilebuf<char_t> {
 public: 
  using LinedFilebuf<char_t>::filename;
  // initialize with a file
  FstreamLFB(const std::string& filename = ""); 
  // write the LinedCharbuf stored in memory to the underlying storage 
  void persist() override; 
  // retrieve permissions for the underlying file
  virtual std::filesystem::perms permissions() override;
};

#endif