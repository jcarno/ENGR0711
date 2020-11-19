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
int computerTurn(int[],int[]);
int userTurn(int[],int[]);
void turnSummary(char,int,int);
void WhoDunnit(void);
void GameIntro(char[]);
void EvidenceExamination(int,int[]);
int LocationExploration(int,char[]);

int main(){
	//Variables
	int gamechoice;
	//Asks user which game they want to play, either Chopsticks or Who Dunnit?
	while(gamechoice!=1&&gamechoice!=2)
	{
		printf("Which game would you like to play?\n1)Chopsticks\n2)Who Dunnit?\n");
		scanf("%d",&gamechoice);
	}
	
	//Will run Chopsticks
	if(gamechoice==1)
	{
	chopsticksMain();
	}
	 
	//Will run Who Dunnit?
	if(gamechoice==2)
	{
		WhoDunnit();
	}
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
	printf("If you hit the other player\'s hand so they have exactly five fingers, that hand is out.\n\n");
	
	//draw hands
		drawHands(user,computer);
		
	//loop for turns until someone wins
	while (result==1)
	{
		
		
		//if user turn
		if (turn==0)
		{
			//ask if they want to opt out
			printf("You can opt out at any time. Enter q to quit, enter anything else to play your turn: ");
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
		
		//draw hands
		drawHands(user,computer);
		
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
		if (user[1]<i&&computer[1]<i){
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

//function to check if user or computer can split hands 1=bottom, 0=top, -1=no
int canSplit(int array1[]){
	
	//top empty bottom >1
	if (array1[0]==0 && array1[1]>1){
		return 1;
	}
	//bottom empty top >1
	if (array1[1]==0 && array1[0]>1){
		return 0;
	}
	return -1;
}

//function to do computer turn
int computerTurn(int user[],int computer[]){
	
	//becomes 0 if computer wins
	int i;
	
	//set up array with computer possible hits: top-top,top-bottom, bottom-top, bottom-bottom
	int possibilities[4]={(computer[0]+user[0])%5,(computer[0]+user[1])%5,(computer[1]+user[0])%5,(computer[1]+user[1])%5};
	
	//act in order of: get out a hand, allows winning combo next turn,split, closest to 5 on user
	
	//see if can get out a hand
	for (i=0;i<4;i++){
		
		//check if win, use integer division & remainders to get indexes for computer and user
		if (possibilities[i]==0 && computer[i/2]!=0){
			user[i%2]=possibilities[i];
			
			turnSummary('c',i/2,i%2);
			
			//check if computer won 
			if (user[0]==0 && user[1]==0)
			{
				return 0;
			}
	
			//return 1 if no win
			return 1;
		}
		
	}
	
	
	//check if potentially can get a hand out next turn by checking possibilities+current hand
	for (i =0;i<4;i++){
		//check if win, use integer division & remainders to get indexes for computer and user
		if (((possibilities[i]+computer[0])%5==0 || (possibilities[i]+computer[1])%5==0)&& computer[i/2]!=0){
			user[i%2]=possibilities[i];
			turnSummary('c',i/2,i%2);
		
			//return 1 to exit function
			return 1;
		}
		
		
	}
	
	//top hand can split
	if (canSplit(computer)==0){
		//break apart based on number of fingers, do in most even result
		if (computer[0]==2)
		{
			computer[0]=1;
			computer[1]=1;
			printf("Computer split fingers. 1 finger moved from top to bottom hand. \n");
		}
		else if (computer[0]==3)
		{
			computer[0]=2;
			computer[1]=1;
			printf("Computer split fingers. 1 finger moved from top to bottom hand. \n");
		}
		else if (computer[0]==4)
		{
			computer[0]=2;
			computer[1]=2;
			printf("Computer split fingers. 2 fingers moved from top to bottom hand. \n");
		}
		
		return 1;
			
	}
	//bottom hand can split
	else if (canSplit(computer)==1){
		//break apart based on number of fingers, do in most even result
		if (computer[1]==2)
		{
			computer[0]=1;
			computer[1]=1;
			printf("Computer split fingers. 1 finger moved from bottom to top hand. \n");
		}
		else if (computer[1]==3)
		{
			computer[0]=1;
			computer[1]=2;
			printf("Computer split fingers. 1 finger moved from bottom to top hand. \n");
		}
		else if (computer[1]==4)
		{
			computer[0]=2;
			computer[1]=2;
			printf("Computer split fingers. 2 fingers moved from bottom to top hand. \n");
		}
		
		return 1;
	}
	
	//if all else fails - do whatever gets computer closest to 5
	int maxIndex,maxVal=0;
	
	for (i =0;i<4;i++){
		//check if win, use integer division & remainders to get indexes for computer and user
		if (possibilities[i]>maxVal){
			maxVal=possibilities[i];
			maxIndex=i;
		}
	}
	
	user[maxIndex%2]=maxVal;
	
	turnSummary('c',maxIndex/2,maxIndex%2);
	
	return 1;
	
	
	
	
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
			printf("You can only enter numbers between 1 and %d.\n", user[1]-1); 
			scanf("%d",&input); 
		}
		
		user[0]=input; 
		user[1]=user[1]-input; 
		return 1;
		
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
			printf("You can only enter numbers between 1 and %d.\n", user[0]-1);
			scanf("%d",&input); 
		}
		
		user[1]=input;
		user[0]=user[0]-input; 
		
		return 1;
		
	}else if(splitresult==-1)
	{
		printf("You can't split.\n"); 
		
	}
	
	int computer_fingerchoice=-1;
	printf("Which computer hand do you want to hit?\n");
	while( computer_fingerchoice!=0 && computer_fingerchoice!=1)
	{
		printf("Enter 0 for top. Enter 1 for bottom. "); 
		scanf("%d",&computer_fingerchoice);
	}
	
	
	int user_fingerchoice=-1; 
	printf("What hand do you want to use?\n"); 
	while(user_fingerchoice!=0 && user_fingerchoice!=1)
	{
		printf("Enter 0 for top. Enter 1 for bottom. "); 
		scanf("%d",&user_fingerchoice);		
	}
	
	
		
	if(user_fingerchoice==0 && computer_fingerchoice==0) //user bottom to user botton
	{
		computer[0]=(computer[0]+user[0])%5;
		
	}else if (user_fingerchoice==0 && computer_fingerchoice==1) //user bottom to user top
	{
	
		computer[1]=(computer[1]+user[0])%5;
	}
	else if (user_fingerchoice==1 && computer_fingerchoice==0) //user top to computer bottom
	{
		computer[0]=(computer[0]+user[1])%5;
	}
	else if (user_fingerchoice==1 && computer_fingerchoice==1) //user top to computer top
	{
		computer[1]=(computer[1]+user[1])%5;
	}
	
	turnSummary('u',user_fingerchoice,computer_fingerchoice);
	
	if(computer[0]==0 && computer[1]==0)
	{
		return 2; 
	}
	
	return 1; 
	

	
}
void turnSummary(char turn, int handUsed, int handHit)
{
	
	//output based on who made the move and what hand was used and hit
	
	switch (turn)
	{
		case 'c':
		{
			if (handUsed==0){
				if (handHit==0){
					printf("The computer used their top hand to hit your top hand. \n");
				}
				else{
					printf("The computer used their top hand to hit your bottom hand. \n");
				}
			}
			else
			{
				if (handHit==0){
					printf("The computer used their bottom hand to hit your top hand. \n");
				}
				else{
					printf("The computer used their bottom hand to hit your bottom hand. \n");
				}
			}
	
			break; 
		}
		case 'u':
		{
			if (handUsed==0){
				if (handHit==0){
					printf("You used your top hand to hit the computer\'s top hand. \n");
				}
				else{
					printf("You used your top hand to hit the computer\'s bottom hand. \n");
				}
			}
			else
			{
				if (handHit==0){
					printf("You used your bottom hand to hit the computer\'s top hand. \n");
				}
				else{
					printf("You used your bottom hand to hit the computer\'s bottom hand. \n");
				}
			}
			break; 
		}
	}
	
}
