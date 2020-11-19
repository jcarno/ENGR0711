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

void WhoDunnit(void)
{
	//Variables
	char name[50];
	int sci,evi,evidencecompletion[3],loc,explorecompletion[3],gary2;
	//Will give a description of what is going on
	GameIntro(name);
	
	//User will enter 1 to get dialogue from forensic scientist
	printf("\nAlright Detective %s, first things first, you need to talk to the forensic scientist about the body. \nCHOP CHOP! NO TIME TO WASTE!\n (Press 1 to talk to the forensic scientist)\n",name);
	scanf("%d",&sci);
	
	while(sci!=1)
	{
		printf("Would you quit goofing off, %s! The murderer is getting away! Trust me I saw it on First 48. But seriously get to the forensic scientist (Press 1) \n",name);
		scanf("%d",&sci);
	}
	
	if(sci==1)
	{
		//User will choose with an integer which piece of evidence they would like to review first
		printf("\nForensic scientist: Welcome Detective %s, I have found a few pieces of evidence that could give us some leads.\n Which would you like to hear about first?\n",name);
		printf("1) Cause of death\n2) Belongings\n3) Burger takeout plate\n");
		scanf("%d",&evi);
	}
	
	while(evi!=1&&evi!=2&&evi!=3)
	{
		printf("C'mon Detective %s! Quit horsin around. Which evidence do you want to look at first?\n",name);
		scanf("%d",&evi);
	}
	//This function will go into detail what each piece of evidence reveals
	EvidenceExamination(evi,evidencecompletion);
	
	//Asks user which location would they like to travel to first
	printf("Alright Detective %s, what would you like to do now?\n1)Search Schenley Plaza more\n2)Search victim's dorm\n",name);
	scanf("%d",&loc);
	while(loc!=1&&loc!=2)
	{
		printf("C'mon %s you can't go there be serious. Where do you want to go?\n1)Search Schenley Plaza more\n2)Search victim's dorm\n",name);
		scanf("%d",&loc);
	}
	gary2=LocationExploration(loc,name);
	
}
//Function declaration
void GameIntro(char name[])
{
	printf("It was a quiet night in Oakland until... MURDER! Yes that's right...\nA John D. Cranbury was found dead in Schenley Plaza. He was such a diligent, proactive, involved\nstudent that was respected and adored by many. However, with that much attention, one is always bound to draw enemies\nand John's days were numbered. That is why we need YOU, detective, to solve this crime.\nFirst..., remind me of your name again?\n");
	scanf("%s",name);
}
void EvidenceExamination(int evi,int evidencecompletion[])
{
	
	do
	{
	switch(evi)
	{
	case 1:
	printf("\nThe victim was a 6 foot tall, 200 pound Caucasian male. The body was found around 12am on November 13, 2020. \nThe patient's medical history showed nothing of concern with no allergies or underlying conditions. \nThere were no external signs of trauma but an autopsy revealed that the victim had been poisoned with cyanide.\n");
	evidencecompletion[0]=1;
	printf("\nWhat evidence do you want to look at now?\n");
	printf("\n1) Cause of death\n2) Belongings\n3) Burger takeout plate\n");
	scanf("%d",&evi);
	break;
	
	case 2:
	printf("\nThe victim was found wearing a collared shirt, jeans, a Rolex, and light rain jacket. While the watch was quite valuable and still remained, his shoes, wallet, and phone were taken.\n");
	printf("\nWhat evidence do you want to look at now?\n");
	printf("\n1) Cause of death\n2) Belongings\n3) Burger takeout plate\n");
	scanf("%d",&evi);
	evidencecompletion[1]=1;
	break;
	
	case 3:
	printf("\nFound next to the victim was a takeout box with a burger with only one bite taken out of it.\n");
	printf("\nWhat evidence do you want to look at now?\n");
	printf("\n1) Cause of death\n2) Belongings\n3) Burger takeout plate\n");
	scanf("%d",&evi);
	evidencecompletion[2]=1;
	break;
}
}while(evidencecompletion[0]!=1&&evidencecompletion[1]!=1&&evidencecompletion[2]!=1);

}
int LocationExploration(int loc,char name[])
{
	int schenleychoice,gary2=0;
	switch(loc)
	{
	case 1:
	printf("Well Detective %s, I think some of the best witnesses would be at that 'Porch' restaurant or maybe some of the shuttle drivers. What do you think?\n",name);
	printf("1)The Porch employees\n2)Shuttle drivers\n");
	scanf("%d",&schenleychoice);
	while(schenleychoice!=1&&schenleychoice!=2)
	{
		printf("%s We don't have time to waste! Who do you want to interrogate?\n",name);
		scanf("%d",&schenleychoice);
	}
	if(schenleychoice==1)
	{
		printf("Restaurant employee: Yeah I work here. Good thing you came in before we closed early. I saw John last night he ordered 3 burgers for him and his girlfriend Jenny and his buddy James.\n I remember he was wearing some really loud shoes that drew attention. They were some high top neon green Nikes. To me they were pretty ugly but John was such a sneakerhead and a good friend and I'm gonna miss him. Please find the man that killed him.\n");
		printf("\n\nThat gives us some more information. Damn, the shuttles left us. Let's go to John's dorm now.\n");
	}
	
	else if(schenleychoice==2)
	{
		printf("Shuttle driver: I remember John's face. He came here with 2 other people earlier in the night but when his two friends rode the shuttle back it was just them. I think it was his girlfriend and another friend of his.\n");
		printf("\n Ok we should look into his girlfriend and other friend that was with him. According to the bus' ID scanner history, a few hours before the time of death a Jenny A. and James B. caught the shuttle from Sutherland. Let's go check out The Porch. Oh no! They're closed!\nWell what do you want to do now?:\n1)Search victim's dorm\n2)Interrogate friends\n");
	}
	
	case 2:
	printf("\nThe victim lived on the 8th floor of Tower C in a single room. The room was cleaned almost in a suspicious manner. The victim appears to have quite the collection of shoes. The victim's MacBook is here but appears to be severely damaged. Perhaps the tech team can recover the hard drive's content. A container of cyanide was placed haphazardly in the middle of the floor.\nKNOCK! KNOCK!\n\nGary G:Hey I'm Gary, John's neighbor, what's going on over here?\n");
	int gary;
	while(gary!=1&&gary!=2)
	{
	printf("\nChoose one of the following dialogue options:\n1)We are investigating the murder of John Cranbury. Do you have any information that you think you could offer us?\n2)Sir this is the site of a crime scene we need you to leave the premises now!\n");
	scanf("%d",&gary);
}
if(gary==2)
{
	printf("\nGeez man. You didn't have to turn me down like that. I might've had some helpful information for you. Have a good one jerk.\n");
}
else if(gary==1)
{
	printf("\nOh yeah, RIP John. I'm gonna miss that dude. He always had the cleanest shoe game. Yesterday, he was wearing some fire kicks you should've seen em. I know his girlfriend was really obsessive and jealous over how he spent too much time and money towards his shoe collection. But I would literally KILL to have some of the kicks he had.\n");
	gary2=0;
	while(gary2!=1&&gary2!=2)
	{
	printf("\nChoose one of the following dialogue options:\n1)Thanks Gary, anything else you want us to know?\n2)Thank you for your time Gary that will be all.\n");
	scanf("%d",&gary2);
}

if(gary2==1)
{
	printf("\nGary: Yeah, I dunno if this has anything to do with the crime but I heard some noise outside my room that sounding like it was coming from John's room around midnight or 1 in the morning. I almost ignored it but I peeped outside and saw it was John's girlfriend going into his room. I didn't think much of it because she has visited him before so I just went back to bed.\n");
}
else if(gary2==2)
{
	printf("\nGary: Happy to help. Lemme know if you need anything else.\n");
}
}
}


	return(gary2);
}
