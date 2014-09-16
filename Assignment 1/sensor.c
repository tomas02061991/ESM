#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <time.h>


static const char filename[] = "ECG.txt";
int bookmark = 0;

int getNextData(){
	FILE *file = fopen ( filename, "r" );
	int data;
	fseek(file, bookmark, SEEK_SET);

	if(bookmark == 0){

	}

	if(fscanf(file,"%i",&data) != EOF){
		bookmark = ftell(file);
		return data;
	}
	return 0;
}

int lowPassFilter(int data){
	return 0;
}

int highPassFilter(int data){
	return 0;
}

int derivativeFilter(int data){
	return 0;
}

int squaringFilter(int data){
	return 0;
}

int movingWindowIntegration(int data){
	return 0;
}

int filterData(int data){
	data = lowPassFilter(data);
	data = highPassFilter(data);
	data = derivativeFilter(data);
	data = squaringFilter(data);
	data = movingWindowIntegration(data);
	return data;
}


int main(){
	printf("%d",getNextData());
	printf("%d",getNextData());
	printf("%d",getNextData());
	return 0;
}

