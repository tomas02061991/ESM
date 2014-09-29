#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <time.h>



static const char filename[] = "ECG.txt";
int bookmark = 0;
int dataBuffer[32];
int lowPassBuffer[2];
int highPassBuffer[1];
//create new array to save peaks in
int peakArray[30];
int peak;
int averagearray1[8];
int averagearray2[8];
int RR_AVERAGE1;
int RR_AVERAGE2;

int getNextData(){
	FILE *file = fopen ( filename, "r" );
	int data;

	fseek(file, bookmark, SEEK_SET);
	if(fscanf(file,"%i",&data) != EOF){
		bookmark = ftell(file);
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
	int x_der;
	x_der =1/8(2*data-dataBuffer[0]-dataBuffer[2]-2*dataBuffer[3]);
	return x_der;
}

int squaringFilter(int data){
	return sqrt(data);
}

int movingWindowIntegration(int data){
	int x;
	for(int i=30;i>0;i--) x+=dataBuffer[i-1];
	int x_mov = 1/30*x;

	return x_mov;
}

void filterData(int data){
	data = getNextData();
	data = lowPassFilter(data);
	data = highPassFilter(data);
	data = derivativeFilter(data);
	data = squaringFilter(data);
	data = movingWindowIntegration(data);
	for(int i=31;i>0;i--){
		if(i==0) dataBuffer[i] = data;
		else dataBuffer[i] = dataBuffer[i-1];
	}
}

void findPeak(){
//search for local maxima
	for(int i=0;i<31;i++){
		//save data point from the filters in array
		//add data to peakarray if data is a local maximum point
		//The acording to 1.4 print it so user can see it
		if(dataBuffer[i-1] < dataBuffer[i] && dataBuffer[i] > dataBuffer[i+1] && dataBuffer[i]!=0){
			for(int j=29;j>=0;j--){
						if(j==0) peakArray[j] = dataBuffer[i];
						else peakArray[j] = peakArray[j-1];
					}
			peak = dataBuffer[i];
		}
	}

}

void setAverage(){
	int average1, average2;
	for(int i=0; i<8;i++){
		average1 +=averagearray1[i];
		average2 +=averagearray2[i];
	}
	RR_AVERAGE1 = average1/8;
	RR_AVERAGE2 = average2/8;
}

//create variables
//SPKF = estimate of R-peak value
int SPKF = peak;
int NPKF = 0.125*peak + 0.875*1;
int THRESHOLD1 = NPKF+0.25*(SPKF-NPKF);
int THRESHOLD2 = 0.5*THRESHOLD1;

int RR_LOW = RR_AVERAGE2 * 0.92;
int RR_HIGH = RR_AVERAGE2 * 1.16;
int RR_MISS = RR_AVERAGE2 * 1.66;
int missedintervalcounter = 0;

//Make a loob to compare a datapoint peak to these variables
while(peak != 0){
	if(peak > RR_LOW && peak < RR_HIGH){
		missedintervalcounter = 0;
		if(peak > TRESHOLD1){
			averagearray2.add(peak);
			SPKF = 0.125 * peak + 0.875 * SPKF;
			THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
			THRESHOLD2 = 0.5 * THRESHOLD1;
			else{
				averagearray1.add(peak);
				THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
				THRESHOLD2 = 0.5 * THRESHOLD1;
				NPKF = 0.125 * peak + 0.875 * NPKF;
			}
		}else if(peak > RR_MISS){
			//increment counter
			missedintervalcounter = ++;
			if(missedintervalcounter = 5){
				print("warning missed peak interval");
			}
		//iterate through peakarray until a value greater
		//than TRESHOLD2 has been found
			//start at the end of the array
			for(int i=29; i>=0; i--){
				if(peakArray[i]>threshold2){
					for(int j=7;j>=0;j--){
							if(i==0){
								averagearray1[j] = peakArray[i];
								averagearray2[j] = peakArray[i];
							}
							else{
								averagearray1[i] = averagearray1[i-1];
								averagearray2[i] = averagearray2[i-1];
							}
					}
				}
			}

			while(peak1 < TRESHOLD2){
				peak1 = indexofpeakarray-1;
			}
			averagearray1.add(peak1);
			averagearray2.add(peak1);
			RR_AVERAGE1 = average of last 8 values added average array;
			RR_AVERAGE2 = average of last 8 values of average array 2;
			RR_LOW = RR_AVERAGE2 * 92%;
			RR_HIGH = RR_AVERAGE2 * 116%;
			RR_MISS = RR_AVERAGE2 * 166%;
			THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
			THRESHOLD2 = 0.5 * THRESHOLD1;
			SPKF = 0.25 * y + 0.75*SPKF;
		}else{
			missedintervalcounter = ++;
				if(missedintervalcounter = 5){
					print("warning missed peak interval");
				}
				if(peak < 2000){
					print("peak below 2000")
				}
		}	
	}
	print(peak);
	print(time);
	print(time between this peak and the last);
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

