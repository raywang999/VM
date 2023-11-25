#ifndef LINED_FILEBUF_H
#define LINED_FILEBUF_H

#include <filesystem> 

#include "lined_charbuf.h"

template<typename char_t> 
class LinedFilebuf: public LinedCharbuf<char_t> {
 public: 
  // write the LinedCharbuf stored in memory to the underlying storage 
  virtual void persist() =0; 
  // retrieve permissions for the underlying file
  virtual std::filesystem::perms permissions() =0;
};

#endif