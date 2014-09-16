#include <stdio.h>

int main(){
	printf("Hello World!\n\n");
	static const char filename[] = "ECG.txt";
	FILE *file = fopen ( filename, "r" );
	int i1 = 0;
	int i2;
	while(fscanf(file,"%i",&i2) != EOF) {
		if(i2>i1){
			i1 = i2;
		}

	}
	printf("largest number is: %d",i1);
	fclose(file);
	return 1;
}
