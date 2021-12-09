#include <stdio.h>
#include <stdlib.h>

     
int modes(void);
int playerVsComputer(int modeChoice, char Board[3][3]);
int playerVsPlayer(int modeChoice, char Board[3][3]);
int whoPlaysFirst(int modeChoice);
char findWinner(char Board[3][3]);
void createBoard(char Board[3][3]);
void playerMove(char player, char Board[3][3]);
void computerMove(char player, char computer, char Board[3][3]);
int checkWinOrDeafeat(char mark, char computer, char Board[3][3]);
void printBoard(char Board[3][3]);



int main(void){

    char Board[3][3]; // the tic tac toe Board  
	int modeChoice;
	
	printf("************\nTic Tac Toe.\n\n");
	
	if(modes() == 1){
		modeChoice = 1;
		playerVsPlayer(modeChoice, Board);
	}
	else{
		modeChoice = 0;
		playerVsComputer(modeChoice, Board);
	}

	return 0;
}

//παιχτης εναντιον παιχτη 
int playerVsPlayer(int modeChoice, char Board[3][3]){
	char done, player1, player2;


	printf("************\nPlayer 1 VS Player 2.\n");
	done = ' ';
	createBoard(Board);
	
	printBoard(Board);
	if(whoPlaysFirst(modeChoice) == 1)
	{
		player1 = 'X';
		player2 = 'O';
		while(done == ' '){
			
			printf("Player 1 your turn.\n");
			playerMove(player1, Board);
			done = findWinner(Board); // see if Winner

			if(done == ' '){  
				
				
				printf("Player 2 your turn.\n");
				playerMove(player2, Board);
				done = findWinner(Board); // see if Winner 
				printf("%c", done);
			} 

			if(done == player1){ //Winner
				printf("************\nPlayer 1 won!\n");
			}
			if(done == player2){ 
				printf("************\nPlayer 2 won!\n");
			}
			if(done == 'D'){
				printf("Its a Draw!\n");
			}
			//printBoard(); // show final positions 
		}
	}
}

//παιχτης εναντια υπολογιστη 
int playerVsComputer(int modeChoice, char Board[3][3]){
	char done, computer, player;


	printf("************\nYou will be playing  against the computer.\n");
	done = ' ';
	createBoard(Board);
	
	printBoard(Board);
	if(whoPlaysFirst(modeChoice) == 1)
	{
		computer = 'O';
		player = 'X';
		while(done == ' '){
		
			playerMove(player, Board);
			done = findWinner(Board);   // see if Winner 
			if(done == ' '){  
				printf("%c\n", done);
				computerMove(player, computer, Board);
				done = findWinner(Board); // see if Winner 
			}

			if(done == player){ //Winner
				printf("************\nYou won!\n");
			}
			if(done == computer){ 
				printf("************\nComputer won!\n");
			}
			if(done == 'D'){
				printf("Its a Draw!\n");
			}
			//printBoard(); // show final positions 
		}
	}
	else
	{	
		computer = 'X';
		player = 'O';
		while(done == ' '){
		
			computerMove(player, computer, Board);
			done = findWinner(Board);   // see if Winner 
			if(done == ' '){  
				printf("%c\n", done);
				playerMove(player, Board);
				done = findWinner(Board); // see if Winner 
			} 
	
			if(done == player){ //Winner
				printf("************\nYou won!\n");
			}
			if(done == computer){ 
				printf("************\nComputer won!\n");
			}
			if(done == 'D'){
				printf("Its a Draw!\n");
			}
			//printBoard(); // show final positions 
		}
	}	
	return 0;
}

// Initialize the Board. 
void createBoard(char Board[3][3])
{
	int i, j;
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){ 
		Board[i][j] = ' ';
		}
	}
}

// Get a player's move. 
void playerMove(char player, char Board[3][3])
{
	int x, y;
	do{
		printf("Enter X,Y coordinates for your move: \nX: ");
		scanf("%d", &x);
		printf("Y: ");
		scanf("%d", &y);
		x= x - 1; 
		y= y - 1;

	}while(Board[x][y] != ' ');
	if(Board[x][y] == ' '){ 
		Board[x][y] = player;
		printBoard(Board);
	}
}

//επιλογες που εχει να κανει ο υπολογιστης και τι επιλεγει τελικα συμφωνα με την κατασταση στην οποια βρισκεται
void computerMove(char player, char computer, char Board[3][3]){ // player1, player 2 
	int found ;
	int i, j, x, y;
	char *pos;

	found = checkWinOrDeafeat(computer, computer, Board); // ψαχνω να βρω πιθανη θεση για νικη και την επιλεγω  
		
	if (found == 0){  
		
		found = checkWinOrDeafeat(player, computer, Board); // ψαχνω να δω αν υπαρχει πιθανη κινηση για ηττα και την αποφευγω
		
		if(found == 0){
			
			for(i=0; i<=2; i=i+2){		//ψαχνω για ελευθερες γωνιες αφου δεν υπαρχει κινδυνος για ηττα
				for(j=0; j<=2; j=j+2){
					
					if(Board[i][j] == ' ' ){
						pos = &Board[i][j];
						found = 1;
					}
	
					if(found==0){  //αλλιως ελλεγχω αν ή μεση ειναι κενη και τοποθετο 'Ο' σε αυτη 
						
						if(Board[1][1] == ' '){
							pos = &Board[1][1];
				
						}
						else{  //αλλιως επιλέγω μια τυχαία θεση ελεγχω αν ειναι κενη και βαζω 'Ο' σε αυτη 
							x = rand() % 3;
							y = rand() % 3;
							
							pos = &Board[x][y];
							
						}
					}
				}
			}
			if( computer == 'O'){ // τοποθετω το 'Ο' ή το 'Χ' αναλογα στον πινακα στην θεση στην οποια κατεληξα πιο πανω 
				*pos = 'O'; 
			}
			else{
				*pos = 'X';
			}				
		
		}
	}
	printBoard(Board);
}

//ελεγχω αν υπαρχει κινηση η οποια οδηγει στην ηττα ή στην νικη και προστατευομαι απο αυτη η την επιλεγω για να νικήσω
int checkWinOrDeafeat(char mark, char computer, char Board[3][3]){
   
	int found = 0 ;
	int x, y;
		
	if(Board[0][1]==mark && Board[0][2]==mark && Board[0][0]==' '){	//πανω γραμμη 
		x = 0;
		y = 0;
		found = 1;		
	}
	if(Board[1][1]==mark && Board[2][2]==mark && Board[0][0]==' '){	//διαγωνιος
		x = 0;
		y = 0;
		found = 1;
	} 	
	if(Board[2][0]==mark && Board[1][0]==mark && Board[0][0]==' '){	//1η στηλη
		x = 0;
		y = 0;
		found = 1;
	} 	
//***********
	if(Board[0][0]==mark && Board[0][2]==mark && Board[0][1]==' '){ //πανω γραμμη
		x = 0;
		y = 1;
		found = 1;
	}
	if(Board[2][1]==mark && Board[1][1]==mark && Board[0][1]==' '){ //2η στηλη
		x = 0;
		y = 1;
		found = 1;
	} 
//***********
	if(Board[0][0]==mark && Board[0][1]==mark && Board[0][2]==' '){ //πανω γραμμη
		x = 0;
		y = 2;
		found = 1;
	} 
	if(Board[1][1]==mark && Board[2][0]==mark && Board[0][2]==' '){	//διαγωνιος
		x = 0;
		y = 2;
		found = 1;
	} 
	if(Board[1][2]==mark && Board[2][2]==mark && Board[0][2]==' '){	//3η στηλη
		x = 0;
		y = 2;
		found = 1;
	} 
//***********
	if(Board[0][0]==mark && Board[2][0]==mark && Board[1][0]==' '){	//1η στηλη
		x = 1;
		y = 0;
		found = 1;
	} 
	if(Board[1][1]==mark && Board[1][2]==mark && Board[1][0]==' '){	//πανω γραμμη
		x = 1;
		y = 0;
		found = 1;
	} 
//***********
	if(Board[0][0]==mark && Board[2][2]==mark && Board[1][1]==' '){	//διαγωνιος
		x = 1;
		y = 1;
		found = 1;
	} 
	if(Board[0][1]==mark && Board[2][1]==mark && Board[1][1]==' '){	//2η στηλη 
		x = 1;
		y = 1;
		found = 1;
	} 
	if(Board[0][2]==mark && Board[2][0]==mark && Board[0][2]==' '){	//αντιθετη διαγωνιος
		x = 1;
		y = 1;
		found = 1;		
	} 
	if(Board[1][0]==mark && Board[1][2]==mark && Board[1][1]==' '){	//μεσαια γραμμη
		x = 1;
		y = 1;	
		found = 1;	
	} 
//***********
	if(Board[1][0]==mark && Board[1][1]==mark && Board[1][2]==' '){	//μεσαια γραμμη
		x = 1;
		y = 2;	
		found = 1;
	} 
	if(Board[0][2]==mark && Board[2][2]==mark && Board[1][2]==' '){	//πανω γραμμη
		x = 1;
		y = 2;	
		found = 1;
	} 
//***********
	if(Board[2][1]==mark && Board[2][2]==mark && Board[2][0]==' '){	//κατω γραμμη
		x = 2;
		y = 0;	
		found = 1;
	} 
	if(Board[0][2]==mark && Board[1][1]==mark && Board[2][0]==' '){	//αντιθετη διαγωνιος
		x = 2;
		y = 0;	
		found = 1;
	} 
	if(Board[0][0]==mark && Board[1][0]==mark && Board[2][0]==' '){ //1η στηλη 
		x = 2;
		y = 0;	
		found = 1;
	}    
//***********
	if(Board[0][1]==mark && Board[1][1]==mark && Board[2][1]==' '){ //2η στηλη
		x = 2;
		y = 1;	
		found = 1;
	} 
	if(Board[2][0]==mark && Board[2][2]==mark && Board[2][1]==' '){ //τελευταια γραμμη 
		x = 2;
		y = 1;
		found = 1;	
	} 
//***********
	if(Board[0][0]==mark && Board[1][1]==mark && Board[2][2]==' '){	//διαγωνιος
		x = 2;
		y = 2;
		found = 1;	
	} 
	if(Board[0][2]==mark && Board[1][2]==mark && Board[2][2]==' '){	//3η στηλη	
		x = 2;
		y = 2;
		found = 1;	
	} 
	if(Board[2][0]==mark && Board[2][1]==mark && Board[2][2]==' '){	//τελευταια γραμμη 
		x = 2;
		y = 2;
		found = 1;	
	} 
	if (found == 1){
		if(computer == 'O'){
			Board[x][y] = 'O';
		}
		else{
			Board[x][y] = 'X';	
		}

	}
	
	return found;
}

// Display the Board on the screen. 
void printBoard(char Board[3][3])
{
	int i;
	printf("************\n");
	for(i=0; i<3; i++) {
		printf(" %c | %c | %c ",Board[i][0],Board[i][1], Board [i][2]);
		if(i!=2){ 
			printf("\n---|---|---\n");
		}
	}
	printf("\n");
}

// See if there is a Winner. 
char findWinner(char Board[3][3])
{
	int i, j;
	int found = 0;
	int draw;

	

// Check rows for win 	
	for(i=0; i<3; i++){                                                    
		if(Board[i][0]==Board[i][1] && Board[i][0]==Board[i][2]){ 
			return Board[i][0];
			found = 1;
		}
	}		
// findWinner columns 
	for(i=0; i<3; i++){                                                   
		if(Board[0][i]==Board[1][i] && Board[0][i]==Board[2][i]){
			return Board[0][i];
			found = 1;
		}
	}
// test diagonals 
	if(Board[0][0]==Board[1][1] && Board[1][1]==Board[2][2]){
		return Board[0][0];
		found = 1;
	}
	if(Board[0][2]==Board[1][1] && Board[1][1]==Board[2][0]){
		return Board[0][2];
		found = 1;
	}
	draw = 1;
	if(found == 0){
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(Board[i][j]==' '){
					draw = 0;
				
				}
			}
		}
		if(draw==0){
			return ' ';
		}
		else{
			return 'D';
		}
	}	
}

//Modes επιστρεφει την επιλογη αυτη 
int modes(void){
    int modeChoice;
    
    printf("1. Player VS Player\n2. Player VS NPC\nChoose: ");
    do{
        scanf("%d", &modeChoice);
    }while((modeChoice != 1) && (modeChoice != 2));
    if (modeChoice == 1){
        return 1 ;
    } 
    else {
        return 2 ;
    }
}

//who plays First, επιστρέφει αληθης(1) αν η απαντηση ειναι Yes(y) και ψευδης(0) αν η απαντηση ειναι No(n)
int whoPlaysFirst(int modeChoice)
{
	char answer = ' ';
    //char junk;

	if (modeChoice == 1){
		
    }
    else{
  		printf("\nDo you want to go first? (y/n) ");
  		do{
		
			//junk='a'; while(junk != '\n') scanf("%c", &junk);
			scanf("%c", &answer);
		
    	} while ((answer != 'y') && (answer != 'Y') && (answer != 'n') && (answer != 'N'));

		if ((answer == 'y') || (answer == 'Y')){
    		return 1;
    	}
		else{
  			return 0;
		}
    
	}
}
