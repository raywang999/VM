#ifndef LINED_FILEBUF_H
#define LINED_FILEBUF_H

#include <filesystem> 
#include <string> 

#include "lined_charbuf.h"

// represents the underlying file inside a buffer 
// if the file is empty, provides a single empty line
template<typename char_t>
class LinedFilebuf: public LinedCharbuf<char_t> {
 public: 
  std::string filename;
  LinedFilebuf(const std::string& filename): filename{filename} {}
  // write the LinedCharbuf stored in memory to the underlying storage 
  virtual void persist() =0; 
  // retrieve permissions for the underlying file
  virtual std::filesystem::perms permissions() =0;

  virtual ~LinedFilebuf(){}
};

#endif
