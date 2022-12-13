# Non-sandboxed filesystem

**Quick links:** [itch.io](https://yellowafterlife.itch.io/gamemaker-file-dropper)
**Versions:** GameMaker: Studio, GameMaker Studio 2  
**Platforms:** Windows, Windows (YYC)

This extension allows the user to drag-and-drop files and directories onto the game window.

Featuring a total of 1 (one) function:

**file_dropper_init()➜**  
Sets up the drag and drop operations for the game window.  
Should be called before you expect user to attempt dragging and dropping objects onto the window (usually on Game Start).  
Harmless if called more than once.  
Returns whether successful (I'm not aware of circumstances that could cause this function to fail).

---

After calling the said function, the game window will indicate to the system that it's happy to accept objects and the user will be able to drag and drop files from Explorer/etc. Doing so will dispatch one Async - System event per file, where

- `async_load[?"event_type"]` is `"file_drop"`
- `async_load[?"filename"]` is an absolute path to the file  
  Note that in GMS1.4, you'll need an extension to read files outside of game/save directory
  (e.g. [non-sandboxed filesystem](https://yellowafterlife.itch.io/gamemaker-nsfs))

## What's interesting here

A little bit of boilerplate for `RegisterDragDrop` + `IDropTarget`, neither of which is well-documented.

Apparently you can also do this using `DragAcceptFiles`,
but also [the extension that was using that approach](https://marketplace.yoyogames.com/assets/5265/windows-filedropper)
doesn't work anymore, so who knows, maybe I dodged a bullet here.

## Meta

**Author:** [YellowAfterlife](https://github.com/YellowAfterlife)  
**License:** MIT