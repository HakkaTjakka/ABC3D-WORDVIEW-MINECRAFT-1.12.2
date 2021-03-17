setblock ~2 ~-4 ~-5 air 0
fill ~2 ~-4 ~-5 ~2 ~-4 ~-5 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~2 ~-4 ~-5 16 16 16 0.1 5000
execute kill @e[type=Bat,distance=..9]
