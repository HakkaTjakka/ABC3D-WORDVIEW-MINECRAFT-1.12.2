setblock ~7 ~8 ~-7 air 0
fill ~7 ~8 ~-7 ~7 ~8 ~-7 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~7 ~8 ~-7 16 16 16 0.1 5000
kill @e[type=Bat,r=8]
