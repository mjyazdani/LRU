/* Programmer : Mj.Yazdani
   Email : Mj.Yazdani1988@gmail.com
   Date: April 6, 2011
*/
/*********************************
 * Least Recently Used (LRU) algorithm is a page replacement technique
 * used for memory management. According to this method, the page which
 * is least recently used is replaced. Therefore, in memory, any page 
 * that has been unused for a longer period of time than the others is 
 * replaced.
 *********************************/

#include "conio.h"
#include <iostream>
using namespace std;

//If the request is available in the memory, function retuens the page number of the request,
//otherwise returns -1.
int IsAvailable(int a,int numofloc,int tempArray[])
{
	for (int i=0;i<numofloc;i++)
		if (tempArray[i]==a)
			return i;
	return -1;
}

//Main Function
int main()
{
    int temp=0;
    int const NumOfLocations = 3;
    
    //Get the number of requests
    cout<<"\nHow many Requests do you have?\n";
    cin>>temp;
    int const NumOfRequest = temp;

    //**Initilizing the variables
    
    /* First row of mainArray[][] keeps the requests entries.
      The last row, keeps whether page fault occured or not.
      Other rows keeps the pages in each memory location in each step.
    */
    int mainArray[NumOfLocations+2][NumOfRequest]={0};
    
    /* tempArray keeps the current amount of each memory location.*/
    int tempArray[NumOfLocations]={0};

	/* LRUMatrix is a square matrix and used to determine 
	which memory location (is/is not) referenced recently */
	int LRUMatrix[NumOfLocations][NumOfLocations]={0};
	
	int S=0,Smin=0,imin=0,faults=0;
	
	cout<<"************************************\n";
	cout<<"*     LRU Algorithem Started!      *\n";
	cout<<"************************************\n";

	//Reciving data from user
	cout<<"\nplease enter "<<NumOfRequest<<" numbers (don't enter 0):\n";
	for (int i=0 ;i<NumOfRequest;i++)
	{
		cin>>mainArray[0][i];
	}

	//Start to Calculate 
	for (int k=0;k<NumOfRequest;k++)
	{
		imin= IsAvailable(mainArray[0][k],NumOfLocations,tempArray);
	    //If the request was available in the memory ...
	    if (imin!=-1)
		{
		    //Create a new reference to the page.
			for (int w=0;w<NumOfLocations;w++)
			{
			    LRUMatrix[imin][w]=1;//row = 1
				LRUMatrix[w][imin]=0;//column = 0
			}
			mainArray[1][k]=tempArray[0];
			mainArray[2][k]=tempArray[1];
			mainArray[3][k]=tempArray[2];
			mainArray[4][k]=0;
		}
		//If the request was NOT available in the memory ...
		else
		{
			S=0;Smin=0;
			//Finding the page that should be replaced
			for(int i=0;i<NumOfLocations;i++){
				S=S*10+LRUMatrix[0][i];
			}
			
			Smin=S;
			
			if(Smin==0){
			    imin=0;
			    goto A;
			}
			
			for(int i=1;i<NumOfLocations;i++)
			{
				S=0;			
				for (int j=0;j<NumOfLocations;j++)				
					S=S*10+LRUMatrix[i][j];			
				if (S<Smin)
				{
					Smin=S;imin=i;
				}
			}
			
A:
            //Create a new reference to the page.
			for (int w=0;w<NumOfLocations;w++)
			{
				LRUMatrix[imin][w]=1;//row = 1
				LRUMatrix[w][imin]=0;//column =0
			}

			//Replace the new page with the old one.
			tempArray[imin]=mainArray[0][k];
				
			mainArray[1][k]=tempArray[0];
			mainArray[2][k]=tempArray[1];
			mainArray[3][k]=tempArray[2];
			mainArray[4][k]=1;
			faults++;
		}
	}
	
	//Printing the result
	cout<<"\n Requests:   | "; for(int i=0;i<NumOfRequest;i++)cout<<mainArray[0][i]<<" | ";
	cout<<"\n             "; for(int i=0;i<NumOfRequest;i++){cout<<"----";}  cout<<"-";
	cout<<"\n Location1:  | "; for(int i=0;i<NumOfRequest;i++)cout<<mainArray[1][i]<<" | ";
	cout<<"\n Location2:  | "; for(int i=0;i<NumOfRequest;i++)cout<<mainArray[2][i]<<" | ";
	cout<<"\n Location3:  | "; for(int i=0;i<NumOfRequest;i++)cout<<mainArray[3][i]<<" | ";
	cout<<"\n Page fault: | "; for(int i=0;i<NumOfRequest;i++)if(mainArray[4][i]==1)cout<<"+ | ";else cout<<"- | ";		
	cout<<endl;
	cout<<"\n Page fault percentage = "<<(float)(faults*100)/NumOfRequest<<"%";
	
	getch();
	return 0;
}


