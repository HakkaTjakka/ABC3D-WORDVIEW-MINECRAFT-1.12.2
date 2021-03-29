https://github.com/HakkaTjakka/ABC3D-WORDVIEW-MINECRAFT-1.12.2/tree/main/F2F_RAILS

operates on /saves/template/region
put region.init/*.mca into /saves/template/region
run ftf.exe -save for saving region back into /saves/template/region/r.0.0.mca
run ftf.exe -f2f for converting resources/abc_16x16.png into .mcfunction files
.mcfunction files end up into directory mcfunctions, batch file copies them into /saves/template/data/functions/abc and/or /saves/ABC/data/functions/abc

/function abc:start for starting maze.
and/or use r.19.19.mca and /tp 10000 ~ 10000 and/or type /function abc:start
eventually copy world from /saves/template to /%appdata/.minecraft/saves and/or /saves/ABC to /%appdata/.minecraft/saves
