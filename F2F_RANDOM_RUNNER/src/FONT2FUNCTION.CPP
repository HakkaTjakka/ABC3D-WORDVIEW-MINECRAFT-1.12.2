#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

void font2function_sub(int chain);
void button(FILE* mcfunction, int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, int l, bool blockit );
void button_B( int x, int y, int z, char* name, int offset_x, int offset_y, int offset_z, bool blockit );

bool do_random=true;

int main(int argc, char ** argv) {
    srand(time(0));
    for (int n=0; n<argc; n++) printf("%s ",argv[n]);
    printf("\n");

//    font2function_sub(0);
//    font2function_sub(1);
//    font2function_sub(2);
    font2function_sub(3);
}   //


void font2function_sub(int chain) {
    sf::Image fontimage;
    fontimage.loadFromFile("resources/abc_16x16.png");
    printf("Size x=%d, y=%d\n",fontimage.getSize().x,fontimage.getSize().y);
    mkdir("mcfunctions");
    int offset_x=0;
    int offset_y=0;
    int offset_z=0;
    char block_inner[100]="concrete 0";
//    char block_outer[100]="concrete 13"; //dark green
    char block_outer[100]="glowstone 0";
    char block_back[100]="concrete 4";
//    char block_back2[100]="glowstone 0";
    char block_outline[100]="concrete 14";
    char block_fill[100]="stained_glass 5"; //lime green
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
                button(mcfunction,       -5,     -4,      -6 , "DOWN",           0,-1, 0, l, true);
                button(mcfunction,       -4,     -4,      -5 , "UP",             0, 1, 0, l, true);
                button(mcfunction,       -3,     -4,      -6 , "NORTH",          0, 0,-1, l, true);
                button(mcfunction,       -2,     -4,      -5 , "SOUTH",          0, 0, 1, l, true);
                button(mcfunction,       -1,     -4,      -6 , "EAST",           1, 0, 0, l, true);
                button(mcfunction,        0,     -4,      -5 , "WEST",          -1, 0, 0, l, true);

//                button(mcfunction,      -5,     -4,      6 , "DOWN_B",           0,-2, 0, l);
//                button(mcfunction,      -4,     -4,      5 , "UP_B",             0, 2, 0, l);
//                button(mcfunction,      -3,     -4,      6 , "NORTH_B",          0, 0,-2, l);
//                button(mcfunction,      -2,     -4,      5 , "SOUTH_B",          0, 0, 2, l);
//                button(mcfunction,      -1,     -4,      6 , "EAST_B",           2, 0, 0, l);
//                button(mcfunction,       0,     -4,      5 , "WEST_B",          -2, 0, 0, l);

                static int a=next_letter;
                button(mcfunction,       -6,     -5,       4 , "NEXT_A",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,       -5,     -5,       3 , "NEXT_B",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,       -4,     -5,       4 , "NEXT_C",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,       -3,     -5,       3 , "NEXT_D",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,       -2,     -5,       4 , "NEXT_E",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,       -1,     -5,       3 , "NEXT_F",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        0,     -5,       4 , "NEXT_G",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        1,     -5,       3 , "NEXT_H",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        2,     -5,       4 , "NEXT_I",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        3,     -5,       3 , "NEXT_J",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        4,     -5,       4 , "NEXT_K",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        5,     -5,       3 , "NEXT_L",     a, a, a, l, true); a=(rand())%26+1;
                button(mcfunction,        6,     -5,       4 , "NEXT_M",     a, a, a, l, true); a=(rand())%26+1;

                button(mcfunction,        0,     -2,       0 , "ERASE_A",        0, 0, 0, l, true);
                fprintf(mcfunction,"setblock ~0 ~-1 ~1 glass 0\n");
                fprintf(mcfunction,"setblock ~0 ~-1 ~-1 glass 0\n");
                fprintf(mcfunction,"setblock ~1 ~-1 ~1 glass 0\n");
                fprintf(mcfunction,"setblock ~1 ~-1 ~-1 glass 0\n");
                fprintf(mcfunction,"setblock ~1 ~-1 ~ glass 0\n");
//                button(mcfunction,        0,      -2,       2 , "ERASE_B",        0, 0, 0, l);

////                fprintf(mcfunction,"summon minecraft:bat ~-4 ~3 ~4\n");
                fprintf(mcfunction,"kill @e[type=Bat,r=8]\n");
//                fprintf(mcfunction,"execute kill @e[type=Bat,r=10]\n");
//                fprintf(mcfunction,"execute kill @e[type=Bat,r=10]\n");
                fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
                fprintf(mcfunction,"summon minecraft:bat ~ ~5 ~\n");
//                fprintf(mcfunction,"summon minecraft:bat ~4 ~3 ~-4\n");
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
            fprintf(mcfunction,"fill ~%d ~%d ~%d ~%d ~%d ~%d command_block 0 keep {Command:\"function abc:%s_%c\"}\n", x, y, z,  x, y, z, name, offset_x+64);
            char new_name[100];
            sprintf(new_name,"%s_%c",name, l+64);
            button_B( x, y, z, new_name, offset_x, offset_x, offset_x, blockit );
//            button_B( x, y, z, new_name, l, l, l );
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

        } else {
            fprintf(button_file,"setblock ~%d ~%d ~%d air 0\n", -x, -y, -z);
            fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:current_ONE_%c\",auto:1b}\n", -x, -y, -z, -x, -y, -z, offset_x+64);
            if (blockit) fprintf(button_file,"setblock ~ ~ ~ concrete 15\n");
//            fprintf(button_file,"execute kill @e[type=Bat,distance=..9]\n");
        }
    } else {
//        fprintf(button_file,"setblock ~%d ~%d ~%d air 0\"}\n", -x+offset_x*16, -y+offset_y*16, -z+offset_z*16);
        fprintf(button_file,"fill ~%d ~%d ~%d ~%d ~%d ~%d repeating_command_block 0 keep {Command:\"function abc:current_ONE_A\",auto:1b}\n", -x+offset_x*16, -y+offset_y*16, -z+offset_z*16, -x+offset_x*16, -y+offset_y*16, -z+offset_z*16);
        if (blockit) fprintf(button_file,"setblock ~ ~ ~ concrete 15\n");
    }
    fclose(button_file);

}

