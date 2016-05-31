#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRINT_DICE		// Uncomment for intermediary print

#define rnd(mx)	(rand() % mx + 1)

// { dice, faces, modifier }
static int values[3] = { 0 };

#define DICE	values[0]
#define FACES	values[1]
#define MOD 	values[2]

int rollDice() {
	int i = 0, rnd = 0;
	
	#ifdef PRINT_DICE
		int tmp = 0;
		printf("( ");
	#endif
	
	while (i++ < DICE) {
		#ifdef PRINT_DICE
			rnd += (tmp = rnd(FACES));
		#else
			rnd += rnd(FACES);
		#endif
		
		#ifdef PRINT_DICE
			printf("%d", tmp);
			if (i < DICE) printf(" + ");
		#endif
	}
	
	#ifdef PRINT_DICE
		if (MOD > 0) printf(" + %d", MOD);
		printf(" )  ==  ");
	#endif

	return rnd + MOD;
}

int main(void) {
	srand(time(NULL));
	char str[20], *pch;
	int i; 
	
	while(1) {
		DICE = FACES = MOD = 0;
		do {
			//system("CLS");
			printf("Enter dice format as <dice>d<faces>+<modifier>, e.g. 2d6+3: ");
			scanf("%20s", &str);

			pch = strtok(str, "d+");
			for (i = 0; i < 3 && pch != NULL; i++) {
				values[i] = atoi(pch);
				pch = strtok(NULL, "d+");
			}
			
		} while(DICE < 1 || FACES < 1 || MOD < 0);

		printf("\n\t%dd%d+%d  ==  ", DICE, FACES, MOD);
		printf("%2d\n\n", rollDice());
	}
	
	return 0;
}