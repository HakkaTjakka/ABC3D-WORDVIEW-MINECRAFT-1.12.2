#setblock ~ ~ ~ air 0

fill ~-2 ~-1 ~-2 ~2 ~ ~2 bedrock 0
fill ~-1 ~ ~-1 ~1 ~ ~1 air 0

fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:"/function abc:pattern2"}

fill ~ ~ ~1 ~ ~ ~1 light_weighted_pressure_plate 0 keep
fill ~ ~ ~-1 ~ ~ ~-1 light_weighted_pressure_plate 0 keep
fill ~-1 ~ ~ ~-1 ~ ~ light_weighted_pressure_plate 0 keep
fill ~1 ~ ~ ~1 ~ ~ light_weighted_pressure_plate 0 keep
fill ~ ~1 ~ ~ ~1 ~ light_weighted_pressure_plate 0 keep

summon minecraft:rabbit ~-2 ~ ~-2
#summon minecraft:rabbit ~-2 ~ ~2
summon minecraft:rabbit ~2 ~ ~2
#summon minecraft:rabbit ~2 ~ ~-2
summon minecraft:wolf ~ ~2 ~

#setblock ~ ~ ~ air 0

