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

static void XMLCALL
	starthandler(void *data, const XML_Char *name, const XML_Char **attr)
{
	if (strcmp(name, "instruction") == 0||strcmp(name, "load") == 0) {
		//lwi command
		int i;
		long address;
		int size, hwords;
		uint32 fAddress
		for (;attr[i]; i+= 2) {
			if (strcmp(attr[i], "address") == 0) {
				address = strtol(attr[i + 1], NULL, 16);
				continue;
			}
			if (strcmp(attr[i], "size") == 0) {
				size = strtol(attr[i + 1], NULL, 16);
				continue;
			}
		}
		fAddress = (uint32)(address && 0xFFFFFFFF);
		if (size < 2) {
			fprintf(outFile, "lbui	r20, r0, %i\n", fAddress);
		} else {
			if (size%4) {
				hwords = size / 2 + 1;
				for (i = 0; i < hwords; i++) {
					fprintf(outFile,
						"lhui	r20, r0, %i\n",
						fAddress + i * 2);
				}
			} else {
				for (int i = 0; i < size; i += 4) {
					fprintf(outFile,
						"lwi	r20, r0, %i\n",
						fAddress + i);
				}
			}
		}
}



int main(int argc, char *argv[])
{
	int i, done;
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
		long len = fread(buffer, 1, sizeof(data), inFile);
		done = len < sizeof(buffer);

		if (XML_Parse(p_ctrl, buffer, len, 0) == 0) {
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
	
