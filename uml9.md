```plantuml
left to right direction 
class Main{ 
  main(): void
}
abstract KeystrokeSource
class TerminalArgs{ 
  + files: String[0..*]
  + flags: String[0..*]
  + options: Option[0..*]
  +hasOption(option: Option): bool
  parseArgs(): void
}
class NcursesClosure {
  -terminalArgs: TerminalArgs*
}
class UWSEKeyboard {}
class StyleManager {}
class WindowsClosure {
  +activeWindow: Window**
  +WindowsClosure(tabs: TabsClosure*, styler: StyleManager*)
}
class HistoryClosure {
  +tabsClosure: TabsClosure*
  +cursorRecorder: CursorRecorder 
  +historyRecorder: HistoryRecorder 
  +macroRecorder: HistoryRecorder 
  +macroCursor: CursorRecorder 
  +HistoryClosure(tabs: TabsClosure*, windows: WindowsClosure*)
}
class ModesClosure {
  +windowsClosure: WindowsClosure*
  +tabsClosure: TabsClosure*
  +historyClosure: HistoryClosure*
  +modeManager: ModeManager 
  +clipboard: Clipboard 
  +macroRecorder: KeystrokeRecorder 
  +exRunner: ExRunner
  +exParser: ExParser
  +exMode: Mode
  +setModeParser: SetModeParser
  +setModeRunner: SetModeRunner
  +dotRepeater: DotRepeater
  +undoRunner: UndoRunner
  +messageResetter: MessageResetter
}
class StatusBarClosure {
  +windowsClosure: WindowsClosure
  +modesClosure: ModesClosure
  +renderStatusBar(): void
}
class SearchModeClosure{
  windowsClosure: WindowsClosure*
  modeManager: ModeManager*
  searchParser: SearchParser
}
class NormalModeClosure{
  windowsClosure: WindowsClosure*
  historyClosure: HistoryClosure*
  modeManager: ModeManager*
  searchModeClosure: SearchModeClosure*
  "parsers and runners..."
  parserGroup: ParserGroup
}
class InsertModeClosure{
  +windowsClosure: WindowsClosure*
  +insertParser: InsertParser
  +insertRunner: InsertRunner
  +insertReflector: InsertReflector
  +insertMode: Mode
}
class CursorClosure{
  +windowsClosure: WindowsClosure*
  +modesClosure: ModesClosure*
  ncCursor: NCCursor
  +renderCursor(): void
}
Main o-- UWSEKeyboard
UWSEKeyboard --|> KeystrokeSource
Main o-- TerminalArgs
Main o-- NcursesClosure
Main o-- TabsClosure
TabsClosure "1" o-- TabManager
TabsClosure "1" o-- FileManager
TabsClosure "read files" o- TerminalArgs
WindowsClosure --o Main
RootStatus --o "1" WindowsClosure
RootStatusRender --o "1" WindowsClosure
NCWindow --o "1" WindowsClosure
HistoryClosure --o "1" Main
WindowsClosure -o "1" HistoryClosure
HistoryManager --o "1" HistoryClosure
ModesClosure -o "1" Main
InsertModeClosure --o "1" ModesClosure
SearchModeClosure --o "1" ModesClosure
NormalModeClosure --o "1" ModesClosure
NormalParser --o NormalModeClosure
MovementParser --o NormalModeClosure
ComboNMParser --o NormalModeClosure
Main o- CursorClosure
Main o-- StatusBarClosure
Main o-- StyleManager
```