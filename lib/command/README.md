# About 
This folder contains concrete `CommandParsers`. 
Command Parsers are observers of `KeyStrokeSource`s
- when notified, they will move their current DFA node one step, 
based on subject's keystroke
- if this step reaches a valid terminal node, notifyAll attached `CommandRunner`s
- if this step isn't valid, go to an Invalid state 
and continue to self-loop until `reset()` is called

# Mode Management 
- Note that `CommandParser`s should be attached 
to exactly one `ModeManager` instance
- The `ModeManager` instance 
  - is a `CommandRunner`
  - has several `CommandParser` instances, corresponding to 
e.g. `NormalModeParser`, `VisualModeParser`, and basic parsers like `EscParser`
  - manages which mode is currently active
  - notify the relevant mode to activate based on the current mode
  - when `notify`d, will switch to the relevant Mode based on the Command

