#ifndef INIT_HISTORY_H
#define INIT_HISTORY_H

#include "init_tabs.h"
#include "init_windows.h"

#include "lib/history/history_recorder.h"
#include "init_tabs.h"
#include "init_windows.h"

struct HistoryClosure{
  TabsClosure& tabsClosure;
  WindowsClosure& windowsClosure;
  HistoryManager historyManager;

  CursorRecorder cursorRecorder{windowsClosure.activeWindow};
  HistoryRecorder historyRecorder{windowsClosure.activeWindow, historyManager, cursorRecorder};
  // recorders for running macros
  HistoryRecorder macroRecorder{windowsClosure.activeWindow, historyManager, cursorRecorder};
  CursorRecorder macroCursor{windowsClosure.activeWindow};

  HistoryClosure(TabsClosure& tabsClosure, WindowsClosure& windowsClosure): 
    tabsClosure{tabsClosure}, windowsClosure{windowsClosure} {
    for (const auto& tab: tabsClosure.rootTabManager.getItems()){
      historyManager.save(tab, Cursor{0,0});
    }
    macroRecorder.setActive(false); // keep deactivated until macro runner needs it
    macroCursor.active = true; // listen initially, until the macro runs
    historyRecorder.setActive(true);
  }
};

#endif
