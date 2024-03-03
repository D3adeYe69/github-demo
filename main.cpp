#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <graphics.h>


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

void drawHangmanStage(int mistakes) {


        if (mistakes >= 1) {
            line(50, 20, 50, 200);
            line(50, 20, 100, 20);
            line(100, 20, 100, 55);
        }
        if (mistakes >= 2) {
             circle(100,75,20);
        }
        if (mistakes >= 3) {
            line(100,95,100,150);
        }
        if (mistakes>=4){
            line(100,95,75,120);
        }
        if (mistakes>=5){
           line(100,95,125,120);
        }
        if (mistakes>=6){
              line(100,150,75,175);
        }
          if (mistakes>=7){
                line(100,150,125,175);}


}

int playHangman(const char* randomWord, int len) {
    int mistakes = 0;
    char guessed[26] = "";

    while (mistakes < 7) {

        for (int i = 0; i < len; i++) {
            int charGuessed = 0;
            for (int j = 0; guessed[j] != '\0'; j++) {
                if (tolower(guessed[j]) == tolower(randomWord[i])) {
                    printf("%c ", randomWord[i]);

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
                printf("\nYou've already guessed that letter. Try another.\n");
                delay(1000);
                system("cls");
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
                    delay(200);
                    system("cls");

                    break;
                }
            }

            if (!letterInWord) {
                mistakes++;
                printf("\nInput %c is not in the word",input);
                drawHangmanStage(mistakes);
                delay(900);
                system("cls");
            }
        }
        printf("Previous guesses: %s\n", guessed);
    }

    printf("You've reached 7 mistakes. Game over. The word was \"%s\".\n", randomWord);


    return 1;
}


int main() {
    char input;
    printf("Welcome to Hangman!\n");
    printf("Write 'M' for multiplayer and 'S' for single player: ");
    scanf(" %c", &input);

    while (1) {
        int gd = DETECT , gm;
        initgraph(&gd, &gm, " ");

        if (tolower(input) == 'm') {
           char multiplayerWord[50];
        printf("Player 1, enter the word for Player 2 to guess: ");
        scanf("%s", multiplayerWord);
        system("cls");
        delay(1000);

        int len1 = strlen(multiplayerWord);
        return playHangman(multiplayerWord, len1);
        } else if (tolower(input) == 's') {
            int level = 1;

            while (level <= 5) {
                printf("Level %d\n", level);
                const char *randomWord = pickWord(level);
                int len = strlen(randomWord);

                if (playHangman(randomWord, len) == 0) {
                    level++;
                    delay(2000);
                    closegraph();
                    system("cls");
                    initgraph(&gd, &gm, " ");
                } else {
                    level = 1;
                    system("cls");
                    cleardevice();
                }
            }

            printf("You've completed all levels! Game over.\n");
            break;
        } else {
            printf("Invalid input. Please run the program again.\n");
            break;
        }
    }
    closegraph();

    return 0;
}
