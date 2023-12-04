# UML Diagrams 
```plantuml
left to right direction
abstract Command{}
class Normal{
  +count: Integer
  +type: Character
}
class Movement{
  +count: Integer
  +type: Character
}
class ComboNM{
  +normal: Normal
  +movement: Movement
}
class Ex{
  +sentence: String
}
class Insert{
  +count: Integer
  +sentence: String
}
class Replace{
  +count: Integer
  +sentence: String
}
Command <|-- Normal
Command <|-- Movement
Command <|-- ComboNM
Ex --|> Command 
Insert --|> Command 
Replace --|> Command 
```
```plantuml 
abstract Window
class Keyboard{
  +next(): void
  +getKeystroke(): Keystroke
}
left to right direction
enum KeyType {
  Esc, Plain, Ctrl, Del, Backspace
}
class Keystroke {
  +count: Integer
  +data: Character
}
abstract KeystrokeSource{
  +attach(consumer: KeystrokeConsumer*): void
  {abstract}+getKeystroke(): Keystroke
  +notifyAll(): void
}
Keystroke "1" *-- KeyType
Keyboard "1" *-- Keystroke
Keyboard -|> KeystrokeSource 
abstract KeystrokeConsumer{
  {abstract}+consume(key: Keystroke): void
  {abstract}+notify(source: KeystrokeSource*): void
}
KeystrokeSource "0..*" o---|> KeystrokeConsumer
abstract Mode{}
abstract CommandParser{
  {abstract}-doReset(): void
  +reset(): void
}
class NormalParser {
  -doReset(): void
  +getNormal(): Normal
}
class MovementParser {
  -doReset(): void
  +getMovement(): Movement
}
class ModeManager{
  +consume(key: Keystroke): void
  +notify(source: KeystrokeSource*): void
}
enum ModeType{
  Normal, Insert, Replace, Ex
}
ModeType "1" -* ModeManager
class Mode {
  +consume(key: Keystroke): void
}
KeystrokeConsumer <|- CommandParser 
ModeManager "0..*" o- Mode 
KeystrokeConsumer <|-- ModeManager
abstract CommandSource{
  +notifyAll(): void
  +attach(runner: CommandRunner*): void
}
KeystrokeConsumer --o "0..*" Mode 
CommandParser -|> CommandSource 
abstract CommandRunner{
  {abstract}+run(command: Command*): void
  +notify(source: CommandSource*): void
}
CommandSource "0..*" o- CommandRunner
MovementParser --|> CommandParser
CommandRunner <|- NormalRunner 
MovementRunner --|> CommandRunner 
MovementRunner "1" o- Window
Window --o "1" NormalRunner 
MovementParser --o "1" MovementRunner 
class InsertReflector {
  +consume(key: Keystroke): void
}
KeystrokeConsumer <|-- InsertReflector 
CommandParser <|-- NormalParser
NormalRunner "1" o-- NormalParser 
```
```plantuml 
left to right direction
abstract Window{}
abstract CommandParser{
  {abstract}-doReset(): void
  {abstract}-parse(key: Keystroke): Boolean
  +reset(): void
  +consume(key: Keystroke): void
}
abstract CommandRunner {
  +{abstract}run(command: Command*): void
  +notify(source: CommandSource*): void
}
CommandParser "0..*" o-- CommandRunner
class NormalParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getNormal(): Normal
}
class MacroParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getMacro(): Macro
}
class MacroRunner {
  -registers: map<Character, CommandChain>
  +run(command: Command*): void
}
class NormalRunner {
  +run(command: Command*): void
}
MacroRunner -|> CommandRunner
CommandRunner <|- NormalRunner 
CommandParser <|- NormalParser
MacroParser -|> CommandParser 
NormalParser --o "1" NormalRunner
MacroParser --o "1" MacroRunner 
class CommandChain{
  +run(command: Command*): void 
  +runChain(): void
}
abstract Command{}
Command "0..*" -* CommandChain 
CommandRunner <|-- CommandChain
NormalRunner "1" o- Window
CommandChain "1" o- Window 
```
```plantuml
left to right direction
abstract LinedFilebuf{}
class TabManager {
  +nextTab(): void
  +currTab(): Tab
  +prevTab(): void
}
Window "1" *--> TabManager
abstract Window{
  -parent: Window*
  -children: Window*[0..*]
  +splitVert(): Boolean
  +splitHori(): Boolean
  +delete(child: Window*)
}
enum WindowType{
  VertSplit, HoriSplit, NoSplit
}
class Tab{
  +getTopLine(): Integer
}
Tab "1" o-- LinedFilebuf
Tab "1" *- Cursor
TabManager "1..*" *-- Tab
Window "1" *- WindowType
class NCWindow{
  +render(): void
}
NCWindow -|> Window
NCWindow "1" *-- Textbox
Textbox "1" o-- StyleManager
class Textbox{
  +render(): void
}
abstract TextStyler{
  {abstract}+getStyles(first: Integer, last: Integer): Style[0..*]
}
class StyleManager{
  +getStylers(filename: String): TextStyler[0..*]
}
StyleManager "0..*" *-- TextStyler
NCWindow "1" *-- StatusBar
class StatusBar{
  +render(): void
}
struct Style{
  first: Integer, 
  last: Integer, 
  attribute: Integer
}
class RainbowBrackets {
  +getStyles(first: Integer, last: Integer): Style[0..*]
}
class CppHighlight {
  +getStyles(first: Integer, last: Integer): Style[0..*]
}
CppHighlight --|> TextStyler 
RainbowBrackets "reads" -> LinedFilebuf
CppHighlight "reads" -> LinedFilebuf
TextStyler <|- RainbowBrackets 
Style "0..*"-* TextStyler 
abstract class LinedFilebuf{
  {abstract}+erase(line: Integer, start: Integer, len: Integer): void
  {abstract}+insert(line: Integer, start: Integer, chars: String): void
  {abstract}+eraseLines(line: Integer, len: Integer): void
  {abstract}+insertLines(line: Integer, len: Integer): void
  {abstract}+begin(): Iterator
  {abstract}+end(): Iterator
}
StatusBar "reads" --> ModeManager
StatusBar "reads" -> TabManager
class FileManager{
  +open(filename: String): LinedFilebuf* 
}
LinedFilebuf "0..*" -* FileManager 
```
```plantuml
left to right direction
abstract Window{ }
class Tab{
  +getTopLine(): Integer
}
abstract Renderable{
  {abstract}+render(): void
}
class NCWindow{
  +render(): void
}
Translateable <|-- Cursor
NCWindow "1" *- Textbox
RenderableBox <|-- StatusBar 
RenderableBox <|-- Textbox
StatusBar "1" -* NCWindow
class StatusBar{}
abstract Resizeable{
  -height: Integer 
  -width: Integer
  +resize(h: Integer, w: Integer)
}
abstract Translateable{
  -toprow: Integer
  -leftcol: Integer
  +transform(r: Integer, c: Integer)
}
class StatusBar{
  +render(): void
}
class Textbox{
  +render(): void
}
abstract Box{}
Box --|> Resizeable 
Translateable <|- Box
abstract RenderableBox {}
Box <|- RenderableBox 
RenderableBox -|> Renderable
Window <|-- NCWindow 
RenderableBox <|-- Window 
Resizeable <|-- Tab
```
# Plan of Attack 
## Get something showing 
- Implement `Cursor` with getters, setters 
- Implement `LinedFileBuf`
  - Implement a `Placeholder` concrete LinedFileBuf 
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
- Implement a proper `LinedFileBuf`
  - manages a `fstream` 
  - maintains `vector<string|> lines` 
  - syncs `fstream` with `lines`
  - give returns of begin and end efficient `random_access_iterator`
- implement `NormalParser`, `NormalMode`
- extend `ModeManager` to work with `NormalMode`
  - add `Esc` handler 
- Implement a `NormalRunner` 
- test simple commands (`x, i, esc`)
- Implement `Cmdline` mode 
  - Implement `ExRunner`
- Implement search-related commands (`f,I,%`)

## Extend Model
- Implement `/, ?`
- Implement Combo commands (`2d3fa`) 
- Implement `Replace` mode 
- Implement `Ctrl` commands 
- Implement Undo 
  - Implement a tuple that can store forward and backwards information
  - Implement a `CommandChain`
  - Implement a `CommandInverter` helper
- Implement `MacroParser, MacroMode`
- Implement `MacroRunner` 
  - Implement a `MacroManager` 
  - Implement `@` Macro playback 

## Improve View 
- Extend `StatusBar` to reflect required info 
- Extend `Tab` to sync Cursor and Window Movements

# Extras
## Multiwindow & Multifile 
- Implement `FileManager`
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
