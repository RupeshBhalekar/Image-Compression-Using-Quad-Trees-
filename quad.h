#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef long long ll;



typedef struct color{
    char r,g,b; 
}color;



typedef struct node{
    color c;
    int length;
    struct node * nw,*ne,*sw,*se;
}node;




node * createnode(color c,int l);

void addnode(node ** root,color c,int length);

color averagecolor(int x,int y,int l,int width,color a[width][width]);

int compare(int x,int y,int l,int width,color a[width][width],int p);

void compress(node ** root,int x,int y,int l,int width, color a[width][width],int p);

int isLeaf(node * root);

void fillSquare(int x, int y, color c, int l, int width, color a[width][width]);

void decompress(node **root, int x, int y, int l, int width, color a[width][width]);

void printImage(char *fileName, int width, color a[width][width]);

void freeTree(node **root);

void readImage(int p, char *inFile, char *outFile);

