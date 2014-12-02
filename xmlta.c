#include <stdio.h>
#include <stdlib.h>
#include <expat.h>
#include <unistd.h>
#include <string.h>

#define BUFFSZ 512

static char buffer[BUFFSZ];
FILE *inFile;
FILE *outFile;
char *inFileStr = NULL;
char *outFileStr = NULL;

int main(int argc, char *argv[])
{
	int i;
	inFile = stdin;
	outFile = stdout;

	while ((i = getopt(argc, argv, "i:o:")) != -1){
		switch(i) {
		case 'i':
			inFileStr = optarg;
			break;
		case 'o':
			outFileStr = optarg;
			break;
		}
	}

	if (inFileStr) {
		inFile = fopen(inFileStr, "r");
		if (inFile == NULL) {
			fprintf(stderr, "Could not open %s\n", inFileStr);
			exit(-1);
		}
	}

	if (outFileStr) {
		outFile = fopen(outFileStr, "w");
		if (outFile == NULL) {
			fprintf(stderr, "Could not open %s\n", outFileStr);
			exit(-1);
		}
	}

	XML_Parser p_ctrl = XML_ParserCreate("UTF-8")
	if (!p_ctrl) {
		fprintf(stderr, "Could not create XML parser.\n");
		exit(-1);
	}

	XML_SetStartElementHandler(p_ctrl, starthandler);
	
	do {
		len = fread(data, 1, sizeof(data), inFile);
		done = len < sizeof(data);

		if (XML_Parse(p_ctrl, data, len, 0) == 0) {
			enum XML_Error errcode = XML_GetErrorCode(p_ctrl);
			fprintf(stderr, "XML ERROR: %s\n",
				XML_ErrorString(errcode));
			fprintf(stderr, "Error at column number %lu\n",
				XML_GetCurrentColumnNumber(p_ctrl));
			fprintf(stderr, "Error at line number %lu\n",
				XML_GetCurrentLineNumber(p_ctrl));
			exit(-1);
		}
	} while(!done);

	XML_ParseFree(p_ctrl);
	if (inFileStr) {
		fclose(inFile);
	}
	if (outFileStr) {
		fclose(outFile);
	}

	return 0;
}
	
