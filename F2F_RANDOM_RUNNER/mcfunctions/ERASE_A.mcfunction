setblock ~0 ~2 ~0 air 0
fill ~0 ~2 ~0 ~0 ~2 ~0 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~0 ~2 ~0 16 16 16 0.1 5000
kill @e[type=Bat,r=8]
