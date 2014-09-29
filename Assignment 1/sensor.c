#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <time.h>
typedef struct dataPoint dataPoint;


static const char filename[] = "ECG.txt";
int bookmark = 0;
int dataBuffer[32];
int lowPassBuffer[2];
int highPassBuffer[1];

int getNextData(){
	FILE *file = fopen ( filename, "r" );
	int data;

	fseek(file, bookmark, SEEK_SET);
	if(fscanf(file,"%i",&data) != EOF){
		bookmark = ftell(file);
		for(int i=31;i>=0;i--){
					if(i==0) dataBuffer[i] = data;
					else dataBuffer[i] = dataBuffer[i-1];
				}
		return data;
	}
	return 0;
}



int lowPassFilter(int data){
	int x_low;
	x_low = 2*lowPassBuffer[0]-lowPassBuffer[1]+1/32*(data-2*dataBuffer[5]+dataBuffer[11]);

	for(int i=1;i>=0;i--){
			if(i==0) lowPassBuffer[i] = x_low;
			else lowPassBuffer[i] = lowPassBuffer[i-1];
		}
	return x_low;
}

int highPassFilter(int data){
	int x_high;
	x_high = highPassBuffer[0]-data/32+dataBuffer[15]-dataBuffer[16]+dataBuffer[31]/32;
	highPassBuffer[0] = x_high;
	return x_high;
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
	int test[5];
	for(int i=0; i<5;i++){
		test[i] = i;
	}

	for(int j=0;j<5;j++){
		printf("%d ",test[j]);
	}
	printf("  First\n");

	for(int k=4;k>=0;k--){
		if(k==0) test[k] = 5;
		else test[k] = test[k-1];
	}




	for(int l=0; l<5;l++){
		printf("%d ",test[l]);
	}
	return 0;
}

