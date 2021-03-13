#fill ~-32 ~ ~-16 ~-32 ~ ~-16 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~-32 ~ ~16 ~-32 ~ ~16 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~32 ~ ~-16 ~32 ~ ~-16 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~32 ~ ~16 ~32 ~ ~16 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~-16 ~ ~-32 ~-16 ~ ~-32 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~-16 ~ ~32 ~-16 ~ ~32 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~16 ~ ~-32 ~16 ~ ~-32 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}
#fill ~16 ~ ~32 ~16 ~ ~32 repeating_command_block 0 keep {Command:"/function abc:pattern3",auto:1b}

setblock ~64 ~ ~48 stone 0 keep
#setblock ~-32 ~ ~32 stone 0
#setblock ~32 ~ ~-32 stone 0
setblock ~-48 ~ ~-64 stone 0 keep
setblock ~16 ~48 ~16 stone 0 keep
setblock ~16 ~-32 ~ stone 0 keep
setblock ~16 ~32 ~-48 stone 0 keep
setblock ~16 ~16 ~-16 stone 0 keep
setblock ~16 ~16 ~-32 stone 0 keep
setblock ~48 ~-16 ~-32 stone 0 keep
setblock ~16 ~16 ~-48 stone 0 keep
setblock ~48 ~16 ~-16 stone 0 keep
setblock ~32 ~16 ~-16 stone 0 keep
setblock ~-64 ~64 ~32 stone 0 keep
setblock ~-64 ~48 ~32 stone 0 keep


#fill ~-32 ~ ~ ~-32 ~ ~ repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}
fill ~48 ~ ~16 ~48 ~ ~16 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}
fill ~-64 ~32 ~ ~-64 ~32 ~ repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}

fill ~-48 ~16 ~64 ~-48 ~16 ~64 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}

#fill ~16 ~ ~-48 ~16 ~ ~-48 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}
fill ~ ~32 ~48 ~ ~32 ~48 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}
#fill ~ ~ ~-64 ~ ~ ~-64 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}

#fill ~32 ~32 ~16 ~32 ~32 ~16 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}
#fill ~-16 ~16 ~-32 ~-16 ~16 ~-32 repeating_command_block 0 keep {Command:"/function abc:pattern4",auto:1b}

setblock ~ ~ ~ air 0
fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:"/function abc:letter_ONE_A"}
fill ~ ~ ~1 ~ ~ ~1 light_weighted_pressure_plate 0 keep
fill ~ ~ ~-1 ~ ~ ~-1 light_weighted_pressure_plate 0 keep
fill ~-1 ~ ~ ~-1 ~ ~ light_weighted_pressure_plate 0 keep
fill ~1 ~ ~ ~1 ~ ~ light_weighted_pressure_plate 0 keep
fill ~ ~1 ~ ~ ~1 ~ light_weighted_pressure_plate 0 keep



#setblock ~ ~ ~ air 0

