#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <unordered_map>
#include <string>
#include <memory>

#include "lib/buffer/lined_filebuf.h"
#include "lib/textbox/stylemanager.h"
#include "lib/buffer/fstream_lfb.h"

// manages collections of Filenames, and their corresponding 
// `LinedFilebuf`s, `TextStyler`s, and `History`s. 
// based on the filetype 
class FileManager {
  using filebuf_ptr = std::unique_ptr<LinedFilebuf<char>>;
  std::unordered_map<std::string, filebuf_ptr> files;
 public: 
  // returning Data for the file, opening it if necessary
  filebuf_ptr& open(const std::string& filename){
    auto& file_p = files[filename];
    if (file_p.get()) return file_p; // file was already opened
    // otherwise, create the stylers and filebuf
    file_p = std::make_unique<FstreamLFB<char>>(filename);
    return file_p;
  }
  size_t isOpen(const std::string& file) const {return files.count(file);}
};

#endif
