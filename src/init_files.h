#ifndef INIT_FILES_H
#define INIT_FILES_H

#include <string>

#include "parse_args.h"

#include "lib/buffer/file_manager.h"

struct FilesClosure{
  TerminalArgs& args;
  // open all the files given by terminal args into their own tabs
  // opens a temporary file if none are provided
  FilesClosure(TerminalArgs& args): args{args} {
    const auto& files = args.files;
    if (files.empty()){
      fileManager.open("temporaryvmfile.txt").get();
    } else {
      for (auto file: files){
        auto filebufp = fileManager.open(file).get();
        rootTabManager.emplace_back(*filebufp);
      }
    }
    activeTab = &rootTabManager.curr();
  }
};

#endif
