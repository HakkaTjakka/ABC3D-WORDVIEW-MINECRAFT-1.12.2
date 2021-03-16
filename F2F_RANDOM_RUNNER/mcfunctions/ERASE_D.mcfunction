setblock ~0 ~-4 ~-5 air 0
fill ~0 ~-4 ~-5 ~0 ~-4 ~-5 repeating_command_block 0 keep {Command:"function abc:letter_ONE_REMOVE",auto:1b}
particle explode ~0 ~-4 ~-5 16 16 16 0.1 5000
