
//#include "memory"
#include "MCEditor/globals.h"
//#include <cstdio>
//#include <vector>
#include <string>
//#include <cstdlib>
//#include <algorithm>
#include "MCEditor/MCEditor.h"
#include "MCEditor/BlockEntity.h"
#include "MCEditor/MCACoder.h"

#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

#define GLOWSTONE 89
#define GLASS 20
#define STAINED_GLASS 95
#define BEDROCK 7
#define GOLDEN_RAIL 27
#define RAIL 66
#define CONCRETE 251
#define REDSTONE_BLOCK 152
#define COMMAND_BLOCK 137
#define LIGHT_WEIGHTED_PRESSURE_PLATE 147

void font2function_sub(int chain);
void button(FILE* mcfunction, int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, int l, bool blockit );
void button_B( int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, bool blockit );

bool do_random=true;
bool do_makeit=true;
bool do_bats=false;
//bool do_random=false;
void mceditor(MCRegion& region, bool load_only);
void region2function(bool load_only);

using namespace std;

int chunk_offsetx, chunk_offsetz;
extern string file_name_MCA;
extern int first_MCEDIT;
int region_xxx,region_zzz;
extern int remove_block_entities;
extern void reset_block();

extern int region_x_old,region_z_old;

int main(int argc, char ** argv) {
    srand(time(0));
    bool load_only=true;
    for (int n=0; n<argc; n++) {
        printf("%s ",argv[n]);
        if (n>0) {
            if (strcmp(argv[n],"-save")==0) load_only=false;
            if (strcmp(argv[n],"-f2f")==0) {
                font2function_sub(3);
            }
        }
    }
    printf("\n");

//    font2function_sub(0);
//    font2function_sub(1);
//    font2function_sub(2);
//    font2function_sub(3);
    region2function(load_only);
}   //

int toggle_2=0;

void toggle2() {
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

void region2function_sub(MCRegion& region);

void region2function(bool load_only) {
    MCRegion region(0, 0, 0, 512, 512, 256);

//    mceditor(region,true);          //do NOT save region file after creating rotated chunks (quicker)
//    mceditor(region,false);         //save after creating rotated chunks
    mceditor(region, load_only);
    printf("converted -> functions\n");
    region2function_sub(region);
    printf(" ready\n");
}

void mceditor(MCRegion& region, bool load_only)
{
    MCEditor *editor;
//    MCRegion *region;
    editor = new MCEditor();
//    region = new MCRegion(0, 0, 0, 512, 512, 256);


    char tmp[256];

    int region_x=0;
    int region_z=0;

    region_xxx=region_x;
    region_zzz=region_z;


    remove_block_entities=0;
    first_MCEDIT=1;
    reset_block();

    sprintf(tmp, "/Saves/template/region/r.0.0.mca");
    file_name_MCA=tmp;

    editor->mca_coder.loadMCA(tmp);

    first_MCEDIT=0;
    region_x_old=0,region_z_old=0;

    printf(" Loaded. Converting");

//    MCRegion region(0, 0, 0, 512, 512, 256);

    editor->mca_coder.getBlock_FAST(region);

    printf(". Ready.");

    BlockInfo*** AX=region.A;
//    AX=region.A;


    if (0) {
        for (int x = 0; x < 16; x++) {
            BlockInfo** AZ=AX[x];
            toggle2();
            for (int z = 0; z < 16; z++) {
                BlockInfo* AY=AZ[z];
                for (int y = 17; y >=1; y--) {

    //                if (AY[y].id==27) {
    //                    AX[x][z][y-1]=BlockInfo(152,0,0,0);
    //                }

                    AX[x][z+64][y]=AX[x][z+48][y];
    //                AY[y]=AX[x+1][z][y];
//                    if (y>1) AY[y]=AY[y-1];
                }
//                AY[0]=BlockInfo(BEDROCK,0,0,0);
            }
        }
    } else {
        for (int p=0; p<3; p++) {
            for (int x = 0; x < 16; x++) {
                BlockInfo** AZ=AX[x];
                toggle2();
                for (int z = 0; z < 16; z++) {
                    BlockInfo* AY=AZ[z];
                    for (int y = 1; y <= 19; y++) {
                        BlockInfo* A=&AX[x+p*16][z][y];
                        BlockInfo* AN=&AX[15-z+16+p*16][x][y];

                        *AN=*A;
                        if (AN->id==GOLDEN_RAIL) {
                            if ((AN->data&0x7)==0) AN->data=1 | (AN->data & 0x8);
                            else if (((AN->data&0x7))==1) AN->data=0 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==2) AN->data=5 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==3) AN->data=4 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==4) AN->data=2 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==5) AN->data=3 | (AN->data & 0x8);
                        }

                        A=&AX[x+p*16][z+32][y];
                        AN=&AX[15-z+16+p*16][x+32][y];

                        *AN=*A;
                        if (AN->id==GOLDEN_RAIL) {
                            if ((AN->data&0x7)==0) AN->data=1 | (AN->data & 0x8);
                            else if (((AN->data&0x7))==1) AN->data=0 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==2) AN->data=5 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==3) AN->data=4 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==4) AN->data=2 | (AN->data & 0x8);
                            else if ((AN->data&0x7)==5) AN->data=3 | (AN->data & 0x8);
                        } else if (AN->id==RAIL) {
                            if (AN->data==0) AN->data=1;
                            else if ((AN->data)==1) AN->data=0;
                            else if (AN->data==2) AN->data=5;
                            else if (AN->data==3) AN->data=4;
                            else if (AN->data==4) AN->data=2;
                            else if (AN->data==5) AN->data=3;
                            else if (AN->data==6) AN->data=7;
                            else if (AN->data==7) AN->data=8;
                            else if (AN->data==8) AN->data=9;
                            else if (AN->data==9) AN->data=6;

                        }

    /*
    rail:
    0	Straight rail connecting to the north and south.
    1	Straight rail connecting to the east and west.
    2	Sloped rail ascending to the east.
    3	Sloped rail ascending to the west.
    4	Sloped rail ascending to the north.
    5	Sloped rail ascending to the south.
    6	Curved rail connecting to the south and east.
    7	Curved rail connecting to the south and west.
    8	Curved rail connecting to the north and west.
    9	Curved rail connecting to the north and east.

    golden_rail:
    0: flat track going north-south
    1: flat track going east-west
    2: sloped track ascending to the east
    3: sloped track ascending to the west
    4: sloped track ascending to the north
    5: sloped track ascending to the south

    0x8	Set if rail is active.
    */
                        if (p==0) {
                            A=&AX[x][z+16][y];
                            AN=&AX[z+16][x+16][y];
                            *AN=*A;
                            if (AN->id==27) {
                                if ((AN->data&0x7)==0) AN->data=1 | (AN->data & 0x8);
                                else if ((AN->data&0x7)==1) AN->data=0 | (AN->data & 0x8);
                            }
                        }
                    }
                }
            }
        }
    }

/*

*/

    if (!load_only) {
        file_name_MCA=tmp;

        printf(" Saving: ");

        first_MCEDIT=0;
        region_x_old=0;
        region_z_old=0;

        editor->setRegion(region);
    }

    delete editor;
//    delete region;
    printf("Ready.\n");
}

void region2function_sub(MCRegion& region) {
    mkdir("mcfunctions");
    int offset_x=0;
    int offset_y=0;
    int offset_z=0;

    std::string substring;


    FILE* mcfunction;
    char fname[100];
    int o=-8;
    int n_o=7;
    int z=o-1;
    int n_z=n_o+1;
    int k=z;
    int n_k=n_z;

    substring="RAILS";
    offset_x=0;
    offset_y=0;
    offset_z=0;
//    offset_x=0+o;
//    offset_y=0+o;
//    offset_z=0+o;

    for (int l=1; l<=24; l++) {
        sprintf(fname,"mcfunctions/%s_%c.mcfunction",substring.c_str(),64+l);
        mcfunction=fopen(fname,"w");

        printf("%c",64+l);

        if (l<=12) {
//            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
//                     offset_x +   o,                    offset_y + o,                   offset_z + o,
//                     offset_x + n_o,                    offset_y + n_o,                 offset_z + n_o);
            fprintf(mcfunction, "setblock ~ ~ ~ air 0 replace repeating_command_block 0\n");
          } else {
            fprintf(mcfunction, "setblock ~ ~ ~ air 0 replace repeating_command_block 0\n");
        }

        std::string all="";
        char p[1000]="";
        char block[100];
        BlockInfo*** AX=region.A;
        int x;
        int y;
        int z;

        for (int c_z=0; c_z<16; c_z++) {
            for (int c_x=0; c_x<16; c_x++) {
                for (int c_y=0; c_y<19; c_y++) {
                    if (l<=4) {
                        x=c_x + 16 * (l-1);
                        y=c_y + 1;
                        z=c_z;
                    } else if (l<=6) {
                        x=c_x + 16 * (l-1-4);
                        y=c_y + 1;
                        z=c_z + 16;
                    } else if (l<=10) {
                        x=c_x + 16 * (l-1-6);
                        y=c_y + 1;
                        z=c_z + 32;
                    } else if (l<=11) {
                        x=c_x + 16 * (l-1-10);
                        y=c_y + 1;
                        z=c_z + 48;
                    } else if (l<=12) {
                        x=c_x + 16 * (l-1-11);
                        y=c_y + 1;
                        z=c_z + 64;

                    } else if (l<=4+12) {
                        x=c_x + 16 * (l-1-12);
                        y=c_y + 1;
                        z=c_z;
                    } else if (l<=6+12) {
                        x=c_x + 16 * (l-1-4-12);
                        y=c_y + 1;
                        z=c_z + 16;
                    } else if (l<=10+12) {
                        x=c_x + 16 * (l-1-6-12);
                        y=c_y + 1;
                        z=c_z + 32;
                    } else if (l<=11+12) {
                        x=c_x + 16 * (l-1-10-12);
                        y=c_y + 1;
                        z=c_z + 48;
                    } else if (l<=12+12) {
                        x=c_x + 16 * (l-1-11-12);
                        y=c_y + 1;
                        z=c_z + 64;
                    }

                    BlockInfo* A=&AX[x][z][y];
                    if (A->id==CONCRETE)                            sprintf(block,"concrete %d", A->data);
                    else if (A->id==GLOWSTONE)                      sprintf(block,"glowstone 0");
                    else if (A->id==STAINED_GLASS)                  sprintf(block,"stained_glass %d", A->data);
                    else if (A->id==GLASS)                          sprintf(block,"glass %d", 0);
                    else if (A->id==GOLDEN_RAIL)                    sprintf(block,"golden_rail %d", A->data);
                    else if (A->id==REDSTONE_BLOCK)                 sprintf(block,"redstone_block 0");
                    else if (A->id==RAIL)                           sprintf(block,"rail %d",A->data);
                    else if (A->id==COMMAND_BLOCK)                  sprintf(block,"command_block 0");
                    else if (A->id==LIGHT_WEIGHTED_PRESSURE_PLATE)  sprintf(block,"light_weighted_pressure_plate 0");
                    else continue;
                    if (l<=12) {
                        sprintf(p, "setblock ~%d ~%d ~%d %s keep\n",
                            offset_x + c_x+o,   offset_y + c_y+o,   offset_z + c_z+o ,  block);
                    } else {
                        sprintf(p, "setblock ~%d ~%d ~%d %s keep\n",
                            offset_x + c_x+o,   offset_y + c_y,     offset_z + c_z+o ,  block);
                    }
                    all+= std::string()+p;
                }
            }
        }
        if (l>12) {
            int c_yyy=0;
            if (l==24) {
                c_yyy=0;
            }
            for (int c_z=-3+c_yyy; c_z<16+3-c_yyy; c_z++) {
                for (int c_x=-3+c_yyy; c_x<16+3-c_yyy; c_x++) {
                    for (int c_y=0; c_y<19; c_y++) {
                        int c_xxx,c_zzz;

//                        int c_max=c_x;
//                        if (c_z>c_max) c_max=c_z;
//                        int c_min=c_x;
//                        if (c_z<c_min) c_min=c_z;

                        if (c_z<0 && c_x<0) {
                            c_xxx=0;
                            c_zzz=0;
                        } else if (c_z>=16 && c_x>=16) {
                            c_xxx=15;
                            c_zzz=15;
                        } else if (c_z<0 && c_x>=16) {
                            c_xxx=15;
                            c_zzz=0;
                        } else if (c_z>=16 && c_x<0) {
                            c_xxx=0;
                            c_zzz=15;
                        } else if (c_z>=16) {
                            c_xxx=c_x;
                            c_zzz=15;
                        } else if (c_z<0) {
                            c_xxx=c_x;
                            c_zzz=0;
                        } else if (c_x>=16) {
                            c_xxx=15;
                            c_zzz=c_z;
                        } else if (c_x<0) {
                            c_xxx=0;
                            c_zzz=c_z;
                        } else {
                            continue;
                        }
                        if (l<=4+12) {
                            x=c_xxx + 16 * (l-1-12);
                            y=c_y + 1;
                            z=c_zzz;
                        } else if (l<=6+12) {
                            x=c_xxx + 16 * (l-1-4-12);
                            y=c_y + 1;
                            z=c_zzz + 16;
                        } else if (l<=10+12) {
                            if (l==12+10 && (c_x<  0  || ((c_z<0 || c_z>=16) && c_x>=16))) continue;
                            if (l==12+ 8 && (c_x>=16  || ((c_z<0 || c_z>=16) && c_x<  0))) continue;
                            if (l==12+ 7 && (c_z<  0  || ((c_x<0 || c_x>=16) && c_z>=16))) continue;
                            if (l==12+ 9 && (c_z>=16  || ((c_x<0 || c_x>=16) && c_z<  0))) continue;
                            x=c_xxx + 16 * (l-1-6-12  );
                            y=c_y + 1;
                            z=c_zzz + 32;
                        } else if (l<=11+12) {
                            x=c_xxx + 16 * (l-1-10-12);
                            y=c_y + 1;
                            z=c_zzz + 48;
                        } else if (l<=12+12) {
                            x=c_xxx + 16 * (l-1-11-12);
                            y=c_y + 1;
                            z=c_zzz + 64;
                        }

                        BlockInfo* A=&AX[x][z][y];
                        if (A->id==CONCRETE)                            sprintf(block,"concrete %d", A->data);
                        else if (A->id==GLOWSTONE)                      sprintf(block,"glowstone 0");
                        else if (A->id==STAINED_GLASS)                  sprintf(block,"stained_glass %d", A->data);
                        else if (A->id==GLASS)                          sprintf(block,"glass %d", 0);
                        else if (A->id==GOLDEN_RAIL)                    sprintf(block,"golden_rail %d", A->data);
                        else if (A->id==REDSTONE_BLOCK)                 sprintf(block,"redstone_block 0");
                        else if (A->id==RAIL)                           sprintf(block,"rail %d",A->data);
                        else if (A->id==COMMAND_BLOCK)                  sprintf(block,"command_block 0");
                        else if (A->id==LIGHT_WEIGHTED_PRESSURE_PLATE)  sprintf(block,"light_weighted_pressure_plate 0");
                        else continue;
                        if ( !(l<=6+12) && (l<=10+12) ) {
                            sprintf(p, "setblock ~%d ~%d ~%d %s\n",
                                offset_x + c_x+o,   offset_y + c_y + c_yyy,     offset_z + c_z+o ,  block); all+= std::string()+p;
                        } else {
                            sprintf(p, "setblock ~%d ~%d ~%d %s keep\n",
                                offset_x + c_x+o,   offset_y + c_y + c_yyy,     offset_z + c_z+o ,  block); all+= std::string()+p;
                        }
                    }
                }
            }
        }
//        for (int xx=-2; xx<3; xx++)
//            for (int zz=-2; zz<3; zz++)
//                if (xx!=0 || zz!=0) {
//                    sprintf(p, "setblock ~%d ~%d ~%d %s glowstone 0 replace repeating_command_block 0\n",
//                        offset_x + xx*16,   offset_y -4, offset_z + zz*16 ); all+= std::string()+p;
//                    sprintf(p, "setblock ~%d ~%d ~%d glowstone 0 replace repeating_command_block 0\n",
//                        offset_x + xx*16,   249, offset_z + zz*16 ); all+= std::string()+p;
//                    sprintf(p, "setblock ~%d ~%d ~%d glowstone 0 replace repeating_command_block 0\n",
//                        offset_x ,   249, offset_z  ); all+= std::string()+p;
//                        sprintf(p, "setblock ~%d ~%d ~%d concrete 15\n",
//                            offset_x + xx*16,   offset_y -4, offset_z + zz*16 ); all+= std::string()+p;

//                }

        fprintf(mcfunction,all.c_str());

        int ll;
        ll=l;
        if (ll>12) ll-=12;
        if (!(ll<5)) {
            if (l<=12) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 1\n",
                        offset_x,offset_y,offset_z,offset_x-1,offset_y,offset_z-1);
            }
        }

/*
        int off_x=0;
        int off_z=0;
        if (l==1) off_x=-1;
        if (l==2) off_x=-1;
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d glowstone 0\n",offset_x+off_x,offset_y,offset_z+off_x);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 1\n",
                offset_x+off_x,offset_y,offset_z+off_x,offset_x+off_x-1,offset_y,offset_z+off_x-1);
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d glowstone 0\n",off_x,0,off_x);
*/

//        int next_letter=l+1; if (next_letter>12) next_letter=1;

/*
        int off_x=0;
        int off_z=0;
        if (l==1) off_x=-1;
        if (l==2) off_z=-1;
        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x+off_x,offset_y,offset_z+off_z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:next_%s_%c\",auto:1b}\n",
                offset_x+off_x,offset_y,offset_z+off_z,offset_x+off_x,offset_y,offset_z+off_z,substring.c_str(),next_letter+64);
*/
        fclose(mcfunction);

/*
        sprintf(fname,"mcfunctions/current_%s_%c.mcfunction",substring.c_str(),l+64);
        mcfunction=fopen(fname,"w");
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d glowstone 0\n",-offset_x,-offset_y,-offset_z);

//hoppa

        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",-offset_x,-offset_y,-offset_z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:%s_%c\",auto:1b}\n",
                -offset_x,-offset_y,-offset_z,-offset_x,-offset_y,-offset_z,substring.c_str(),l+64);

        fclose(mcfunction);
*/

/*
        sprintf(fname,"mcfunctions/next_%s_%c.mcfunction",substring.c_str(),next_letter+64);
        mcfunction=fopen(fname,"w");
*/

/*
        fprintf(mcfunction,"setblock ~ ~ ~ air 0\n");
        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"/function abc:current_%s_%c\"}\n",substring.c_str(),l+64);
//        fprintf(mcfunction,"fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 replace %s\n",block_outer);
//        fprintf(mcfunction,"fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 keep\n");
        fprintf(mcfunction,"fill ~-1 ~ ~ ~-1 ~ ~ air 0 replace redstone_block 0\n");
*/


/*
        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                -offset_x,-offset_y,-offset_z);
  //      fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0 replace redstone_block 0\n",
//                -offset_x,-offset_y+1,-offset_z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:%s_%c\"}\n",
                -offset_x,-offset_y,-offset_z,
                -offset_x,-offset_y,-offset_z,substring.c_str(),next_letter+64);

        fclose(mcfunction);
*/
    }

//    printf("\n");

}

void font2function_sub(int chain) {
    sf::Image fontimage;
    fontimage.loadFromFile("resources/abc_16x16.png");
    printf("Size x=%d, y=%d\n",fontimage.getSize().x,fontimage.getSize().y);
    mkdir("mcfunctions");
    int offset_x=0;
    int offset_y=0;
    int offset_z=0;

    char block_outline[100]="concrete 13";
    char block_inner[100]="concrete 0";
//    char block_inner[100]="stained_glass 4";
    char block_outer[100]="glowstone 0";
//    char block_outer[100]="concrete 15";
    char block_back[100]="concrete 14";
    char block_fill[100]="stained_glass 5"; //lime green
//    char block_fill[100]="stained_glass 14"; //lime green
//    char block_fill[100]="glowstone 0"; //lime green


    char remove_inner[100]="air 0";
    char remove_outer[100]="air 0";
    char remove_back[100]="air 0";
    char remove_outline[100]="air 0";
//    char remove_inner[100]="stained_glass 0";
//    char remove_outer[100]="stained_glass 14";
//    char remove_back[100]="stained_glass 4";
//    char remove_outline[100]="stained_glass 6";

    std::string substring;

    if (chain==0) {
        substring="XDIR";
    } else if (chain==1) {
        substring="YDIR";
    } else if (chain==2) {
        substring="ZDIR";
    } else if (chain==3) {
        substring="ONE";
        offset_x=0;
        offset_y=5;
        offset_z=0;
    }
    int offset_inner=0;
    int offset_outer=-1;
    int offset_back=0;
    FILE* mcfunction;
    char fname[100];
    int o=-8;
    int n_o=7;
    int z=o-1;
    int n_z=n_o+1;
    int k=z;
    int n_k=n_z;
    for (int l=1; l<=26; l++) {
        sprintf(fname,"mcfunctions/letter_%s_%c.mcfunction",substring.c_str(),64+l);
        mcfunction=fopen(fname,"w");

        printf("%c",64+l);


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z + n_z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z + n_z,                 block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z +   z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z +   z,                 block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z,                    offset_y + k,                   offset_z +   k,
                 offset_x +   z,                    offset_y + n_k,                 offset_z +   n_k,               block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z,                    offset_y + k,                   offset_z +   k,
                 offset_x + n_z,                    offset_y + n_k,                 offset_z + n_k,                 block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + n_z,                 offset_z +   k,
                 offset_x + n_k,                    offset_y + n_z,                 offset_z + n_k,                 block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + z,                   offset_z + k,
                 offset_x + n_k,                    offset_y + z,                   offset_z + n_k,                 block_outline);   //Y-



        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                   offset_z + n_z,
                 offset_x + n_o,                    offset_y + n_o,                 offset_z + n_z,                 block_back,block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                   offset_z +   z,
                 offset_x + n_o,                    offset_y + n_o,                 offset_z +   z,                 block_back,block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z,                    offset_y + o,                   offset_z +   o,
                 offset_x +   z,                    offset_y + n_o,                 offset_z +   n_o,               block_back,block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z,                    offset_y + o,                   offset_z +   o,
                 offset_x + n_z,                    offset_y + n_o,                 offset_z + n_o,                 block_back,block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z,                 offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z,                 offset_z + n_o,                 block_back,block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z,                   offset_z + o,
                 offset_x + n_o,                    offset_y + z,                   offset_z + n_o,                 block_back,block_outline);   //Y-



        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_outline,block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_outline,block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_outline,block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_outline,block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_outline,block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_outline,block_fill);   //Y-


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_inner,block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_inner,block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_inner,block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_inner,block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_inner,block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_inner,block_fill);   //Y-




        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    remove_inner,block_inner);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    remove_inner,block_inner);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  remove_inner,block_inner);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    remove_inner,block_inner);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    remove_inner,block_inner);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    remove_inner,block_inner);   //Y-


        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_outer,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_outer,                    remove_outer,block_outer);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_outer,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_outer,                    remove_outer,block_outer);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_outer,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_outer,    offset_y + n_o,                  offset_z +   n_o,                                  remove_outer,block_outer);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_outer,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_outer,    offset_y + n_o,                  offset_z + n_o,                                    remove_outer,block_outer);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_outer,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_outer,  offset_z + n_o,                                    remove_outer,block_outer);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_outer,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_outer,    offset_z + n_o,                                    remove_outer,block_outer);   //Y-






        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_back,                     remove_back,block_back);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_back,                     remove_back,block_back);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_back,     offset_y + n_o,                  offset_z +   n_o,                                  remove_back,block_back);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_back,     offset_y + n_o,                  offset_z + n_o,                                    remove_back,block_back);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_back,   offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_back,   offset_z + n_o,                                    remove_back,block_back);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_back,     offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_back,     offset_z + n_o,                                    remove_back,block_back);   //Y-







        std::string all_back="";
        std::string all_outer="";
        std::string all_inner="";
        std::string all_fill="";
        char p[1000]="";
        for (int c_y=-8; c_y<8; c_y++) {
            for (int c_x=-8; c_x<8; c_x++) {
                sf::Color pixel=fontimage.getPixel(32*16+l*16+8+c_x,8+c_y);

                int x=c_x;
                int y=-c_y-1;

                int n_x=-c_x-1;
                int n_y=c_y;

                if (pixel.a==0) {
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_back,    block_back);  all_back+= std::string()+p;  //front
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_back,    block_back);  all_back+= std::string()+p;  //back
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_back,     offset_y + y,                    offset_z +   x,                   block_back);  all_back+= std::string()+p;  //left
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_back,     offset_y + y,                    offset_z + n_x,                   block_back);  all_back+= std::string()+p;  //right
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_back,   offset_z + n_y,                   block_back);  all_back+= std::string()+p;  //bottom
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_back,     offset_z + n_y,                   block_back);  all_back+= std::string()+p;  //top

                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_back,    block_back,block_fill);  all_fill+= std::string()+p;  //front
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_back,    block_back,block_fill);  all_fill+= std::string()+p;  //back
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_back,     offset_y + y,                    offset_z +   x,                   block_back,block_fill);  all_fill+= std::string()+p;  //left
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_back,     offset_y + y,                    offset_z + n_x,                   block_back,block_fill);  all_fill+= std::string()+p;  //right
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_back,   offset_z + n_y,                   block_back,block_fill);  all_fill+= std::string()+p;  //bottom
                    sprintf(p, "setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_back,     offset_z + n_y,                   block_back,block_fill);  all_fill+= std::string()+p;  //top
                } else if (pixel.r==0) {
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_outer,   block_outer);  all_outer+=std::string()+p;  //front
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_outer,   block_outer);  all_outer+=std::string()+p;   //back
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   z  - offset_outer,    offset_y + y,                    offset_z +   x,                   block_outer);  all_outer+=std::string()+p;   //left
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_z  + offset_outer,    offset_y + y,                    offset_z + n_x,                   block_outer);  all_outer+=std::string()+p;   //right
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x +   x,                    offset_y + n_z  + offset_outer,  offset_z + n_y,                   block_outer);  all_outer+=std::string()+p;   //bottom
                    sprintf(p,"setblock ~%d ~%d ~%d %s\n", offset_x + n_x,                    offset_y + z  - offset_outer,    offset_z + n_y,                   block_outer);  all_outer+=std::string()+p;   //top

                } else {
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + y,                    offset_z + n_z  + offset_inner,   block_inner);  all_inner+=std::string()+p;   //Z+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + y,                    offset_z +   z  - offset_inner,   block_inner);  all_inner+=std::string()+p;   //Z-
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   z  - offset_inner,    offset_y + y,                    offset_z +   x,                   block_inner);  all_inner+=std::string()+p;   //X-
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_z  + offset_inner,    offset_y + y,                    offset_z + n_x,                   block_inner);  all_inner+=std::string()+p;   //X+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x +   x,                    offset_y + n_z  + offset_inner,  offset_z + n_y,                   block_inner);  all_inner+=std::string()+p;   //Y+
                    sprintf(p,"setblock ~%d ~%d ~%d %s keep\n", offset_x + n_x,                    offset_y + z  - offset_inner,    offset_z + n_y,                   block_inner);  all_inner+=std::string()+p;   //Y-
                }
            }
        }

        fprintf(mcfunction,all_back.c_str());
        fprintf(mcfunction,all_inner.c_str());
        fprintf(mcfunction,all_outer.c_str());

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z + n_z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z + n_z,                 block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + k,                   offset_z +   z,
                 offset_x + n_k,                    offset_y + n_k,                 offset_z +   z,                 block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z,                    offset_y + k,                   offset_z +   k,
                 offset_x +   z,                    offset_y + n_k,                 offset_z +   n_k,               block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z,                    offset_y + k,                   offset_z +   k,
                 offset_x + n_z,                    offset_y + n_k,                 offset_z + n_k,                 block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + n_z,                 offset_z +   k,
                 offset_x + n_k,                    offset_y + n_z,                 offset_z + n_k,                 block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   k,                    offset_y + z,                   offset_z + k,
                 offset_x + n_k,                    offset_y + z,                   offset_z + n_k,                 block_outline);   //Y-

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_back,                     remove_outline,block_outline);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_back,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_back,                     remove_outline,block_outline);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   z  - offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_back,     offset_y + n_o,                  offset_z +   n_o,                                  remove_outline,block_outline);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x + n_z  + offset_back,     offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_back,     offset_y + n_o,                  offset_z + n_o,                                    remove_outline,block_outline);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + n_z  + offset_back,   offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_back,   offset_z + n_o,                                    remove_outline,block_outline);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s replace %s\n",
                 offset_x +   o,                    offset_y + z  - offset_back,     offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_back,     offset_z + n_o,                                    remove_outline,block_outline);   //Y-

//        fprintf(mcfunction,all_fill.c_str());

        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + o,                    offset_z + n_z  + offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z + n_z  + offset_inner,                    block_fill);   //Z+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + o,                    offset_z +   z  - offset_inner,
                 offset_x + n_o,                    offset_y + n_o,                  offset_z +   z  - offset_inner,                    block_fill);   //Z-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   z  - offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x +   z  - offset_inner,    offset_y + n_o,                  offset_z +   n_o,                                  block_fill);   //X-
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x + n_z  + offset_inner,    offset_y + o,                    offset_z +   o,
                 offset_x + n_z  + offset_inner,    offset_y + n_o,                  offset_z + n_o,                                    block_fill);   //X+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + n_z  + offset_inner,  offset_z +   o,
                 offset_x + n_o,                    offset_y + n_z  + offset_inner,  offset_z + n_o,                                    block_fill);   //Y+
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",
                 offset_x +   o,                    offset_y + z  - offset_inner,    offset_z + o,
                 offset_x + n_o,                    offset_y + z  - offset_inner,    offset_z + n_o,                                    block_fill);   //Y-

        fprintf(mcfunction,all_fill.c_str());

        int next_letter=l+1; if (next_letter>26) next_letter=1;



/*
        if (chain==3) {
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x-16,offset_y,offset_z,offset_x-16,offset_y,offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x-16-1,offset_y,offset_z-1,offset_x-16+1,offset_y,offset_z+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x-16,offset_y+1,offset_z);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x+16,offset_y,offset_z,offset_x+16,offset_y,offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x+16-1,offset_y,offset_z-1,offset_x+16+1,offset_y,offset_z+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x+16,offset_y+1,offset_z);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x,offset_y,offset_z-16,offset_x,offset_y,offset_z-16);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x-1,offset_y,offset_z-16-1,offset_x+1,offset_y,offset_z-16+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x,offset_y+1,offset_z-16);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x,offset_y,offset_z+16,offset_x,offset_y,offset_z+16);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x-1,offset_y,offset_z+16-1,offset_x+1,offset_y,offset_z+16+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x,offset_y+1,offset_z+16);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x,offset_y-16,offset_z,offset_x,offset_y-16,offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x-1,offset_y-16,offset_z-1,offset_x+1,offset_y-16,offset_z+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x,offset_y-16+1,offset_z);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:current_ONE_A\"}\n",offset_x,offset_y+16,offset_z,offset_x,offset_y+16,offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d %s keep\n",offset_x-1,offset_y+16,offset_z-1,offset_x+1,offset_y+16,offset_z+1,block_outer);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x,offset_y+16+1,offset_z);

        }
*/

        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x,offset_y,offset_z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:next_%s_%c\",auto:1b}\n",offset_x,offset_y,offset_z,offset_x,offset_y,offset_z,substring.c_str(),next_letter+64);

//funny
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x,offset_y+1,offset_z);
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n",offset_x,offset_y+1,offset_z);

        fclose(mcfunction);

//next

        if (chain==3) {
            sprintf(fname,"mcfunctions/current_%s_%c.mcfunction",substring.c_str(),l+64);
            mcfunction=fopen(fname,"w");
//            fprintf(mcfunction,"setblock ~ ~1 ~ air 0\n");
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",-offset_x,-offset_y,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:letter_%s_%c\",auto:1b}\n",-offset_x,-offset_y,-offset_z,-offset_x,-offset_y,-offset_z,substring.c_str(),l+64);
//            fprintf(mcfunction,"setblock ~%d ~%d ~%d redstone_block 0\n",-offset_x,-offset_y+1,-offset_z);
            fclose(mcfunction);
        }


        sprintf(fname,"mcfunctions/next_%s_%c.mcfunction",substring.c_str(),next_letter+64);
        mcfunction=fopen(fname,"w");
        fprintf(mcfunction,"setblock ~ ~ ~ air 0\n");

        if (chain==3) {
            fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"/function abc:current_%s_%c\"}\n",substring.c_str(),l+64);
            fprintf(mcfunction,"fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 replace %s\n",block_outer);
            fprintf(mcfunction,"fill ~-1 ~ ~-1 ~1 ~ ~1 glowstone 0 keep\n");
            fprintf(mcfunction,"fill ~-1 ~ ~ ~-1 ~ ~ glowstone 0 replace redstone_block 0\n");
//funny
//            fprintf(mcfunction,"setblock ~ ~1 ~ light_weighted_pressure_plate 0 keep\n");

            if (do_random) {
                if (do_makeit) {
                    button(mcfunction,      -6,     -4,      -6 , "DOWN",             0,-1, 0, l, true);
                    button(mcfunction,      -5,     -4,      -5 , "UP",               0, 1, 0, l, true);
                    button(mcfunction,      -4,     -4,      -6 , "NORTH",            0, 0,-1, l, true);
                    button(mcfunction,      -3,     -4,      -5 , "SOUTH",            0, 0, 1, l, true);
                    button(mcfunction,      -2,     -4,      -6 , "EAST",             1, 0, 0, l, true);
                    button(mcfunction,      -1,     -4,      -5 , "WEST",            -1, 0, 0, l, true);

                    button(mcfunction,       1,     -4,      -6 , "DOWN_B",           0,-3, 0, l, true);
                    button(mcfunction,       2,     -4,      -5 , "UP_B",             0, 3, 0, l, true);
                    button(mcfunction,       3,     -4,      -6 , "NORTH_B",          0, 0,-3, l, true);
                    button(mcfunction,       4,     -4,      -5 , "SOUTH_B",          0, 0, 3, l, true);
                    button(mcfunction,       5,     -4,      -6 , "EAST_B",           3, 0, 0, l, true);
                    button(mcfunction,       6,     -4,      -5 , "WEST_B",          -3, 0, 0, l, true);

                }

//                static int a=next_letter;
                int a=1;
                button(mcfunction,       -6,     -5,       4 , "NEXT_A",     a, a, a, l, true); a++; //a=(rand())%26+1;
                button(mcfunction,       -5,     -5,       3 , "NEXT_B",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -4,     -5,       4 , "NEXT_C",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -3,     -5,       3 , "NEXT_D",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -2,     -5,       4 , "NEXT_E",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -1,     -5,       3 , "NEXT_F",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        0,     -5,       4 , "NEXT_G",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        1,     -5,       3 , "NEXT_H",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        2,     -5,       4 , "NEXT_I",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        3,     -5,       3 , "NEXT_J",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        4,     -5,       4 , "NEXT_K",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        5,     -5,       3 , "NEXT_L",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        6,     -5,       4 , "NEXT_M",     a, a, a, l, true); a++; // a=(rand())%26+1;

                button(mcfunction,       -6,     -1,       4 , "NEXT_N",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -5,     -1,       3 , "NEXT_O",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -4,     -1,       4 , "NEXT_P",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -3,     -1,       3 , "NEXT_Q",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -2,     -1,       4 , "NEXT_R",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,       -1,     -1,       3 , "NEXT_S",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        0,     -1,       4 , "NEXT_T",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        1,     -1,       3 , "NEXT_U",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        2,     -1,       4 , "NEXT_V",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        3,     -1,       3 , "NEXT_W",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        4,     -1,       4 , "NEXT_X",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        5,     -1,       3 , "NEXT_Y",     a, a, a, l, true); a++; // a=(rand())%26+1;
                button(mcfunction,        6,     -1,       4 , "NEXT_Z",     a, a, a, l, true); a++; // a=(rand())%26+1;

                if (do_makeit) {
                    button(mcfunction,        0,     -2,       0 , "ERASE_A",        0, 0, 0, l, true);
                    fprintf(mcfunction,"setblock ~ ~-1 ~1 glass 0\n");
                    fprintf(mcfunction,"setblock ~ ~-1 ~-1 glass 0\n");
                    fprintf(mcfunction,"setblock ~-1 ~-1 ~ glass 0\n");
                    fprintf(mcfunction,"kill @e[type=Bat,r=8]\n");
                }
//                fprintf(mcfunction,"setblock ~1 ~-1 ~ glass 0\n");

//                fprintf(mcfunction,"setblock ~1 ~-1 ~1 glass 0\n");
//                fprintf(mcfunction,"setblock ~1 ~-1 ~-1 glass 0\n");
//                fprintf(mcfunction,"setblock ~1 ~-1 ~ glass 0\n");

//                button(mcfunction,        0,      -2,       2 , "ERASE_B",        0, 0, 0, l);

//                fprintf(mcfunction,"execute kill @e[type=Bat,r=10]\n");
//                fprintf(mcfunction,"execute kill @e[type=Bat,r=10]\n");

                if (do_bats) {
                    fprintf(mcfunction,"kill @e[type=Bat,r=8]\n");
//                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
//                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                    fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                }
            }

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",    n_z-2,      z+1,   n_z+1,    n_z-2,      z+1,   n_z+1);        // SOUTH    //Y--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 3 keep\n",     n_z-2,    n_z-1,   n_z+1,    n_z-2,    n_z-1,   n_z+1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 3 keep\n",       z+2,      z+1,   n_z+1,      z+2,      z+1,   n_z+1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",      z+2,    n_z-1,   n_z+1,      z+2,    n_z-1,   n_z+1);        // SOUTH    //Y++

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",    n_z-1,      z+2,   n_z+1,    n_z-1,      z+2,   n_z+1);        // SOUTH    //X++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",    n_z-1,    n_z-2,   n_z+1,    n_z-1,    n_z-2,   n_z+1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",      z+1,      z+2,   n_z+1,      z+1,      z+2,   n_z+1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",      z+1,    n_z-2,   n_z+1,      z+1,    n_z-2,   n_z+1);        // SOUTH    //X--

//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",    n_z-1,      z+1,   n_z+1,    n_z-1,      z+1,   n_z+1);        // SOUTH    //LOWER RIGHT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",    n_z-1,    n_z-1,   n_z+1,    n_z-1,    n_z-1,   n_z+1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",      z+1,      z+1,   n_z+1,      z+1,      z+1,   n_z+1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 3 keep\n",      z+1,    n_z-1,   n_z+1,      z+1,    n_z-1,   n_z+1);        // SOUTH    //UPPER LEFT


            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 4 keep\n",    n_z-2,      z+1,     z-1,    n_z-2,      z+1,     z-1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",   n_z-2,    n_z-1,     z-1,    n_z-2,    n_z-1,     z-1);        // NORTH    //Y++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",     z+2,      z+1,     z-1,      z+2,      z+1,     z-1);        // NORTH    //Y--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 4 keep\n",      z+2,    n_z-1,     z-1,      z+2,    n_z-1,     z-1);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",    n_z-1,      z+2,     z-1,    n_z-1,      z+2,     z-1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",    n_z-1,    n_z-2,     z-1,    n_z-1,    n_z-2,     z-1);        // NORTH    //X++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",      z+1,      z+2,     z-1,      z+1,      z+2,     z-1);        // NORTH    //X--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",      z+1,    n_z-2,     z-1,      z+1,    n_z-2,     z-1);

//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",    n_z-1,      z+1,     z-1,    n_z-1,      z+1,     z-1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",    n_z-1,    n_z-1,     z-1,    n_z-1,    n_z-1,     z-1);        // NORTH    //UPPER LEFT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",      z+1,      z+1,     z-1,      z+1,      z+1,     z-1);        // NORTH    //LOWER RIGHT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 4 keep\n",      z+1,    n_z-1,     z-1,      z+1,    n_z-1,     z-1);


            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 1 keep\n",    n_z+1,      z+1,   n_z-2,    n_z+1,      z+1,   n_z-2);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",   n_z+1,    n_z-1,   n_z-2,    n_z+1,    n_z-1,   n_z-2);        // EAST     //Y++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",   n_z+1,      z+1,     z+2,    n_z+1,      z+1,     z+2);        // EAST     //Y--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 1 keep\n",    n_z+1,    n_z-1,     z+2,    n_z+1,    n_z-1,     z+2);

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,      z+2,   n_z-1,    n_z+1,      z+2,   n_z-1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,    n_z-2,   n_z-1,    n_z+1,    n_z-2,   n_z-1);        // EAST     //Z++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,      z+2,     z+1,    n_z+1,      z+2,     z+1);        // EAST     //Z--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,    n_z-2,     z+1,    n_z+1,    n_z-2,     z+1);

//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,      z+1,   n_z-1,    n_z+1,      z+1,   n_z-1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,    n_z-1,   n_z-1,    n_z+1,    n_z-1,   n_z-1);        // EAST     //UPPER LEFT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,      z+1,     z+1,    n_z+1,      z+1,     z+1);        // EAST     //LOWER RIGHT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 1 keep\n",    n_z+1,    n_z-1,     z+1,    n_z+1,    n_z-1,     z+1);


            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",     z-1,      z+1,   n_z-2,      z-1,      z+1,   n_z-2);        // WEST     //Y--
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 2 keep\n",      z-1,    n_z-1,   n_z-2,      z-1,    n_z-1,   n_z-2);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d stone_button 2 keep\n",      z-1,      z+1,     z+2,      z-1,      z+1,     z+2);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",     z-1,    n_z-1,     z+2,      z-1,    n_z-1,     z+2);        // WEST     //Y++

            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,      z+2,   n_z-1,      z-1,      z+2,   n_z-1);        // WEST     //Z++
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,    n_z-2,   n_z-1,      z-1,    n_z-2,   n_z-1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,      z+2,     z+1,      z-1,      z+2,     z+1);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,    n_z-2,     z+1,      z-1,    n_z-2,     z+1);        // WEST     //Z--

//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,      z+1,   n_z-1,      z-1,      z+1,   n_z-1);        // WEST     //LOWER RIGHT
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,    n_z-1,   n_z-1,      z-1,    n_z-1,   n_z-1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,      z+1,     z+1,      z-1,      z+1,     z+1);
//          fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d wooden_button 2 keep\n",      z-1,    n_z-1,     z+1,      z-1,    n_z-1,     z+1);        // WEST     //UPPER LEFT


            button(mcfunction,    n_z-2,    n_z-1,   n_z-1,"SOUTH_NEXT",    next_letter,next_letter,next_letter,l, false);
            button(mcfunction,      z+2,      z+1,   n_z-1,"SOUTH_ERASE",   0,0,0,l, false);
            button(mcfunction,    n_z-2,      z+1,   n_z-1,"SOUTH_Y_NEG",           0,-1, 0,l, false);
            button(mcfunction,      z+2,    n_z-1,   n_z-1,"SOUTH_Y_POS",           0, 1, 0,l, false);
            button(mcfunction,    n_z-1,      z+2,   n_z-1,"SOUTH_X_POS",           1, 0, 0,l, false);
            button(mcfunction,      z+1,    n_z-2,   n_z-1,"SOUTH_X_NEG",          -1, 0, 0,l, false);
//            button(mcfunction,    n_z-1,      z+1,   n_z-1,"SOUTH_LOWER_RIGHT",     0, 0, 0,l);
//            button(mcfunction,      z+1,    n_z-1,   n_z-1,"SOUTH_UPPER_LEFT",      1, 1, 1,l);

            button(mcfunction,      z+2,    n_z-1,     z+1,"NORTH_NEXT",    next_letter,next_letter,next_letter,l, false);
            button(mcfunction,    n_z-2,      z+1,     z+1,"NORTH_ERASE",           0, 0, 0,l, false);
            button(mcfunction,    n_z-2,    n_z-1,     z+1,"NORTH_Y_POS",           0, 1, 0,l, false);
            button(mcfunction,      z+2,      z+1,     z+1,"NORTH_Y_NEG",           0,-1, 0,l, false);
            button(mcfunction,    n_z-1,    n_z-2,     z+1,"NORTH_X_POS",           1, 0, 0,l, false);
            button(mcfunction,      z+1,      z+2,     z+1,"NORTH_X_NEG",          -1, 0, 0,l, false);
//            button(mcfunction,    n_z-1,    n_z-1,     z+1,"NORTH_UPPER_LEFT",      1, 1, 1,l);
//            button(mcfunction,      z+1,      z+1,     z+1,"NORTH_LOWER_RIGHT",     0, 0, 0,l);

            button(mcfunction,    n_z-1,    n_z-1,     z+2,"WEST_NEXT",     next_letter,next_letter,next_letter,l, false);
            button(mcfunction,    n_z-1,      z+1,   n_z-2,"WEST_ERASE",            0, 0 ,0,l, false);
            button(mcfunction,    n_z-1,    n_z-1,   n_z-2,"WEST_Y_POS",            0, 1, 0,l, false);
            button(mcfunction,    n_z-1,      z+1,     z+2,"WEST_Y_NEG",            0,-1, 0,l, false);
            button(mcfunction,    n_z-1,    n_z-2,   n_z-1,"WEST_Z_POS",            0, 0, 1,l, false);
            button(mcfunction,    n_z-1,      z+2,     z+1,"WEST_Z_NEG",            0, 0,-1,l, false);
//            button(mcfunction,    n_z-1,    n_z-1,   n_z-1,"WEST_UPPER_LEFT",       1, 1, 1,l);
//            button(mcfunction,    n_z-1,      z+1,     z+1,"WEST_LOWER_RIGHT",      0, 0, 0,l);

            button(mcfunction,      z+1,    n_z-1,   n_z-2,"EAST_NEXT",     next_letter,next_letter,next_letter,l, false);
            button(mcfunction,      z+1,      z+1,     z+2,"EAST_ERASE",            0, 0, 0,l, false);
            button(mcfunction,      z+1,      z+1,   n_z-2,"EAST_Y_NEG",            0,-1, 0,l, false);
            button(mcfunction,      z+1,    n_z-1,     z+2,"EAST_Y_POS",            0, 1, 0,l, false);
            button(mcfunction,      z+1,      z+2,   n_z-1,"EAST_Z_POS",            0, 0, 1,l, false);
            button(mcfunction,      z+1,    n_z-2,     z+1,"EAST_Z_NEG",            0, 0,-1,l, false);
//            button(mcfunction,      z+1,      z+1,   n_z-1,"EAST_LOWER_RIGHT",      0, 0, 0,l);
//            button(mcfunction,      z+1,    n_z-1,     z+1,"EAST_UPPER_LEFT",       1, 1, 1,l);

        }

//        fprintf(mcfunction,"setblock ~ ~ ~ air 0\n");
        if (chain==0) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x+16,-offset_y,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x+16,-offset_y,-offset_z,
                    -offset_x+16,-offset_y,-offset_z,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+32,-offset_y+16-16,-offset_z,
                    -offset_x+32,-offset_y+16-16,-offset_z,"YDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+48,-offset_y,-offset_z+16-16,
                    -offset_x+48,-offset_y,-offset_z+16-16,"ZDIR",2+64);
            }
        } else if (chain==1) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x,-offset_y+16,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+16,-offset_z,
                    -offset_x,-offset_y+16,-offset_z,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+16-16,-offset_y+32,-offset_z,
                    -offset_x+16-16,-offset_y+32,-offset_z,"XDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+48,-offset_z+16-16,
                    -offset_x,-offset_y+48,-offset_z+16-16,"ZDIR",2+64);
            }
        } else if (chain==2) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x,-offset_y,-offset_z+16);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:letter_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y,-offset_z+16,
                    -offset_x,-offset_y,-offset_z+16,substring.c_str(),next_letter+64);
            if (next_letter==26) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x+16-16,-offset_y,-offset_z+32,
                    -offset_x+16-16,-offset_y,-offset_z+32,"XDIR",2+64);
            }
            if (next_letter==25) {
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"/function abc:next_%s_%c\",auto:1b}\n",
                    -offset_x,-offset_y+16-16,-offset_z+48,
                    -offset_x,-offset_y+16-16,-offset_z+48,"YDIR",2+64);
            }
        } else if (chain==3) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",
                    -offset_x,-offset_y,-offset_z);
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0 replace redstone_block 0\n",
                    -offset_x,-offset_y+1,-offset_z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"/function abc:letter_%s_%c\"}\n",
                    -offset_x,-offset_y,-offset_z,
                    -offset_x,-offset_y,-offset_z,substring.c_str(),next_letter+64);
        }

//        fprintf(mcfunction,"fill ~ ~ ~ ~ ~ ~ command_block 0 keep {Command:\"/function abc:letter_%c\"}\n",next_letter+64);

        fclose(mcfunction);
    }

    sprintf(fname,"mcfunctions/letter_REMOVE.mcfunction");
    mcfunction=fopen(fname,"w");

    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   z,                    offset_y + z,                   offset_z + n_z,
             offset_x + n_z,                    offset_y + n_z,                 offset_z + n_z);   //Z+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   z,                    offset_y + z,                   offset_z +   z,
             offset_x + n_z,                    offset_y + n_z,                 offset_z +   z);   //Z-
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   z,                    offset_y + z,                   offset_z +   z,
             offset_x +   z,                    offset_y + n_z,                 offset_z +   n_z);   //X-
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x + n_z,                    offset_y + z,                   offset_z +   z,
             offset_x + n_z,                    offset_y + n_z,                 offset_z + n_z);   //X+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   z,                    offset_y + n_z,                 offset_z +   z,
             offset_x + n_z,                    offset_y + n_z,                 offset_z + n_z);   //Y+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   z,                    offset_y + z,                   offset_z + z,
             offset_x + n_z,                    offset_y + z,                   offset_z + n_z);   //Y-

    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             offset_x +   o,                    offset_y + o,                    offset_z + o   ,
             offset_x + n_o,                    offset_y + n_o,                  offset_z + n_o );   //Z+

    for (int z=-1; z<2; z++) {
        for (int y=-1; y<2; y++) {
            for (int x=-1; x<2; x++) {
                if (x!=0 || y!=0 || z!=0) {
                    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d redstone_block 0 replace glowstone 0\n",
                        offset_x-1+x*16, offset_y+y*16, offset_z+z*16,
                        offset_x-1+x*16, offset_y+y*16, offset_z+z*16);
                }
            }
        }
    }

    fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x,offset_y,offset_z);
    fclose(mcfunction);

    sprintf(fname,"mcfunctions/letter_%s_REMOVE.mcfunction",substring.c_str());

    mcfunction=fopen(fname,"w");

    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               z,                    z,                   n_z,
             n_z,                    n_z,                 n_z);   //Z+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               z,                    z,                     z,
             n_z,                    n_z,                   z);   //Z-
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               z,                    z,                     z,
               z,                    n_z,                   n_z);   //X-
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
             n_z,                    z,                     z,
             n_z,                    n_z,                 n_z);   //X+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               z,                    n_z,                   z,
             n_z,                    n_z,                 n_z);   //Y+
    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               z,                    z,                   z,
             n_z,                    z,                   n_z);   //Y-

    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d air 0\n",
               o,                    o,                    o   ,
             n_o,                    n_o,                  n_o );   //Z+

    for (int z=-1; z<2; z++) {
        for (int y=-1; y<2; y++) {
            for (int x=-1; x<2; x++) {
                if (x!=0 || y!=0 || z!=0) {
                    fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d redstone_block 0 replace glowstone 0\n",
                        -1+x*16, y*16, z*16,
                        -1+x*16, y*16, z*16);
                }
            }
        }
    }

    fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n",offset_x,offset_y,offset_z);
    fclose(mcfunction);

    printf("\n");
}


void button(FILE* mcfunction, int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, int l, bool blockit ) {

    if (offset_x==offset_y && offset_y==offset_z) {
        if (offset_x==0 && offset_y==0 && offset_z==0) {
            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n", x, y, z);
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s\"}\n", x, y, z,  x, y, z, name);
            if (l==1) button_B( x, y, z, name, offset_x, offset_y, offset_z, blockit );
        } else {
//            fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n", x, y, z);
            if (blockit) {
//                fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n", x, y, z);
//                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s_%c\"}\n", x, y, z,  x, y, z, name, offset_x+64);
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s\"}\n", x, y, z,  x, y, z, name, offset_x+64);
                if (l==1) {
                    button_B( x, y, z, name, offset_x, offset_x, offset_x, blockit );
//                    char new_name[100];
//                    sprintf(new_name,"%s_%c",name, l+64);
//                    button_B( x, y, z, new_name, offset_x, offset_x, offset_x, blockit );

                }
            } else {
                fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n", x, y, z);
                fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s_%c\"}\n", x, y, z,  x, y, z, name, offset_x+64);
                char new_name[100];
                sprintf(new_name,"%s_%c",name, l+64);
                button_B( x, y, z, new_name, l, l, l, blockit );
            }
        }
    } else {
//        fprintf(mcfunction,"setblock ~%d ~%d ~%d air 0\n", x, y, z);
        fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s\"}\n", x, y, z,  x, y, z, name);
        if (l==1) button_B( x, y, z, name, offset_x, offset_y, offset_z , blockit);
    }
    if (blockit) fprintf(mcfunction,"setblock ~%d ~%d ~%d light_weighted_pressure_plate 0 keep\n", x, y+1, z);
}

void button_B(int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, bool blockit ) {
    FILE* button_file;
    char fname[100];

    sprintf(fname,"mcfunctions/%s.mcfunction",name);
    button_file=fopen(fname,"w");

    if (offset_x==offset_y && offset_y==offset_z) {
        if (offset_x==0 && offset_y==0 && offset_z==0) {

          fprintf(button_file,"setblock ~%d ~%d ~%d air 0\n", -x, -y, -z);
          fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:letter_ONE_REMOVE\",auto:1b}\n", -x, -y, -z, -x, -y, -z);

//            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:%s\",auto:1b}\n", -x, -y, -z, -x, -y, -z, name);
            fprintf(button_file,"particle explode ~%d ~%d ~%d 16 16 16 0.1 5000\n", -x, -y, -z);
            fprintf(button_file,"kill @e[type=Bat,r=8]\n");
//            fprintf(button_file,"execute kill @e[type=Bat,r=9]\n");
//            /kill @e[type=Bat,r=RADIUS]

            if (blockit) {

//                button(mcfunction,      -5,     -4,      -5 , "UP",               0, 1, 0, l, true);
//                button(mcfunction,      -6,     -4,      -6 , "DOWN",             0,-1, 0, l, true);
//                button(mcfunction,      -3,     -4,      -5 , "SOUTH",            0, 0, 1, l, true);
//                button(mcfunction,      -4,     -4,      -6 , "NORTH",            0, 0,-1, l, true);
//                button(mcfunction,      -1,     -4,      -5 , "WEST",            -1, 0, 0, l, true);
//                button(mcfunction,      -2,     -4,      -6 , "EAST",             1, 0, 0, l, true);


                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             - 5, -y+        -16   -4, -z               -5,
                         -x             - 5, -y+        -16   -4, -z               -5);  //block up - down
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             - 6, -y+        +16   -4, -z               -6,
                         -x             - 6, -y+        +16   -4, -z               -6);  //block down - up
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             - 3, -y+              -4, -z               -5 -16,
                         -x             - 3, -y+              -4, -z               -5 -16);  //block south - north
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             - 4, -y+              -4, -z               -6 +16,
                         -x             - 4, -y+              -4, -z               -6 +16);  //block north - south
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x     +16     - 1, -y+              -4, -z               -5    ,
                         -x     +16     - 1, -y+              -4, -z               -5    );  //block west - east
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x    -16      - 2, -y+              -4, -z               -6    ,
                         -x    -16      - 2, -y+              -4, -z               -6    );  //block east - west

//                button(mcfunction,       2,     -4,      -5 , "UP_B",             0, 1, 0, l, true);
//                button(mcfunction,       1,     -4,      -6 , "DOWN_B",           0,-1, 0, l, true);
//                button(mcfunction,       4,     -4,      -5 , "SOUTH_B",          0, 0, 1, l, true);
//                button(mcfunction,       3,     -4,      -6 , "NORTH_B",          0, 0,-1, l, true);
//                button(mcfunction,       6,     -4,      -5 , "WEST_B",          -1, 0, 0, l, true);
//                button(mcfunction,       5,     -4,      -6 , "EAST_B",           1, 0, 0, l, true);

                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             + 2, -y+        -16   -4, -z               -5,
                         -x             + 2, -y+        -16   -4, -z               -5);  //block up - down
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             + 1, -y+        +16   -4, -z               -6,
                         -x             + 1, -y+        +16   -4, -z               -6);  //block down - up
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             + 4, -y+              -4, -z               -5 -16,
                         -x             + 4, -y+              -4, -z               -5 -16);  //block south - north
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x             + 3, -y+              -4, -z               -6 +16,
                         -x             + 3, -y+              -4, -z               -6 +16);  //block north - south
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x     +16     + 6, -y+              -4, -z               -5    ,
                         -x     +16     + 6, -y+              -4, -z               -5    );  //block west - east
                fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                         -x    -16      + 5, -y+              -4, -z               -6    ,
                         -x    -16      + 5, -y+              -4, -z               -6    );  //block east - west

            }



        } else {
            fprintf(button_file,"setblock ~%d ~%d ~%d air 0\n", -x, -y, -z);
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:current_ONE_%c\",auto:1b}\n", -x, -y, -z, -x, -y, -z, offset_x+64);
//            if (blockit) fprintf(button_file,"setblock ~ ~ ~ concrete 15\n");
//            if (blockit) fprintf(button_file,"fill ~ ~ ~-1 ~1 ~ ~1 concrete 15 replace command_block 0\n");
            if (blockit) fprintf(button_file,"fill ~ ~ ~ ~ ~ ~ concrete 15 replace command_block 0\n");
//            if (blockit) fprintf(button_file,"fill ~-1 ~ ~-1 ~1 ~ ~1 concrete 15 replace command_block 0\n");
//            fprintf(button_file,"execute kill @e[type=Bat,distance=..9]\n");
        }
    } else {
//        fprintf(button_file,"setblock ~%d ~%d ~%d air 0\"}\n", -x+offset_x*16, -y+offset_y*16, -z+offset_z*16);
        fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:current_ONE_A\",auto:1b}\n", -x+offset_x*16, -y+offset_y*16, -z+offset_z*16, -x+offset_x*16, -y+offset_y*16, -z+offset_z*16);
//        if (blockit) fprintf(button_file,"setblock ~ ~ ~ concrete 15\n");
        if (blockit) {
            fprintf(button_file,"fill ~ ~ ~ ~1 ~ ~1 concrete 15 replace command_block 0\n");

                fprintf(button_file,"setblock ~%d ~%d ~%d air 0\n", -x, -y-1, -z+1);
                fprintf(button_file,"setblock ~%d ~%d ~%d air 0\n", -x, -y-1, -z-1);
//                fprintf(button_file,"setblock ~%d ~%d ~%d glass 0\n", -x+1, -y-1, -z);
//                fprintf(button_file,"setblock ~%d ~%d ~%d glass 0\n", -x-1, -y-1, -z);

        }

        if (do_makeit) {
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           - 5, -y+  offset_y*16      -16   -4, -z  +offset_z*16             -5,
                     -x  +offset_x*16           - 5, -y+  offset_y*16      -16   -4, -z  +offset_z*16             -5);  //block up - down
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           - 6, -y+  offset_y*16      +16   -4, -z  +offset_z*16             -6,
                     -x  +offset_x*16           - 6, -y+  offset_y*16      +16   -4, -z  +offset_z*16             -6);  //block down - up
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           - 3, -y+  offset_y*16            -4, -z  +offset_z*16             -5 -16,
                     -x  +offset_x*16           - 3, -y+  offset_y*16            -4, -z  +offset_z*16             -5 -16);  //block south - north
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           - 4, -y+  offset_y*16            -4, -z  +offset_z*16             -6 +16,
                     -x  +offset_x*16           - 4, -y+  offset_y*16            -4, -z  +offset_z*16             -6 +16);  //block north - south
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16   +16     - 1, -y+  offset_y*16            -4, -z  +offset_z*16             -5    ,
                     -x  +offset_x*16   +16     - 1, -y+  offset_y*16            -4, -z  +offset_z*16             -5    );  //block west - east
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16  -16      - 2, -y+  offset_y*16            -4, -z  +offset_z*16             -6    ,
                     -x  +offset_x*16  -16      - 2, -y+  offset_y*16            -4, -z  +offset_z*16             -6    );  //block east - west

            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           + 2, -y+  offset_y*16      -16   -4, -z  +offset_z*16             -5,
                     -x  +offset_x*16           + 2, -y+  offset_y*16      -16   -4, -z  +offset_z*16             -5);  //block up - down
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           + 1, -y+  offset_y*16      +16   -4, -z  +offset_z*16             -6,
                     -x  +offset_x*16           + 1, -y+  offset_y*16      +16   -4, -z  +offset_z*16             -6);  //block down - up
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           + 4, -y+  offset_y*16            -4, -z  +offset_z*16             -5 -16,
                     -x  +offset_x*16           + 4, -y+  offset_y*16            -4, -z  +offset_z*16             -5 -16);  //block south - north
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16           + 3, -y+  offset_y*16            -4, -z  +offset_z*16             -6 +16,
                     -x  +offset_x*16           + 3, -y+  offset_y*16            -4, -z  +offset_z*16             -6 +16);  //block north - south
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16   +16     + 6, -y+  offset_y*16            -4, -z  +offset_z*16             -5    ,
                     -x  +offset_x*16   +16     + 6, -y+  offset_y*16            -4, -z  +offset_z*16             -5    );  //block west - east
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d concrete 15 replace command_block\n",
                     -x  +offset_x*16  -16      + 5, -y+  offset_y*16            -4, -z  +offset_z*16             -6    ,
                     -x  +offset_x*16  -16      + 5, -y+  offset_y*16            -4, -z  +offset_z*16             -6    );  //block east - west
        }

//        if (blockit) fprintf(button_file,"fill ~-1 ~ ~-1 ~1 ~ ~1 concrete 15 replace command_block 0\n");
    }
    fclose(button_file);

}






//BlockInfo*** AX;

//MCEditor editor;




