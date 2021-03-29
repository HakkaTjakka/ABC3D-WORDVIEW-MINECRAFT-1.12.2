#setblock ~ ~ ~ air 0
setblock ~ ~ ~ bedrock 0
setblock ~ ~6 ~ air 0
fill ~ ~6 ~ ~ ~6 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~-16 ~6 ~ ~-16 ~6 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}
fill ~16 ~6 ~ ~16 ~6 ~ repeating_command_block 0 keep {Command:"function abc:rails_e",auto:1b}

