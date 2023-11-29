# UML Diagrams 
```cc
using Command = variant<
  Normal, 
  Movement, 
  Insert, 
  PartialInsert, 
  Replace,
  PartialReplace,
  Ex,
>;
```
- I initially had `Command` as an abstract class because
  - I wanted to have an `undo` interface for `Commands` to inherit 
    - e.g. a `Movement` command could have an `undo()` method 
that returns the inverse movement 
- Ultimately decided to use a variant 
  - most consumers of `Command`s would always `dynamic_cast` them 
to get their types
  - managing history should be separate from storing `Command` 
info 
  - a solution using `Memento` pattern or by storing 
  `stack past; stack future;` is better
```plantuml
left to right direction
struct Command{}
note top of Command: Variant 
struct Normal{
  +count: Integer
  +type: Character
}
struct Movement{
  +count: Integer
  +type: Character
}
struct ComboNM{
  +normal: Normal
  +movement: Movement
}
struct Ex{
  +sentence: String
}
struct Insert{
  +sentence: String
}
struct PartialInsert{
  +ch: Character
}
struct Replace{
  +sentence: String
}
struct PartialReplace{
  +ch: Character
}
Command <-- Normal
Command <-- Movement
Command <-- ComboNM
Ex --> Command 
Insert --> Command 
PartialInsert --> Command 
Replace --> Command 
Command <-- PartialReplace
```
```plantuml 
left to right direction
abstract KeystrokeSource{
  +addConsumer(KeystrokeConsumer)
  +notifyAll()
}
KeystrokeSource <- Keyboard
abstract KeystrokeConsumer{
  {abstract}+consume(Keystroke)
}
KeystrokeSource "0..*" o--> KeystrokeConsumer
KeystrokeConsumer <-- KeystrokeBuffer
abstract Mode{}
abstract CommandParser{
  +reset()
}
KeystrokeConsumer <- CommandParser 
Mode "0..*" <-* ModeManager
ModeManager -> CommandRunner
abstract CommandSource{
  {abstract}+runAll(): void
}
CommandParser"0..*" <--* Mode 
CommandParser -> CommandSource 
abstract CommandRunner{
  {abstract}+run(Command): void
}
CommandSource "0..*" o--> CommandRunner
```
```plantuml
left to right direction
abstract LinedFilebuf{}
class Cursor{
  -line: Integer
  -col: Integer
  +getCol(): Integer 
  +getLine(): Integer 
  +setCol(Integer)
  +setLine(Integer)
}
class TabManager {
  +nextTab()
  +currTab()
  +prevTab()
}
Window --> TabManager
abstract Window{
  -type: WindowType
  -parent: Window*
  -children: Window*[0..*]
  +splitVert(): Boolean
  +splitHori(): Boolean
  +delete(Window* child)
}
enum WindowType{
  VertSplit, HoriSplit, NoSplit
}
class Tab{
  +setLine(line: Integer, anchor: Anchor) 
  +setCursor(line: Integer, col: Integer)
  +getTopLine(): Integer
}
Tab "1" o-- LinedFilebuf
Tab "1" *- Cursor
TabManager "1..*" *-- Tab
Window -* WindowType
class NCWindow{
  +render(): void
}
NCWindow -> Window
NCWindow "1" *--> Textbox
Textbox "1" o--> StyleManager
class Textbox{}
abstract TextStyler{
  {abstract}+getStyles(first: Integer, last: Integer): Style[0..*]
}
abstract StyleManager{
  {abstract}+getStylers(string filename): TextStyler[0..*]
}
StyleManager "0..*" *--> TextStyler
NCWindow "1" *--> StatusBar
TextStyler "1" o-> LinedFilebuf
class StatusBar{}
struct Style{
  first: Integer, 
  last: Integer, 
  attribute: Integer
}
Style "0..*"<-* TextStyler 
```
```plantuml
left to right direction
abstract Window{ }
class Tab{
  +setLine(line: Integer, anchor: Anchor) 
  +setCursor(line: Integer, col: Integer)
  +getTopLine(): Integer
}
abstract Renderable{
  {abstract}+render(): void
}
class NCWindow{
  +render(): void
}
Translateable <-- Cursor
NCWindow "1" *-> Textbox
RenderableBox <-- StatusBar 
RenderableBox <-- Textbox
StatusBar "1" <-* NCWindow
class StatusBar{}
abstract Resizeable{
  -height: Integer 
  -width: Integer
  {abstract} - doResize()
  +resize(h: Integer, w: Integer)
}
abstract Translateable{
  -toprow: Integer
  -leftcol: Integer
  +transform(r: Integer, c: Integer)
}
abstract Box{}
Box --> Resizeable 
Translateable <- Box
abstract RenderableBox {}
Box -> RenderableBox 
RenderableBox <- Renderable
Window <-- NCWindow 
RenderableBox <-- Window 
Resizeable <-- Tab
```
```plantuml
left to right direction 
abstract class LinedFilebuf{
  {abstract}+erase( size_t line, size_t start, size_t len): void
  {abstract}+insert(size_t line, size_t start, string_view): void
  {abstract}+erase_lines(size_t line, size_t len): void
  {abstract}+insert_lines(size_t line, size_t len): void
  {abstract}+begin(): iterator
  {abstract}+end(): iterator
}
class FileManager{
  -index
  -map<String, unique_ptr<LinedFilebuf>>
  +open(String filename): LinedFilebuf* 
  +next(): LinedFilebuf*
  +prev(): LinedFilebuf*
  +FileManager(files String[0..*])
}
FileManager "0..*" *-- LinedFilebuf
```
```plantuml 
left to right direction
abstract CommandParser{
  {abstract}-doConsume(Keystroke): Boolean
  +reset()
  +consume(Keystroke)
}
NormalParser --> CommandParser
ExParser --> CommandParser
CommandParser <-- InsertParser
CommandParser <-- ColonParser

```
```cc 
main(){
  Keyboard keyboard{};
  ModeManager modeManager({Normal, CmdLine, });
  keyboard.addWatcher(modeManager);
  KeystrokeBuf keystrokeBuf{};
  keyBoard.addWatcher(keystrokeBuf);
}
```
```plantuml 
left to right direction
enum ModeType{
  Normal, CmdLine, Insert, Replace
}
ModeType "1" <-* ModeManager
abstract CommandSource{}
abstract Mode{
  +consume(Keystroke)
}
KeystrokeConsumer <-- Mode 
Mode --> CommandSource
abstract CommandRunner
abstract CommandParser
Mode "0..*" *--> CommandParser
CommandRunner "0..*" <--o Mode 
class ModeManager{
  -active: ModeType
  -map<ModeType, CommandParser*>
  +consume(Keystroke)
}
abstract KeystrokeConsumer{}
ModeManager --> CommandSource
KeystrokeConsumer <-- ModeManager
ModeManager "0..*" *-> Mode
```
- note: `Mode` will reset all `CommandParser`s it owns when one of them 
"finishes processing" where 
  - for normal mode, that means a command is issued 
  - for insert/replace, means a non-partial command was issued

# Plan of Attack 
## Get something showing 
- Implement `Cursor` with getters, setters 
- Implement `LinedFileBuf`
  - Implement a `Placehol` concrete LinedFileBuf
- Implement `Tab`
  - getters, setters
- implement `Window`'s getters, setters
- implement `Textbox`, `StatusBar`
  - basic rendering, no styles  
- implement `NCWindow`
  - call render on textbox, statusbar
- write a `main` file that instantiates a `NCWindow` with our `Placeholder` 
- test basic features 
  - cursor position is correct 
  - status bar is on bottom of screen
  - text in textbox appears line by line

## Work on Controller 
- implement Subject Observer templates (copy from a4)
- implement KeystrokeSource, KeystrokeConsumer 
- implement a concrete `Keyboard`
  - adapt Ncurses keyboard api to `Keystrokes` 
  - unit test our `Keyboard`

## Work on Basic Model 
- implement `Command` variants 
- implement `CommandSource`, `CommandParser`, `CommandRunner`
- implement an `InsertParser`, `MacroParser`
- implement `Mode`
  - implement concrete `InsertMode`
- implement `ModeManager` for `ModeType::Insert` 
- implement `InsertRunner`
- extend `main` to instantiate 
  - `NCWindow`, `Placeholder`, `Keyboard`, 
  - `ModeManager` with an `InsertMode` that links an `InsertParser` to the `InsertRunner`
  - attach the objects so that typing appends to the rendered textbox 

## Add basic VM commands
- implement `NormalParser`, `NormalMode`
- extend `ModeManager` to work with `NormalMode`
  - add `Esc` handler 
- Implement a proper `LinedFileBuf`
  - manages a `fstream` 
  - maintains `vector<string> lines` 
  - syncs `fstream` with `lines`
  - give returns of begin and end efficient `random_access_iterator`
- Implement a `NormalRunner` 
- test simple commands (`x, i, esc`)
- Implement `Cmdline` mode 
  - Implement `ExRunner`
- Implement search-related commands (`f,I,%`)

## Extend Model
- Implement `/, ?`
- Implement Combo commands (`2d3fa`) 
- Implement `Replace` mode 
- Implement `MacroParser, MacroMode`
- Implement `MacroRunner` 
  - Implement a `MacroManager` 
  - Implement `@` Macro playback 
- Implement `Ctrl` commands 
- Implement Undo 
  - Implement a tuple that can store forward and backwards information
  - Implement a `HistoryManager`
  - Implement a `CommandInverter`  

## Improve View 
- Extend `StatusBar` to reflect required info 
- Extend `Tab` to sync Cursor and Window Movements

# Extras
## Multiwindow & Multifile 
- Implement `FileManager`, adapt concrete `CommandRunner`s
- Implement `Window` fully 
  - Implement `resize()`s
  - Implement `splitVert(), splitHori(), delete()`

## Add Syntax Highlighting
- Implement `TextStyler`
- Implement `BracketStyler: public TextStyler` 
  - Identify Nesting level 
  - Match pairs of brackets 
  - Identify mismatching brackets
- Implement `CppHighlighter`
  - Implement a Tokenizer
  - Implement a no-lookahead Parse Graph
    - For Keywords, Numerics, Preprocessor Directives
    - Can extend to a more extended parse graph
  - Implement a `Stylizer` structure that implements `TextStyler::getStyles(...)`


## Improve Controls  
- Add support for arrow keys 
- Add support for mouse scrolling


