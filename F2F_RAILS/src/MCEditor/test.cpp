#include <conio.h>
#include <windows.h>
#include <cstdio>
#include "memory"
#include "globals.h"
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "MCEditor.h"
#include "BlockEntity.h"
#include "MCACoder.h"
#include <math.h>
#include <dirent.h>
#include <iostream>
#include <map>

using namespace std;

int chunk_offsetx, chunk_offsetz;
extern string file_name_MCA;
extern int first_MCEDIT;
int region_xxx,region_zzz;
extern int remove_block_entities;
extern void reset_block();

extern int region_x_old,region_z_old;

int toggle_2=0;

void toggle3() {
    toggle_2=(toggle_2+1); if (toggle_2>=5000) toggle_2=0;;
    if (toggle_2==0) printf("/\b");
    else if (toggle_2==1250) {
        static int t=0;
        t++;
        if (t>100) { printf("o-\b"); t=0; }
        else { printf("-\b"); }
    }
    else if (toggle_2==2500) printf("\\\b");
    else if (toggle_2==3750) printf("|\b");
}


MCEditor editor;

char tmp[256];

BlockInfo*** AX;

int mceditor2()
{
//    MCEditor *editor;
//    MCRegion *region;
//    editor = new MCEditor();
//    region = new MCRegion(0, 0, 0, 512, 512, 256);

//    int region_x=0;
//    int region_z=0;
//
//    region_xxx=region_x;
//    region_zzz=region_z;
//
//
//    remove_block_entities=0;
//    first_MCEDIT=1;
//    reset_block();
//
//    sprintf(tmp, "/Saves/template/region/r.0.0.mca");
//    file_name_MCA=tmp;

//    editor.mca_coder.loadMCA(tmp);

//    first_MCEDIT=0;
//    region_x_old=0,region_z_old=0;
//
//    printf(" Loaded. Converting");
//
//    MCRegion region(0, 0, 0, 512, 512, 256);
//
////    editor.mca_coder.getBlock_FAST(region);
//
//    printf(". Ready.");
//
////    BlockInfo*** AX=region.A;
//    AX=region.A;
//
//
//    for (int x = 0; x < 512; x++) {
//        int xx=x+chunk_offsetx*16;
//        BlockInfo** AZ=AX[x];
//        toggle2();
//        for (int z = 0; z < 512; z++) {
//            int zz=z+chunk_offsetz*16;
//            BlockInfo* AY=AZ[z];
//            for (int y = 0; y < 256; y++) {
//            }
//        }
//    }
//
//    file_name_MCA=tmp;
//
//    printf(" Saving ");

//    first_MCEDIT=0;
//    region_x_old=0;
//    region_z_old=0;

//    editor.setRegion(region);

//    delete editor;
//    delete region;
    printf(". Ready.\n");
}


