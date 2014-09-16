#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <time.h>


static const char filename[] = "ECG.txt";
int bookmark;

int getNextData(){
	FILE *file = fopen ( filename, "r" );
	int data;
	fseek(file, bookmark, SEEK_SET);
	if(bookmark == 0){
		int d1,d2,d3;
		fscanf(file,"%i",&d1);
		fscanf(file,"%i",&d2);
		fscanf(file,"%i",&d3);
		bookmark = ftell(file);
		int d[3] = {d1,d2,d3};
		return d;
	}

	if(fscanf(file,"%i",&data) != EOF){
		bookmark = ftell(file);
		return data;
	}
	return 0;
}


int main(){
	printf("%d",getNextData());
}

