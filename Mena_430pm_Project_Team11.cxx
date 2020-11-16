/*
 * Jack Carnovale, Mychal Amoafo, Peter Dadson
 * Team 11
 * Portfolio Project 
 */
#include <stdlib.h>
#include <stdio.h>

int chopsticksMain();
void drawHands(int[],int[]);
void printFingers(char);
int canSplit(int[]);

int main(){
	
	return 0;
	
}


int chopsticksMain()
{
	//declare vars
	int user[]={1,1};
	int computer[]={1,1};
	int result=1, turn=0; //turn is 0 when user's turn, 1 when computers
	char quit;
	
	//show directions 
	printf("\nLet\'s play chopsticks!\n");
	printf("Your goal: Beat the computer by eliminating both of their hands.\n");
	printf("To eliminate a hand, hit it with one of yours, and the number of fingers will add.\n");
	printf("If you hit the other player\'s hand so they have exactly five fingers, that hand is out.\n");
	
	//loop for turns until someone wins
	while (result==1)
	{
		//draw hands
		drawHands(user,computer);
		
		//if user turn
		if (turn==0)
		{
			//ask if they want to opt out
			printf("Enter q to quit, enter anything else to play your turn: ");
			scanf(" %c",&quit);
			if (quit=='q'){
				break;
			}
			
			result=userTurn(user,computer);
			
		}
		//computer turn
		else
		{
			result=computerTurn(user,computer);
		}
		
		//ask if they want to opt out if no one has won yet
		if (result==1){
			printf("Enter q to quit, enter anything else to keep playing: ");
			scanf(" %c",&quit);
			if (quit=='q'){
				break;
			}
		}	
		
		//increment whos turn it is by using remainder
		turn =(turn+1)%2;
	}
	
			
	return result;
}


void drawHands(int user[],int computer[])
{
	
	//for loop
	int i;
	
	//top hands first - add fingers from bottom to top
	//this way looks like how normally would hold fingers - pointer by pointer
	printf("   User\t\tTop \t   Computer\n");
	for (i=4;i>=1;i--)
	{
		//neither have a finger there
		if (user[0]<i&&computer[0]<i)
			printFingers('N');
		//only computer has finger
		else if (user[0]<i)
			printFingers('C');
		//only user
		else if (computer[0]<i)
			printFingers('U');
		//both have fingers
		else
			printFingers('B');
			
	}
	
	
	
	//print bottom hands
	printf("\n\n \t\tBottom \n");
	for (i=1;i<=4;i++)
	{
		//neither have a finger there
		if (user[0]<i&&computer[0]<i){
			printFingers('N');
		}
		//only computer has finger
		else if (user[1]<i){
			printFingers('C');
		}
		//only user
		else if (computer[1]<i){
			printFingers('U');
		}
		//both have fingers
		else{
			printFingers('B');
		}
			
	}
}

//prints only user, only computer, both, or neither fingers
void printFingers(char which)
{
	//create strings for each part of a finger to be used for output
	//all are 13 char long
	//for when no finger output
	char gapFiller[]="             ";
	
	char uFP1[]="___________  ";
	char uFP2[]="________(__ )";
	char cFP1[]="  ___________";
	char cFP2[]="( __)________";
	
	//in the order checked: both, neither, user, computer
	switch (which)
	{
		case 'B':
		{
			printf("%s\t\t%s \n%s\t\t%s \n",uFP1,cFP1,uFP2,cFP2);
			break;
		}
		case 'N':
		{
			printf("\n\n");
			break;
		}
		case 'U':
		{
			printf("%s\t\t%s \n%s\t\t%s \n",uFP1,gapFiller,uFP2,gapFiller);
			break;
		}
		case 'C':
		{
			printf("%s\t\t%s \n%s\t\t%s \n",gapFiller,cFP1,gapFiller,cFP2);
			break;
		}
	}
}
//function to check if user or computer can split hands 1=yes 0=no
int canSplit(int array1[]){

	
	//top empty bottom >1
	if (array1[0]==0 && array1[1]>1){
		return 1;
	}
	//bottom empty top >1
	
	if (array1[1]==0 && array1[0]>1)
	{
		return 0;
	} 
		
	return -1;
}

int userTurn(int user[], int computer[])
{
	int splitresult,input; 
	splitresult=canSplit(user); 
	
	//printf("%d", splitresult); 
	
	 
	char cond1='z'; 
	
	
	if(splitresult==0) //top heavy, top is greater than
	{
		while( cond1!='y' && cond1!='n')
		{
			printf("Do you want to split?");
			scanf(" %c", &cond1); 
		}
		
		while(input<1 || input>user[1])
		{
			printf("How many fingers do you want to send to the other hand?\n");
			printf("You can only enter numbers between %d.\n", user[1]); 
			scanf("%d",&input); 
		}
		
		user[0]=input; 
		user[1]=user[1]-input; 
		
	}else if (splitresult==1) //bottom greater than top
	{
	
		while(cond1!='y' && cond1!='n')
		{
			printf("Do you want to split?"); 
			scanf(" %c",&cond1); 
		}
		
		while(input<1 || input>user[0])
		{
			printf("How many fingers do you want to send to the other hand?\n"); 
			printf("You can only enter numbers between %d.\n", user[0]);
			scanf("%d",&input); 
		}
		
		user[1]=input;
		user[0]=user[0]-input; 
	}else if(splitresult==-1)
	{
		printf("You can't split."); 
		
	}
	
	int computer_fingerchoice;
	printf("Which computer finger do you want to hit?");
	while( computer_fingerchoice!=0 && computer_fingerchoice!=1)
	{
		printf("Enter 0 for bottom. Enter 1 for top."); 
		scanf("%d",&computer_fingerchoice);
	}
	
	
	int user_fingerchoice; 
	printf("What finger do you want to use?"); 
	while(user_fingerchoice!=0 && user_fingerchoice!=1)
	{
		printf("Enter 0 for bottom. Enter 1 for top."); 
		scanf("%d",&user_fingerchoice);		
	}
	
	
		
	if(user_fingerchoice==0 && computer_fingerchoice==0) //user bottom to user botton
	{
		computer[0]=computer[0]+user[0];
		
	}else if (user_fingerchoice==0 && computer_fingerchoice==1) //user bottom to user top
	{
	
		computer[1]=computer[1]+user[0];
	}
	else if (user_fingerchoice==1 && computer_fingerchoice==0) //user top to computer bottom
	{
		computer[0]=computer[0]+user[1];
	}
	else if (user_fingerchoice==1 && computer_fingerchoice==1) //user top to computer top
	{
		computer[1]=computer[1]+user[1];
	}
	

	if(user[0]%5>=1)
	{
		return 2; 
	}
	
	return 1; 
	

	
}
void turnSummary(char turn, int user[], int computer[])
{
	switch (turn)
	{
		case 'c':
		printf("The computer hit user. The computer left hand has %d the right hand has %d.", computer[0], computer[1]); 
		break; 
		
		case 'u':
		printf("The user hit computer.The user left hand %d and the right hand has %d.",user[0], user[1]);
		break; 
		
	}
	
}
