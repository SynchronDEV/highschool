#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int printMenu();
int printView(int measurementNr, int valueArray[]);
int enterMeasurement(int measurementNr, int valueArray[]);
int computeData(int valueArray[]);
int restart(int measurementNr, int valueArray[]);
int quit();
int maxValue(int valueArray[], int n);
int minValue(int valueArray[], int n);
float avgValue(int valueArray[], int n);
float normValue(int valueArray[], int n);

int main(void)
{
	printf("hello world\n\n");
    
    char input;
    int loop=1, i=0, valueArray[10]={ 0 }, measurementNr = 0;
    
    printf("Measurement tool 1.2\n");
    printMenu();
    
    do
    {
       
        printf("VECRQ? ");
        scanf(" %c", &input);
        
            switch(input)
            {
                case 'v': printView(measurementNr, valueArray);
                    break;
                case 'r': measurementNr = restart(measurementNr,valueArray);
                    break;
                case 'e': measurementNr = enterMeasurement(measurementNr, valueArray);
                    break;
                case 'c': computeData(valueArray);
                    break;
                case 'q': quit();
                    break;
                default: printf("Please enter an accepted letter (lowercase): \n");
                    break;
            }
    }while(loop);

	return 0;
}
int printMenu()
{
    printf("v (View)\n");
    printf("e (Enter)\n");
    printf("c (Compute)\n");
    printf("r (Reset)\n");
    printf("q (Quit)\n\n");
}
int printView(int measurementNr, int valueArray[]) //v
{  
    if(valueArray[0]>0)
    {
        printf("[ ");
        for(int i=0;i<measurementNr;i++)
        {
            valueArray[i];
            printf(" %d ", valueArray[i]);
        }
        printf(" ]\n");
    }   
    else
    {
        printf("[ No measurements ]\n");
    }
}
int enterMeasurement(int measurementNr, int valueArray[]) //e
{
    int userNumberInput=1;
    
    if(measurementNr<10)
    {
        while(measurementNr<10)       
        {
            printf("Enter measurement #%d (or 0) ?", measurementNr+1);
            scanf("%d",&userNumberInput);
                        
            if(userNumberInput==0)
            {
                break;
            }
            else
            {
                valueArray[measurementNr++]=userNumberInput;
            }
        }
    }
    else
    {
        printf("Max value reached!\n");
    }
    return measurementNr;
             
}
int computeData(int valueArray[]) //c
{
    printf("Max value: %d\n", maxValue(valueArray, 10));
    printf("Min value: %d\n", minValue(valueArray, 10));
    printf("Avg value: %.2f\n", avgValue(valueArray, 10));
    printf("",normValue(valueArray, 10));
    
}
int restart(int measurementNr, int valueArray[]) //r
{
    for (int i = 0; i < 10; i++)
    {
        valueArray[i] = 0;
    }
    measurementNr = 0;
    
    return measurementNr;
        
}
int quit() //q
{
    printf("Exit measurement tool!\n");
    exit(0);
}
int maxValue(int valueArray[], int n)
{
    int i,maxValue=valueArray[0];
    for(i=1;i<n;i++)
        {
                if(maxValue<valueArray[i])
                {
                   maxValue=valueArray[i];
                }
        }
    return maxValue;
}
int minValue(int valueArray[], int n)
{
    int i,minValue=valueArray[0];
    
    for (i=0;i<n;i++) 
    {
        if(valueArray[i]>0)
        {
            if (minValue>valueArray[i]) 
            {
                minValue=valueArray[i];
            }
        }
  }
  return minValue;
}
float avgValue(int valueArray[], int n)
{
    float avg;
    int i, sum;
    
    sum = avg = 0;
    
    for(i=0;i<valueArray[i];i++)
    {
        sum = sum + valueArray[i];         
    }
    avg = (float)sum/i;
    
    return avg;
    
}
float normValue(int valueArray[], int n)
{
    int i;
    float normValue, calculation;
    normValue = avgValue(valueArray, 10);
    normValue = round(normValue);

    printf("[ ");
        for(int i=0;i<n;i++)
        {
            if(valueArray[i]>0)
            {
            valueArray[i] = valueArray[i] - normValue;
            printf(" %d ", valueArray[i]);
            }
        }
    printf(" ]\n");
   
}