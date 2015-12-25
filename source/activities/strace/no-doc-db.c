#include <stdio.h>
#include <string.h>

FILE *confFile;
char fileName[10];

int main() {
	memset(fileName, 'c', 10);
	fileName[1] += 'o'-'c';
	fileName[3] += 'n'-'c';
	fileName[2] += 'f'-'c';
	fileName[4] += 'i'-'c';
	fileName[5] += 'g'-'c';
	fileName[6] += '.'-'c';
	fileName[7] += 'x'-'c';
	fileName[8] += 'm'-'c';
	fileName[9] += 'l'-'c';

	confFile = fopen(fileName, "r");

	if(!confFile)
		return 100;

	printf("Reading config file...\n");
	printf("TODO: stuff\n");

	return 0;
}
