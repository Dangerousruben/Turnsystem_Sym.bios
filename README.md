# Turnsystem_Sym.bios
The code that was used to create the turn system in Sym.Bios
The engine used was Unreal Engine 4

In the turn-based strategy Sym.Bios units will get their turn individually. The order is based on the "Initiative" value of each unit. The following code are excerpts of the turn system. This turn system uses a circular linked list to allow for adjustments to the turn order several turns in the future.

This system is immensely scalable. There were a lot ideas for things like delaying turns of units, saving "action points" for next round and different kinds of debuffs. All of these ideas were very easily implementatble using the turn system however these ideas never made it in the game.

I made several functions "BlueprintImplementable" which meant that the functions will be defined in the Unreal scripting language "blueprinting". This way you can add a lot of functionality including sound effects without going into the C++ code.
