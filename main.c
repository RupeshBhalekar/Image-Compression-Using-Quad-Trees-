#include"quad.c"

int main(int argc, char **argv)
{
	int tolerance = 0;
	
	char *inFile;
	char *outFile;
	char *new;

	
	if (argc > 1)
	{
		// compress the image
		if (strstr(argv[1], "-c"))
		{
			tolerance = atoi(argv[2]);
			inFile = argv[3];
		
			new = argv[4];
			readImage(tolerance, inFile, new);
			
			
		}
				
	
        
	}
	return 0;
}
