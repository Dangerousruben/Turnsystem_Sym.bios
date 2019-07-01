# Turnsystem_Sym.bios
The code that was used to create the turn system in Sym.Bios

In the turn-based strategy Sym.Bios units will get their turn individually. The order is based on the "Initiative" value of each unit. The following code are excerpts of the turn system. This turn system uses a circular linked list to allow for adjustments the turn order several turns ahead of time
