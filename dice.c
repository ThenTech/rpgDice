#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRINT_DICE		// Uncomment for intermediary print

/// http://xoroshiro.di.unimi.it/
#if 1 //USE_SPLITMIX64
    #include <stdint.h>

    static uint64_t seed; /* The state can be seeded with any value. */

    uint64_t next(void) {
        uint64_t z = (seed += 0x9e3779b97f4a7c15ULL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    }

    #define SEED()      seed = time(NULL)
    #define RINT(mx)	(next() % (mx) + 1)
#else
    #define SEED()      srand(time(NULL))
    #define RINT(mx)	(rand() % (mx) + 1)
#endif


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
            rnd += (tmp = RINT(FACES));
		#else
            rnd += RINT(FACES);
		#endif
		
		#ifdef PRINT_DICE
			printf("%d", tmp);
			if (i < DICE) printf(" + ");
		#endif
	}
	
	#ifdef PRINT_DICE
		     if (MOD < 0) printf(" - %d", -MOD);
		else if (MOD > 0) printf(" + %d", MOD);
		printf(" )  ==  ");
	#endif

	return rnd + MOD;
}

int main(void) {
    SEED();
    char str[20], *start, *end;
    int has_mod;
	
	while(1) {
        do {
            DICE = FACES = MOD = has_mod = 0;
            memset(str, 0, sizeof(str));
            
			//system("CLS");
            printf("Enter dice format as <dice>d<faces>[+|-]<modifier>, e.g. 2d6+3: ");
            scanf("%19s", str);

            #if 1 /// More complex but accurate parsing
                for (start = end = str; *end != '\0'; end++) {
                    if (strchr("d+-", *end) != NULL) { // delimiter at place end
                        switch (*end) {
                            case 'd':
                                DICE  = strtol(start, &end, 10); end++; break;
                            default: // + or -
                                FACES = strtol(start, &end, 10); has_mod = 1; break;
                        }
                        start = end;
                    }
                }

                if (has_mod) MOD   = strtol(start, &end, 10);
                else         FACES = strtol(start, &end, 10);
            #else
                /// Simple with [X]d[Y]+[(-)Z]
                pch = strtok(str, "d");
                for (i = 0; i < 3 && pch != NULL; i++) {
                    values[i] = atoi(pch);
                    pch = strtok(NULL, "d+");
                }
            #endif
		} while(DICE < 1 || FACES < 1);

        printf("\n\t%dd%d%+d  ==  ", DICE, FACES, MOD);
		printf("%2d\n\n", rollDice());
	}
	
	return 0;
}
