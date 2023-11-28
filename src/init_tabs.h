#ifndef INIT_TABS_H
#define INIT_TABS_H

#include <string>

#include "parse_args.h"

#include "lib/buffer/file_manager.h"
#include "lib/tab/tabmanager.h"
#include "lib/tab/tab.h"

struct TabsClosure{
  // root tab manager holding tabs for initially opened files
  TabManager rootTabManager;

  // open all the files given by terminal args into their own tabs
  // opens a temporary file if none are provided
  TabsClosure(TerminalArgs& args, FileManager& fileManager) {
    const auto& files = args.files;
    if (files.empty()){
      auto filebufp = fileManager.open("temporaryvmfile.txt").get();
      rootTabManager.emplace_back(filebufp);
    } else {
      for (auto file: files){
        auto filebufp = fileManager.open(file).get();
        rootTabManager.emplace_back(filebufp);
      }
    }
  }
};

#endif
