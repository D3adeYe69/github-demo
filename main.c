#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




const char* pickWord(int level) {
    const char *Level1[] = { "apple", "banana", "orange", "grape", "lemon" };
    const char *Level2[] = { "elephant", "giraffe", "tiger", "zebra", "cheetah" };
    const char *Level3[] = { "chameleon", "rhinoceros", "hippopotamus", "crocodile", "alligator" };
    const char *Level4[] = { "peregrine", "falcon", "hawk", "eagle", "osprey" };
    const char *Level5[] = { "sasquatch", "yeti", "chupacabra", "mothman", "nessie" };
    srand(time(NULL));
    switch (level) {
        case 1:
            return Level1[rand() % 5];
        case 2:
            return Level2[rand() % 5];
        case 3:
            return Level3[rand() % 5];
        case 4:
            return Level4[rand() % 5];
        case 5:
            return Level5[rand() % 5];
        default:
            return Level1[rand() % 5];
    }
}

int playHangman(const char* randomWord, int len) {
    int mistakes = 0;
    char guessed[26] = "";

    while (mistakes < 5) {
        int found = 0;


        for (int i = 0; i < len; i++) {
            int charGuessed = 0;
            for (int j = 0; guessed[j] != '\0'; j++) {
                if (tolower(guessed[j]) == tolower(randomWord[i])) {
                    printf("%c ", randomWord[i]);
                    found = 1;
                    charGuessed = 1;
                    break;
                }
            }
            if (!charGuessed) {
                printf("_ ");
            }
        }
        printf("\n");


        if (strspn(randomWord, guessed) == strlen(randomWord)) {
            printf("Congratulations! You guessed the word \"%s\"!\n", randomWord);
            return 0;
        }

        printf("Enter a letter: ");
        char input;
        scanf(" %c", &input);

        int letterAlreadyGuessed = 0;
        for (int i = 0; guessed[i] != '\0'; i++) {
            if (tolower(guessed[i]) == tolower(input)) {
                letterAlreadyGuessed = 1;
                printf("You've already guessed that letter. Try another.\n");
                break;
            }
        }

        if (!letterAlreadyGuessed) {
            guessed[strlen(guessed)] = tolower(input);
            guessed[strlen(guessed) + 1] = '\0';

            int letterInWord = 0;
            for (int i = 0; i < len; i++) {
                if (tolower(randomWord[i]) == tolower(input)) {
                    letterInWord = 1;
                    break;
                }
            }

            if (!letterInWord) {
                printf(" Mistake: %c\n", input);
                mistakes++;
            }
        }
        printf("Previous guesses: %s\n", guessed);
    }

    printf("You've reached 5 mistakes. Game over. The word was \"%s\".\n", randomWord);
    return 1;
}

int main() {
    int level = 1;

    printf("Welcome to Hangman!\n");

    while (level <= 5) {
        printf("Level %d\n", level);
        const char* randomWord = pickWord(level);
        int len = strlen(randomWord);

        if (playHangman(randomWord, len) == 0) {
            level++;
        } else {
            level = 1;
        }
       system("cls");
    }


    printf("You've completed all levels! Game over.\n");

    return 0;
}
