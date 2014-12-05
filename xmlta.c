#include <stdio.h>
#include <stdlib.h>
#include <expat.h>
#include <stdint.h>
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
	int i, size = 0;
	uint32_t fAddress;
	long address = 0;

	if (strcmp(name, "store") == 0) {
		for (i = 0;attr[i]; i+= 2) {
			if (strcmp(attr[i], "address") == 0) {
				address = strtol(attr[i + 1], NULL, 16);
				continue;
			}
			if (strcmp(attr[i], "size") == 0) {
				size = strtol(attr[i + 1], NULL, 16);
				continue;
			}
		}
		fAddress = (unint32_t)(address & 0xFFFFFFFC
		switch (size) {
			case 0:
			break;

			case 1:
			fAddress = (uint32_t)(address & 0xFFFFFFFF);
			fprintf(outFile, "sbui	r20, r0, %#x\n", fAddress);
			break;

			case 2:
			fAddress = (uint32_t)(address & 0xFFFFFFFE);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress);
			break;

			case 3:
			case 4:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			break;

			case 5:
			case 6:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress + 4);
			break;

			case 7:
			case 8:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			break;

			case 9:
			case 10:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress + 8);
			break;

			case 11:
			case 12:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 8);
			break;

			case 13:
			case 14:
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"shui	r20, r0, %#x\n", fAddress + 12);
			break;
		}
	}

	if (strcmp(name, "instruction") == 0||strcmp(name, "load") == 0) {
		for (i = 0;attr[i]; i+= 2) {
			if (strcmp(attr[i], "address") == 0) {
				address = strtol(attr[i + 1], NULL, 16);
				continue;
			}
			if (strcmp(attr[i], "size") == 0) {
				size = strtol(attr[i + 1], NULL, 16);
				continue;
			}
		}
		fAddress = (uint32_t)(address & 0xFFFFFFFC);
		switch (size) {
			case 0:
			break;

			case 1:
			fAddress = (uint32_t)(address & 0xFFFFFFFF);
			fprintf(outFile, "lbui	r20, r0, %#x\n", fAddress);
			break;

			case 2:
			fAddress = (uint32_t)(address & 0xFFFFFFFE);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress);
			break;

			case 3:
			case 4:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			break;

			case 5:
			case 6:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress + 4);
			break;

			case 7:
			case 8:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			break;

			case 9:
			case 10:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress + 8);
			break;

			case 11:
			case 12:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			break;

			case 13:
			case 14:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"lhui	r20, r0, %#x\n", fAddress + 12);
			break;

			case 15:
			case 16:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"lwi	r20, r0, %#x\n", fAddress + 12);
			break;

			default:
			break;
		}
	}
	if (strcmp(name, "modify") == 0) {
		for (i = 0;attr[i]; i+= 2) {
			if (strcmp(attr[i], "address") == 0) {
				address = strtol(attr[i + 1], NULL, 16);
				continue;
			}
			if (strcmp(attr[i], "size") == 0) {
				size = strtol(attr[i + 1], NULL, 16);
				continue;
			}
		}
		fAddress = (uint32_t)(address & 0xFFFFFFFC);
		switch (size) {
			case 0:
			break;

			case 1:
			fAddress = (uint32_t)(address & 0xFFFFFFFF);
			fprintf(outFile, "lbui	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "sbui	r20, r0, %#x\n", fAddress);
			break;

			case 2:
			fAddress = (uint32_t)(address & 0xFFFFFFFE);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress);
			break;

			case 3:
			case 4:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			break;

			case 5:
			case 6:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress + 4);
			break;

			case 7:
			case 8:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			break;

			case 9:
			case 10:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lhui	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "shui	r20, r0, %#x\n", fAddress + 8);
			break;

			case 11:
			case 12:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 8);
			break;

			case 13:
			case 14:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"lhui	r20, r0, %#x\n", fAddress + 12);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"shui	r20, r0, %#x\n", fAddress + 12);
			break;

			case 15:
			case 16:
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "lwi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"lwi	r20, r0, %#x\n", fAddress + 12);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 4);
			fprintf(outFile, "swi	r20, r0, %#x\n", fAddress + 8);
			fprintf(outFile, 
				"swi	r20, r0, %#x\n", fAddress + 12);
			break;

			default:
			break;
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

	XML_Parser p_ctrl = XML_ParserCreate("UTF-8");
	if (!p_ctrl) {
		fprintf(stderr, "Could not create XML parser.\n");
		exit(-1);
	}

	XML_SetStartElementHandler(p_ctrl, starthandler);

	fprintf(outFile, ".set 0xE0000000 \n");
	
	do {
		long len = fread(buffer, 1, sizeof(buffer), inFile);
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
	fprintf(outFile, "rtsd	r15, 0x04\n");

	XML_ParserFree(p_ctrl);
	if (inFileStr) {
		fclose(inFile);
	}
	if (outFileStr) {
		fclose(outFile);
	}

	return 0;
}
	
