setblock ~3 ~-4 ~-4 air 0
fill ~3 ~-4 ~-4 ~3 ~-4 ~-4 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~3 ~-4 ~-4 16 16 16 0.1 5000
/kill @e[type=Bat,distance=..9]
