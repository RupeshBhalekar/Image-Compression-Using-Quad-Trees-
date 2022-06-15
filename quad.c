#include "quad.h"


node * createnode(color c,int l){
    node * nn = (node*)malloc (sizeof(node));

    nn->c=c; 
    nn->length=l;
    nn->nw = NULL;
    nn->ne = NULL;
    nn->sw = NULL;
    nn->se = NULL;

    return nn;

}

void addnode(node ** root,color c,int length){
    node * q = createnode(c,length);

    if(*root == NULL) {
        *root = q;
        return;
    }
    if ((*root )->nw == NULL){
        (*root )->nw = q;
        return;
    }
    
    if ((*root )->ne == NULL){
        (*root )->ne = q;
        return;
    }

    if ((*root )->sw == NULL){
        (*root )->sw = q;
        return;
    }
    if ((*root )->se == NULL){
        (*root )->se = q;
        return;
    }

}

color averagecolor(int x,int y,int l,int width,color a[width][width]){
    color c;
    ll red=0;
    ll green = 0;
    ll blue = 0;
    int i,j;
    for(i=x ;i<x+l;i++)
        for(j=y;j<y+l;j++){
            red += a[i][j].r;
            green += a[i][j].g;
            blue += a[i][j].b;

        }
    
    c.r = red / (l*l);
    c.g = green / (l*l);
    c.b = blue /(l*l);
    return c;
}


// compares the mean calculated by me with the given tolerence
//here p is tolerence 
int compare(int x,int y,int l,int width,color a[width][width],int p)
{
    color c= averagecolor(x,y,l,width,a);
    float mean = 0;
    int i,j;
    for(i=x ;i<x+l;i++)
        for(j=y;j<y+l;j++){
            mean += (c.r - a[i][j].r) * (c.r - a[i][j].r);
            mean += (c.g - a[i][j].g) * (c.g - a[i][j].g);
            mean += (c.b - a[i][j].b) * (c.b - a[i][j].b);

        }

    mean /= (3*l*l);
    return (mean <=p);
}

//recursively didides yhe image into quad block until no division is necessary

void compress(node ** root,int x,int y,int l,int width, color a[width][width],int p)
{
    if(l<=1) return; // can't divide 1 pixel

    addnode(root,averagecolor(x,y,l,width,a),l);
    
    if(!compare(x,y,l,width,a,p))

    {
        compress(&(*root)->nw, x, y, l / 2, width, a, p);
		compress(&(*root)->ne, x, y + l / 2, l / 2, width, a, p);
		compress(&(*root)->sw, x + l / 2, y , l / 2, width, a, p);
		compress(&(*root)->se, x + l / 2, y + l / 2, l / 2, width, a, p);
    }

}

int isLeaf(node * root){
    return (root ->nw == NULL && root-> ne == NULL && root ->sw == NULL && root->se == NULL);
}




// Fills an uniform block inside a matrix
void fillSquare(int x, int y, color c, int l, int width, color a[width][width])
{
	int i, j;
	for (i = x; i < x + l; i++)
		for (j = y; j < y + l; j++)
		{
			a[i][j].r = c.r;
			a[i][j].g = c.g;
			a[i][j].b = c.b;
		}
}


void decompress(node **root, int x, int y, int l, int width, color a[width][width])
{
	if (*root == NULL)
		return;
	if (isLeaf(*root))
	{
		fillSquare(x, y, (*root)->c, l, width, a);
	}

	decompress(&(*root)->nw, x, y, l / 2, width, a);
	decompress(&(*root)->ne, x, y + l / 2, l / 2, width, a);
	decompress(&(*root)->se, x + l / 2, y + l / 2, l / 2, width, a);
	decompress(&(*root)->sw, x + l / 2, y, l / 2, width, a);
}




void printImage(char *fileName, int width, color a[width][width])
{
	FILE *fp = fopen(fileName, "wb");

	fprintf(fp, "P6\n");
	fprintf(fp, "%d %d\n", width, width);
	fprintf(fp, "255\n");

	int i;
	for (i = 0; i < width; i++)
		fwrite(a[i], sizeof(color), width, fp);

	fclose(fp);
}


void freeTree(node **root)
{
    if(*root == NULL)
        return;
    
    freeTree(&(*root)->ne);
    freeTree(&(*root)->nw);
    freeTree(&(*root)->se);
    freeTree(&(*root)->sw);

    free(*root);
}



void readImage(int p, char *inFile, char *outFile)
{
	FILE *f = fopen(inFile, "rb");

	char u[3]; // placehoder
	int width, height, max_value;
	fscanf(f, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

	color matrix[width][height];

	int i;
	for (i = 0; i < width; i++)
		fread(&matrix[i], sizeof(color), width, f);
	fclose(f);

	node *root = NULL;
	
	compress(&root, 0, 0, width, width, matrix, p);
	color a[width][width];
	decompress(&root, 0, 0, width, width, a);
	printImage(outFile, width, a);

    freeTree(&root);
}

