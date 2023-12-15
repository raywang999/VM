# UML Diagrams 
```plantuml
left to right direction
abstract Command{}
class Normal{
  +count: Integer
  +type: Character
  +data: Character
}
class Movement{
  +count: Integer
  +type: Character
  +seek: Character
}
class ComboNM{
  +normal: Normal
  +movement: Movement
}
class Ex{
  +sentence: String[0..*]
}
class Insert{
  +count: Integer
  +mode: Character
  +sentence: String
}
class Replace{
  +count: Integer
  +sentence: String
}
class SetMode {
  +count: Integer 
  +type: Character
  +clone(): SetMode
}
class CM {
  +movement: Movement
  +clone(): SetMode
}
class Ctrl {
  +count: Integer
  +type: Character
}
class Search {
  +needle: String
  +type: Character
}
class Macro {
  +count: Integer 
  +reg: Character 
  +type: Character
}
SetMode -|> Command
SetMode <|-- CM
Command <|- Normal
Command <|--- Movement
Command <|-- ComboNM
Ctrl ---|> Command
Replace --|> Command 
Insert ---|> Command 
Command <|-- Search
Macro --|> Command
Command <|--- Ex
```
```plantuml 
class Keyboard{
  +next(): void
  +getKeystroke(): Keystroke
}
class Resetable {
  -doReset(): void 
  +reset(): void
}
left to right direction
enum KeyType {
  Esc, Plain, Ctrl, Del, Backspace
}
class Keystroke {
  +data: Character
}
abstract "Subject<KeyStroke, KeystrokeSource>"{
  +attach(consumer: KeystrokeConsumer*): void
  +notifyAll(): void
}
abstract KeystrokeSource{
  {abstract}+getKeystroke(): Keystroke
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
abstract "CommandParser<CT>"{ }
class ModeManager{
  +consume(key: Keystroke): void
  +notify(source: KeystrokeSource*): void
}
class InsertReflector
KeystrokeConsumer <|- InsertReflector
enum ModeType{
  Normal, Insert, Replace, Ex
}
ModeType "1" -* ModeManager
class Mode {
  +consume(key: Keystroke): void
}
ModeManager "0..*" o- Mode 
KeystrokeConsumer <|-- ModeManager
abstract BaseCommandParser
abstract "CommandSource<CT>"{
}
KeystrokeConsumer --o "0..*" Mode 
abstract "CommandRunner<CT>"{
  {abstract}+run(command: Command*): void
  +notify(source: "CommandSource<CT>"*): void
}
KeystrokeSource -|> "Subject<KeyStroke, KeystrokeSource>"
"CommandSource<CT>" <|--"CommandParser<CT>"  
Resetable <|-- BaseCommandParser
BaseCommandParser <|-"CommandParser<CT>"
KeystrokeConsumer <|- BaseCommandParser
"CommandRunner<CT>" --o "0..*""CommandSource<CT>" 
abstract "Subject<CT,CommandSource<CT>>" {
  +notifyAll(): void
  +attach(runner: CommandRunner*): void
}
"Subject<CT,CommandSource<CT>>" <|- "CommandSource<CT>"
```
```plantuml 
left to right direction
abstract Window{}
struct Data{
  +contents: String
  +addNewline: Boolean
}
class Clipboard{
}
class RootStatus{
  -message: String
  -errorCode: Integer
}
abstract "CommandParser<ComboNM>"{
  {abstract}-doReset(): void
  {abstract}-parse(key: Keystroke): Boolean
  +reset(): void
  +consume(key: Keystroke): void
}
abstract "CommandRunner<ComboNM>" {
  +{abstract}run(command: Command*): void
  +notify(source: CommandSource*): void
}
class ComboNMParser {
  -doReset(): void
  +getComboNM(): ComboNM
}
class ComboNMParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getComboNM(): ComboNM
}
class ComboNMRunner {
  -dotRepeater: DotRepeater*
  -semiColonRepeater: SemiColonRepeater*
  -movementRunner: MovementRunner*
  -matcherRunner: MatcherRunner*
  -normalRunner: NormalRunner
  +run(command: ComboNM*): void
}
Data --o "0..*" Clipboard 
"CommandRunner<ComboNM>" <|-- ComboNMRunner 
ComboNMParser --|> "CommandParser<ComboNM>" 
ComboNMRunner "1" o-- Window 
ComboNMRunner o-- RootStatus
Clipboard -o ComboNMRunner 
"CommandParser<ComboNM>" "0..*" o-- "CommandRunner<ComboNM>"
```
```plantuml
left to right direction
class MovementParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getMovement(): Movement
}
abstract "CommandParser<Movement>"{ }
abstract "CommandRunner<Movement>" { }
class MovementRunner {
  -window: Window**
  +run(command: Movement*): void
}
abstract "CommandRunner<Search>"{}
class SemiColonRepeater{}
class SearchRunner {
  -movementRunner: MovementRunner*
}
class MatcherRunner{
  -window: Window**
  -historyManager: HistoryManager*
  -matcherManager: map<String,Matcher>
}
class Matcher {
  -charbuf: LinedCharbuf*
  -lineLoc: Loc[n]
  -pairLoc: Loc[n]
}
class Trie {
  +add(dfa: String, type: NodeType): void
  +getType(): NodeType
  +step(ch: Character): void
}
"CommandRunner<Movement>" <|-- MovementRunner 
MovementParser --|> "CommandParser<Movement>" 
"CommandParser<Movement>" "0..*" o-- "CommandRunner<Movement>"
"CommandRunner<Search>" <|-- SearchRunner
"CommandRunner<Movement>" <|-- SearchRunner
"CommandRunner<Movement>" <|-- SemiColonRepeater
MatcherRunner -|> "CommandRunner<Movement>"
Matcher -- "manages" MatcherRunner
Trie --o "1" Matcher
```
```plantuml
left to right direction
class MacroParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getMacro(): Macro
}
abstract Window{}
abstract "CommandParser<Macro>"{
  {abstract}-doReset(): void
  {abstract}-parse(key: Keystroke): Boolean
  +reset(): void
  +consume(key: Keystroke): void
}
abstract "CommandRunner<Macro>" {
  +{abstract}run(command: Command*): void
  +notify(source: CommandSource*): void
}
class MacroRunner {
  -registers: map<Character, KeyStroke[0..*]>
  -modeManager: ModeManger*
  +run(command: Macro*): void
}
abstract "CommandRunner<Command>"{}
abstract KeystrokeConsumer
class ParserGroup{ 
  +add(parser: BaseCommandParser*): void
}
class HistoryRecorder {
  -activeWindow: Window**
  -historyManager: HistoryManager*
}
class CursorRecorder{ }
"CommandRunner<Macro>" <|-- MacroRunner 
MacroParser --|> "CommandParser<Macro>" 
MacroRunner "1" o-- Window 
MacroRunner o-- RootStatus
ParserGroup -o MacroRunner 
BaseCommandParser --o "0..*" ParserGroup
"CommandRunner<Command>" <|- ParserGroup
"CommandParser<Macro>" "0..*" o-- "CommandRunner<Macro>"
ParserGroup --|> KeystrokeConsumer
MacroRunner "2" o- HistoryRecorder
CursorRecorder --o "1" HistoryRecorder
```
```plantuml 
left to right direction
abstract Window{}
struct Data{
  +contents: String
  +addNewline: Boolean
}
class Clipboard{
}
class RootStatus{
  -message: String
  -errorCode: Integer
}
abstract "CommandParser<Normal>"{
  {abstract}-doReset(): void
  {abstract}-parse(key: Keystroke): Boolean
  +reset(): void
  +consume(key: Keystroke): void
}
abstract "CommandRunner<Normal>" {
  +{abstract}run(command: Command*): void
  +notify(source: CommandSource*): void
}
class NormalParser {
  -doReset(): void
  +getNormal(): Normal
}
class NormalParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getNormal(): Normal
}
class NormalRunner {
  +run(command: Normal*): void
}
class HistoryManager {
  -map<String, HistoryTree> trees
}
class HistoryTree {
  +push(tab: Tab*): void
  +undo(): bool
  +redo(): bool
}
class RootStatus{
  -message: String
  -errorCode: Integer
}
class UndoRunner {
  +run(command: Normal*): void
}
"CommandRunner<Normal>" <|-- UndoRunner 
UndoRunner "1" o-- Window 
UndoRunner o-- RootStatus
HistoryManager -o UndoRunner 
"CommandParser<Normal>" "0..*" o-- "CommandRunner<Normal>"
HistoryTree "manages" <-- HistoryManager
Data --o "0..*" Clipboard 
"CommandRunner<Normal>" <|-- NormalRunner 
NormalParser --|> "CommandParser<Normal>" 
NormalRunner "1" o-- Window 
NormalRunner o-- RootStatus
NormalRunner o- Clipboard 
"CommandParser<Normal>" "0..*" o-- "CommandRunner<Normal>"
```
```plantuml
class MacroParser {
  -doReset(): void
  -parse(key: Keystroke): Boolean
  +getMacro(): Macro
}
class MacroRunner {
  -registers: map<Character, KeyStroke[0..*]>
  +run(command: Command*): void
}
class MovementRunner{}
ExRunner --|> CommandRunner
RootStatus "1"--o ExRunner
class ComboNMRunner{}
MovementRunner --|> CommandRunner
MovementRunner -o ComboNMRunner 
CommandRunner <|-- SetModeRunner
MacroParser --|> CommandParser 
MovementRunner "1" o-- Window
InsertParser -"resets" SetModeRunner 
SetModeRunner "resets" -- ReplaceParser
SetModeRunner "resets" -- ExParser
CommandParser <|-- InsertParser
CommandParser <|-- ExParser
CommandParser <|-- ReplaceParser
MacroRunner --|> CommandRunner
ModeManager --o MacroRunner 
ComboNMRunner --|> CommandRunner
class MovementParser {
  -doReset(): void
  +getMovement(): Movement
}
class SetModeRunner{}
```
```plantuml
left to right direction
abstract LinedFilebuf{}
class TabManager {
  +next(): void
  +curr(): Tab
  +prev(): void
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
  +fixCursor(): void 
  +fitToCursor(): void 
  +fitToTopline(): void 
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
class LinedCharbuf{
  +erase(line: Integer, start: Integer, len: Integer): void
  +insert(line: Integer, start: Integer, chars: String): void
  +eraseLines(line: Integer, len: Integer): void
  +insertLines(line: Integer, len: Integer): void
  +begin(): Iterator
  +end(): Iterator
}
LinedCharbuf <|- LinedFilebuf
abstract class LinedFilebuf{
  +{abstract} persist(): void
  +{abstract} getPermissions(): Permissions
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
  -doResize(): void
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
  -{abstract}doResize(): void
  +resize(h: Integer, w: Integer): void
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
abstract RenderableBox{}
RenderableBox --|> Resizeable 
Translateable <|- RenderableBox
RenderableBox -|> Renderable
Window <|-- NCWindow 
RenderableBox <|-- Window 
Resizeable <|-- Tab
```