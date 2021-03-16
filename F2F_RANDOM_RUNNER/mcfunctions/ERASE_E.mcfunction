setblock ~-1 ~-4 ~-4 air 0
fill ~-1 ~-4 ~-4 ~-1 ~-4 ~-4 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~-1 ~-4 ~-4 16 16 16 0.1 5000
