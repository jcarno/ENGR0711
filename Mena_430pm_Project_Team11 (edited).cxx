/*
 * Jack Carnovale, Mychal Amoafo, Peter Dadson
 * Team 11
 * Portfolio Project 
 * 
 * 
 * 2 Games: Chopsticks and Who Dunnit.
 * 
 * Chopsticks is a player vs computer game where your goal is to eliminate both the other player's hands.
 * Each player starts with one finger on each hand. Every turn is one player hitting one of the other player's hands 
 * with one of their hands. When a hand is hit, it now has the remainder of the sum of the total number of fingers (on the hand used and hand hit) divided by 5.
 * When the remainder yields 0, that hand is out.  When a player has 0 on one hand and more than 1 finger on another, they can split
 * and send some (but not all) of those fingers to the other hand. The game ends when either the user or computer has both hands eliminated (0 fingers on both)
 * or the user can always quit prematurely. The user will be entering which hand to hit and which hand to use (numerical entry), or how many fingers to move to another hand.
 * The game alternates between user and computer turns.
 * 
 * Who Dunnit is a one player murder mystery game that is played by selecting various dialogue or action prompts while walking through the various locations
 * in the story as a detective trying to solve a murder. Throughout the game the user will give numerical input to choose different routes of trying to solve the mystery.
 * In each repetition of the game the user can create a different outputted dialogue and story than the last time. They can talk to people in different orders,
 * go to different locations, or have differing conversations depending on what selections they make.
 * The game eventually ends with the user picking who they think commmitted the murder.
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
void EvidenceExamination(int,int[],char[]);
int LocationExploration(int,char[]);
void Interrogation(int,char[],int[],int);
void Conclusion(char[],int);

int main(){
	//Variables
	int gamechoice,chopResult;
	char again='y';
	
	//let them keep playing as long as they want
	while(again=='y')
	{
		gamechoice=3;
		
	//Asks user which game they want to play, either Chopsticks or Who Dunnit?
	while(gamechoice!=1&&gamechoice!=2)
	{
		printf("Which game would you like to play?\n1)Chopsticks\n2)Who Dunnit?\n");
		scanf("%d",&gamechoice);
	}
	
	//Will run Chopsticks
	if(gamechoice==1)
	{
		chopResult=chopsticksMain();
		//display result of game
		switch (chopResult)
		{
			case 1:
			{
				printf("You have opted to quit. \n");
				break;
			}
			case 2:
			{
				printf("Congradulations! You won! \n");
				break;
			}
			case 0:
			{
				printf("You lost :( \n");
				break;
			}
		}
	}
	 
	//Will run Who Dunnit?
	if(gamechoice==2)
	{
		WhoDunnit();
	}
	
	again ='o';
	
	//ask if want to run the program again
	while(again!='y' && again !='n')
	{
		printf("Would you like to play another game? (y/n): ");
		scanf(" %c",&again);
	}
		
	}
	return 0;
}

int chopsticksMain()
{
	//declare vars
	int user[]={1,1};
	int computer[]={1,1};
	
	int result=1, turn=0; //turn is 0 when user turn, 1 when computer's turn
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
	
	//act in order of: get out a hand, allows winning combo next turn,split, random hit
	
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
	
	
	//random if computer attempts to split (Make it winnable)
	if (rand()%3==1)
	{
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
	
	
	}
	//if all else fails - do random hit 
	int val,ind;
	do{
		ind=rand()%4;
		val=possibilities[ind];
	}while (user[ind%2]==0 || computer[ind/2]==0);
	
	user[ind%2]=val;
	
	turnSummary('c',ind/2,ind%2);
	
	return 1;
	
	
	
	
}

//ask user to 
int userTurn(int user[], int computer[])
{
	//variable declaration and initialization 
	int splitresult,input=0; 
	
	//function declarations, split result stores the value of the canSplit variable 
	splitresult=canSplit(user); 
	
	//variable declaration to force the error checking 
	char cond1='z'; 
	
	
	if(splitresult==0) //top heavy, top is greater than bottom
	{
		while( cond1!='y' && cond1!='n') //while loop; error checks the user input split or no split
		
		{
			printf("Do you want to split? (y/n) ");
			scanf(" %c", &cond1); 
		}
		
		
		if (cond1!='n') //if the user wants to split 
		{
			while(input<1 || input>user[0]) //evaluates whether input is greater than 1 and less than the fingers on the users hand b/c you can't send all fingers to one hand 
			{
				printf("How many fingers do you want to send to the other hand?\n");
				printf("You can only enter numbers between 1 and %d.\n", user[0]-1); // the user can choose between 1 and the  
				scanf("%d",&input); 
			}
			
			user[1]=input;  //sends the input to the other hand
			user[0]=user[0]-input; //changes the number of fingers on the user's orginal hand
			
			return 1; //returns 1 to indicate the turn is over
			
		}
		
		
	}else if (splitresult==1) //bottom hand has more fingers than the top hand greater than top
	
	{
	
		//error checking the user input
		while(cond1!='y' && cond1!='n')
		{
			printf("Do you want to split? (y/n) "); 
			scanf(" %c",&cond1); 
		}
		
		//the following lines of code operate in the same fashion as the code above;however, we are splitting based on the 
		//bottom hand having more fingers than the top hand.
		
		if (cond1!='n')
		{
			while(input<1 || input>user[1])
			{
				printf("How many fingers do you want to send to the other hand?\n"); 
				printf("You can only enter numbers between 1 and %d.\n", user[1]-1);
				scanf("%d",&input); 
			}
		
			user[0]=input;
			user[1]=user[1]-input; 
		
			return 1;
		}
		
	}else if(splitresult==-1) //can't split 
	{
		printf("You can't split.\n"); //prints message  
	}
	
	//declares variable that allows user to choose what computer hand they want to hit.
	int computer_fingerchoice=-1;

	//asks the user's what computer hand they want to hit.
	printf("Which computer hand do you want to hit?\n");
	
	
	//while loop to error check the computer_fingerchoice
	while( computer_fingerchoice!=0 && computer_fingerchoice!=1)
	{
		printf("Enter 0 for top. Enter 1 for bottom. "); 
		scanf("%d",&computer_fingerchoice);
		
		//if hand chosen has no fingers make them pick again
		if (computer[computer_fingerchoice]==0){
			printf("Invalid. No fingers on that hand. Pick again. \n");
			computer_fingerchoice=-1;
		}
	}
	
	
	int user_fingerchoice=-1; 
	printf("What hand do you want to use?\n"); 
	
	while(user_fingerchoice!=0 && user_fingerchoice!=1)
	{
		printf("Enter 0 for top. Enter 1 for bottom. "); 
		scanf("%d",&user_fingerchoice);		
		//if hand chosen has no fingers make them pick again
		if (user[user_fingerchoice]==0){
			printf("Invalid. No fingers on that hand. Pick again. \n");
			user_fingerchoice=-1;
		}
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
		case 'c': // for the computer turn
		{
			/* If th computer uses their 0 hand it will describe what hand the computer hits 
			 * */
			if (handUsed==0){
				if (handHit==0){
					printf("The computer used their top hand to hit your top hand. \n");
				}
				else{
					printf("The computer used their top hand to hit your bottom hand. \n");
				}
			}
			else
			/*If the computer uses the their bottom hand it describes what hand the computer hits and prints to main 
			 * */
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
		/*Same principle applies as the block of code above, except it describes the actions of the user hand 
		 * */
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
	/*Welcome to WhoDunnit? You must solve the murder of John Cranbury. More information will follow from the game.
	Good luck detective!*/
	//Variables
	char name[50];
	int sci,evi,evidencecompletion[3],loc,gary2,interrogationcompletion[2],choice;
	//Will give a description of what is going on
	GameIntro(name);
	
	//User will enter 1 to get dialogue from forensic scientist
	printf("\nAlright Detective %s, first things first, you need to talk to the forensic scientist about the body. \nCHOP CHOP! NO TIME TO WASTE!\n(Press 1 to talk to the forensic scientist)\n",name);
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
	
	//This will error check to see if the user selected one of the 3 evidence options
	while(evi!=1&&evi!=2&&evi!=3)
	{
		printf("C'mon Detective %s! Quit horsin around. Which evidence do you want to look at first?\n",name);
		scanf("%d",&evi);
	}
	//This function will go into detail what each piece of evidence reveals
	EvidenceExamination(evi,evidencecompletion,name);
	
	//Asks user which location would they like to travel to first
	printf("\nAlright Detective %s, what would you like to do now?\n1)Search Schenley Plaza more\n2)Search victim's dorm\n",name);
	scanf("%d",&loc);
	
	//This will error check to see if the user selected one of the available locations
	while(loc!=1&&loc!=2)
	{
		printf("C'mon %s you can't go there be serious. Where do you want to go?\n1)Search Schenley Plaza more\n2)Search victim's dorm\n",name);
		scanf("%d",&loc);
	}
	
	//This function will explore the different locations based on the user's choice
	gary2=LocationExploration(loc,name);
	
	//This will ask the user which suspect they would like to interrogate first
	while(choice!=1&&choice!=2)
	{
	printf("\nDetective %s, it seems as if we have a few suspects to interrogate at this point.\nWho would you like to interrogate first?\n\n",name);
	printf("1)Jenny, John's girlfriend\n2)James,John's best friend\n\n");
	scanf("%d",&choice);
}

	//This function will interrogate 2 suspects with some dialogue options determining on previous decisions made in the game
	Interrogation(gary2,name,interrogationcompletion,choice);
	
	//This function will ask the user who they think is the murderer and tell them if they are correct or not
	Conclusion(name,gary2);
}
//Function declaration
void GameIntro(char name[])
{
	printf("It was a quiet night in Oakland until... MURDER! Yes that's right...\nA John D. Cranbury was found dead in Schenley Plaza. He was such a diligent, proactive, involved\nstudent that was respected and adored by many. However, with that much attention, one is always bound to draw enemies\nand John's days were numbered. That is why we need YOU, detective, to solve this crime.\nFirst..., remind me of your name again?\n");
	scanf("%s",name);
	
	//make sure it doesn't continually loop if enter spaces or multiple names
	fflush(stdin);
}
void EvidenceExamination(int evi,int evidencecompletion[],char name[])
{
	/*Depending on the evidence detail the user selected, the resulting information will display
	Each time a piece of evidence is reviewed the array "evidencecompletion" has a corresponding element updated to 1
	This will continue until all 3 pieces of evidence have been reviewed and all 3 elements in the array have been updated to 1
	*/
	
	while(evidencecompletion[0]+evidencecompletion[1]+evidencecompletion[2]!=3)
	{
		
		
	switch(evi)
	{
	case 1:
	printf("\nThe victim was a 6 foot tall, 200 pound Caucasian male. The body was found around 12am on November 13, 2020. \nThe patient's medical history showed nothing of concern with no allergies or underlying conditions. \nThere were no external signs of trauma but an autopsy revealed that the victim had been poisoned with cyanide.\n");
	evidencecompletion[0]=1;
	
	if(evidencecompletion[0]+evidencecompletion[1]+evidencecompletion[2]!=3)
	{
	printf("\nWhat evidence do you want to look at now?\n");
	if(evidencecompletion[1]!=1)
	{
	printf("\n2) Belongings\n");
}
if(evidencecompletion[2]!=1)
{
	printf("\n3) Burger takeout plate\n");
}
	scanf("%d",&evi);
	while(evi!=1&&evi!=2&&evi!=3)
		{
			printf("C'mon Detective %s! Quit horsin around. Which evidence do you want to look at now?\n",name);
			scanf("%d",&evi);
			
		}
}
	break;
	
	case 2:
	printf("\nThe victim was found wearing a collared shirt, jeans, a Rolex, and light rain jacket. While the watch was quite valuable and still remained, his shoes, wallet, and phone were taken.\n");
	evidencecompletion[1]=1;
	
	if(evidencecompletion[0]+evidencecompletion[1]+evidencecompletion[2]!=3)
	{
	printf("\nWhat evidence do you want to look at now?\n");
	if(evidencecompletion[0]!=1)
	{
		printf("\n1) Cause of death\n");
	}
	if(evidencecompletion[2]!=1)
	{
		printf("\n3) Burger takeout plate\n");
	}
	scanf("%d",&evi);
	while(evi!=1&&evi!=2&&evi!=3)
		{
			printf("C'mon Detective %s! Quit horsin around. Which evidence do you want to look at now?\n",name);
			scanf("%d",&evi);
			
		}
}
	break;
	
	case 3:
	printf("\nFound next to the victim was a takeout box with a burger with only one bite taken out of it.\n");
	evidencecompletion[2]=1;
	
	if(evidencecompletion[0]+evidencecompletion[1]+evidencecompletion[2]!=3)
	{
	printf("\nWhat evidence do you want to look at now?\n");
	if(evidencecompletion[0]!=1)
	{
		printf("\n1) Cause of death\n");
	}
	
	if(evidencecompletion[1]!=1)
	{
		printf("\n2) Belongings\n");
	}
	scanf("%d",&evi);
	while(evi!=1&&evi!=2&&evi!=3)
		{
			printf("C'mon Detective %s! Quit horsin around. Which evidence do you want to look at now?\n",name);
			scanf("%d",&evi);
			
		}
}
	break;
}

}

}
int LocationExploration(int loc,char name[])
{
	//Variables
	int schenleychoice,gary2=0,progress;
	switch(loc)
	{
	
	
	//Case 1 will run if the user decides to stay in Schenley plaza and go to John's dorm afterward
	case 1:
	printf("Well Detective %s, I think some of the best witnesses would be at that 'Porch' restaurant or \nmaybe some of the shuttle drivers. What do you think?\n",name);
	printf("\n1)The Porch employees\n2)Shuttle drivers\n");
	scanf("%d",&schenleychoice);
	while(schenleychoice!=1&&schenleychoice!=2)
	{
		printf("\n%s We don't have time to waste! Who do you want to interrogate?\n",name);
		scanf("%d",&schenleychoice);
	}
	if(schenleychoice==1)
	{
		printf("\nRestaurant employee: Yeah I work here. Good thing you came in before we closed early. I saw John last night he ordered 3 burgers for him and his girlfriend Jenny and his buddy James.\n I remember he was wearing some really loud shoes that drew attention. They were some high top neon green Nikes. To me they were pretty ugly but John was such a sneakerhead and a good friend and I'm gonna miss him. Please find the man that killed him.\n");
		printf("\n\nThat gives us some more information. Damn, the shuttles left us. Let's go to John's dorm now.\n");
	}
	
	else if(schenleychoice==2)
	{
		printf("\nShuttle driver: I remember John's face. He came here with 2 other people earlier in the night but when his two friends rode the shuttle back it was just them.\nI think it was his girlfriend and another friend of his.\n");
		printf("\n Ok we should look into his girlfriend and other friend that was with him. According to the bus' ID scanner history, a few hours before the time of death a Jenny A. and James B. caught the shuttle from Sutherland. Let's go check out The Porch. Oh no! They're closed!\nWell what do you want to do now?:\n1)Search victim's dorm\n2)Interrogate friends\n");
	}
	
	printf("\nEnter 1 to continue to John's dorm.\n");
	scanf("%d",&progress);
	while(progress!=1)
	{
		printf("\nDetective %s! We're losing daylight here. Press 1 so we can get to John's dorm!\n",name);
		scanf("%d",&progress);
	}
	//Case 2 will run if the user chose to go straight to John's dorm
	case 2:
	printf("\nThe victim lived on the 8th floor of Tower C in a single room. The room was cleaned almost in a suspicious manner.\n The victim appears to have quite the collection of shoes. The victim's MacBook is here but appears to be severely damaged. \nPerhaps the tech team can recover the hard drive's content. A container of cyanide was placed haphazardly in the middle of the floor.\nKNOCK! KNOCK!\n\nGary G:Hey I'm Gary, John's neighbor, what's going on over here?\n");
	
	//The variable "gary" will keep track of the course of the conversation that the user chooses between the detective and Gary
	int gary;
	while(gary!=1&&gary!=2)
	{
	printf("\nChoose one of the following dialogue options:\n1)We are investigating the murder of John Cranbury. Do you have any information that you think you could offer us?\n2)Sir this is the site of a crime scene we need you to leave the premises now!\n");
	scanf("%d",&gary);
}
if(gary==2)
{
	printf("\nGary:Geez man. You didn't have to turn me down like that. I might've had some helpful information for you. Have a good one jerk.\n");
}
else if(gary==1)
{
	printf("\nGary:Oh yeah, RIP John. I'm gonna miss that dude. He always had the cleanest shoe game.\nYesterday, he was wearing some fire kicks you should've seen em.\nI know his girlfriend was really obsessive and jealous over how he spent too much time and money towards his shoe collection.\nBut I would literally KILL to have some of the kicks he had.\n");
	
	//The variable "gary2" will keep further track of the converstion between the detective and Gary, how the user chooses to converse with Gary will depend on what information is revealed later in the game
	gary2=0;
	while(gary2!=1&&gary2!=2)
	{
	printf("\nChoose one of the following dialogue options:\n1)Thanks Gary, anything else you want us to know?\n2)Thank you for your time Gary that will be all.\n");
	scanf("%d",&gary2);
}

if(gary2==1)
{
	printf("\nGary: Yeah, I dunno if this has anything to do with the crime but I heard some noise outside my room that sounding like it was coming from John's room \naround midnight or 1 in the morning.\nI almost ignored it but I peeped outside and saw it was John's girlfriend going into his room.\nI didn't think much of it because she has visited him before so I just went back to bed.\n");
}
else if(gary2==2)
{
	printf("\nGary: Happy to help. Lemme know if you need anything else.\n");
}
}
}


	return(gary2);
}

void Interrogation(int gary2,char name[],int interrogationcompletion[],int choice)
{
	int dialogue,progress;
	
while(interrogationcompletion[0]+1&&interrogationcompletion[1]!=2)
{
	//This will ask the user which suspect they would like to interrogate first
	while(choice!=1&&choice!=2)
	{
	printf("\nDetective %s, it seems as if we have a few suspects to interrogate at this point.\nWho would you like to interrogate first?\n\n",name);
	printf("1)Jenny, John's girlfriend\n2)James,John's best friend\n\n");
	scanf("%d",&choice);
}
	//Dialogue between user and Jenny
	/*The variable "choice" will determine if the user would like to intially interrogate Jenny or James and 
	the variable "dialogue" will record the user's choices of dialogue options and tailor their path towards their decisions*/
	if(choice==1)
	{
		printf("\nYou: Good morning, I'm Detective %s and we are conducting an investigation around the murder of your boyfriend, John Cranbury.\n\n",name);
		printf("\nJenny: I'm happy to help Detective, but how do you know John was murdered?\n");
		
		while(dialogue!=1&&dialogue!=2)
		{
		printf("\nSelect a dialogue option:\n1)Our forensic scientist determined that John's death was caused by poisoning\n2)Just some details that have come to our attention point in that direction\n");
		scanf("%d",&dialogue);
	}
		if(dialogue==1)
		{
			printf("\nJenny: Poisoned? Sounds like an interesting way to go... But I'm here to answer any questions you want Detective\n");
			dialogue=0;
		}
		
		if(dialogue==2)
		{
			printf("\nJenny: Well whoever did this must pay, I'm willing to help out in any manner you need.\n");
			dialogue=0;
		}
		
		printf("\nYou: When was the last time you saw John?\n");
		printf("\nJenny: I saw him last around 11:30pm right before James and I got on the shuttle to go back to Sutherland\n");
		printf("\nYou: And when did you get back to Sutherland?\n");
		printf("\nJenny: Ummm.... To be honest... I kinda forgot. Sorry.\n");
		while(dialogue!=1&&dialogue!=2)
		{
			printf("\nSelect a dialogue option:\n");
			printf("\n1)Do you know anyone with any potential motives to harm John?\n2)Is it possible that you and John were having relationship issues?\n");
			scanf("%d",&dialogue);
		}
		
		if(dialogue==1)
		{
			printf("\nJenny: Nope. Are you insinuating something Detective %s? I don't want any more questions!\n",name);
			dialogue=0;
		}
		
		if(dialogue==2)
		{
			printf("\nJenny: How dare you! That is none of your businees! Get out of my face!\n");
			dialogue=0;
		}
		if(gary2==1)
		{
			printf("\nYou: Sorry ma'am. Just one more thing.\nWere you in John's dorm last night between 12AM and 1AM?\n");
			printf("\nJenny: Wha--- What are you talking about? That's ridiculous!\n");
			printf("\nYou: According to John's neighbor, he saw you going into his room between midnight and 1AM in the morning, which is strange because John's time of death was around midnight\n");
			printf("\nJenny: Well... Umm... I forgot something there and he game me his Panther ID to get it. Gary needs to mind his own business.\n");
			printf("\nYou: Well thank you for your time Ms. Jenny. I am sorry for your loss.\n");
			printf("\nJenny: It's alright detective. I'm glad I could help. It was time for me to move onto better things anyways.\n");
		}
		else if(gary2!=1)
		{
			printf("\nYou: I'm sorry Ms. Jenny. I'm sorry for your loss.\n");
		}
	
		interrogationcompletion[0]=1;
		if(interrogationcompletion[1]!=1)
		{
			progress=0;
			while(progress!=1)
			{
				printf("\nAlright Detective %s, now we have to interrogate James. Let's go! (press 1 to continue) \n",name);
				scanf("%d",&progress);
			}
			dialogue=0;
			progress=0;
			choice=2;
		}
	}
	
	//Dialogue between user and James
	if(choice==2)
	{
		printf("\nYou: Good morning, I'm Detective %s and we are conducting an investigation around the murder of your friend, John Cranbury.\n\n",name);
		printf("\nJames: Uhhhh... Yeah... Quite a shame.\n");
		printf("\nYou: When did you last see John?\n");
		printf("\nJames: Ummm... last night.\n");
		while(dialogue!=1&&dialogue!=2)
		{
		printf("\nSelect a dialogue option:\n1)Where were you and who were you with last night\n2)Why are you so nervous?\n");
		scanf("%d",&dialogue);
	}
	if(dialogue==1)
	{
		printf("\nJames: I was with ummm... Jenny in Schenley Plaza\n");
		printf("\nYou: Was John with you?\n");
		printf("\nJames: I... I think so... We got burgers from The Porch and sat on the lawn. John said he wasn't feeling well around 11:30pm but he just played it off as a stomach ache. Jenny and I got back on the shuttle to Sutherland and I went back to my dorm but Jenny didn't go back to hers. I don't know where she went though.\n");
		dialogue=0;
		//Depending on how thoroughly the user interrogated Gary, the neighbor, depends on if they unlock this dialogue option based on the value of the int "gary2"
		if(gary2==1)
		{
			printf("\nYou: That's interesting. John's neighbor told us that he saw Jenny going to John's room around 12 or 1 in the morning\n");
			printf("\nJames: Aw man... I had no clue... You don't think she...\n");
			printf("\nYou: James, we are going to do everything in our power to find John's killer and we won't stop until we do.\n");
			printf("\nJames: Thank you Detective %s, that means a lot to me.\n",name);
		}
		else if(gary2!=1)
		{
			printf("\nYou: Thank you for your time James.\n");
			printf("\nJames: R-- Re--- Really...? Is that all?\n");
			printf("\nYou: Yep. Thank you for your time James. I'm sorry for your loss.\n");
			printf("\nJames: That means a lot to me Detective %s. Go find that killer.\n",name);
		}
	}
	
	if(dialogue==2)
	{
		printf("\nJames: I DON'T KNOW! Ok look...\nJenny has been acting fishy lately and she had some grudge against John and she's been passive agressive towards him before he passed.\nI know that she was jealous about his dedication to his shoe collection and it was causing some relationship issues. I know it sounds as dumb to you as it does to me.\nI'm not saying she did it because Jenny is my friend too but she's been acting strange lately.\nJohn was like a brother to me and I'm going to miss him.\n");
		dialogue=0;
		
	}
	interrogationcompletion[1]=1;
	if(interrogationcompletion[0]!=1)
		{
			progress=0;
			while(progress!=1)
			{
				printf("\nAlright Detective %s, now we have to interrogate Jenny. Let's go! (press 1 to continue) \n",name);
				scanf("%d",&progress);
			}
			dialogue=0;
			progress=0;
			choice=1;
	}
	
}
	if(interrogationcompletion[0]+interrogationcompletion[1]==2)
	{
		break;
	}
}
}

void Conclusion(char name[],int gary2)
{
	int fin;
	while(fin!=1&&fin!=2&&fin!=3)
	{
	printf("\nAlright Detective %s, who do you think did it?\n",name);
	printf("\n1)Gary, the neighbor\n2)Jenny, the girlfriend\n3)James, the best friend\n");
	scanf("%d",&fin);
}
	//Based on the user's decision on who he/she thought the killer was, the outcome will display based on the value of the variable "fin"
	if(fin==1)
	{
		printf("\n Gary was not the killer! The true killer was Jenny, John's girlfriend who was motivated to do so by her jealousy of John's attention to his shoes over her.\n");
		if(gary2!=1)
		{
			printf("\n Because you didn't ask Gary, the neighbor, enough questions, you failed to find out that Jenny was in John's dorm where presumptuously cleaned up and left the cyanide there.\n");
		}
	}
	
	if(fin==2)
	{
		printf("\nCongrats! You caught the true killer, Jenny. It's quite unfortunate that Jenny poisoned John because\n of his tendency to care for his shoe apparel and then plant the evidence in his room and destroy his laptop.\n At least we caught her and she can't hurt anyone else.\n");
	}
	
	if(fin==3)
	{
		printf("\nNOPE! You let the killer get away detective. It was Jenny all along. Due to her unhealthy obsession with John, she got jealous over his shoe collection and his dedication to it and led her to kill John.\n");
		if(gary2!=1)
		{
			printf("\n Because you didn't ask Gary, the neighbor, enough questions, you failed to find out that Jenny was in John's dorm where presumptuously cleaned up and left the cyanide there.\n");
		}
	}
}
