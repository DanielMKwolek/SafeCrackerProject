//
//  main.c
//  SafeCrackerProject
//
//  Created by Daniel Kwolek on 8/10/16.
//  Copyright © 2016 Arcore. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int safeCrackerGame(void);
int askForNumber(int possibilities, char *prompt);



int main(int argc, const char * argv[])
{
    int replay = 0;
    do
    {
        replay = safeCrackerGame();
    } while (replay == 1);
    return 0;
}

int safeCrackerGame(void)
{
    
    printf("Hello, what would you like to be called? (99 char or less please)\n: ");
    fpurge(stdin);
    char name[100];
    int scanResults = scanf("%99s", name);
    fpurge(stdin);
    printf("Hello, %s\n", name);
    int safeMax;
    do
    {
        printf("What would you like the range of the safe combo to be? (9 max)\n: ");
        scanf("%1d", &safeMax);
        fpurge(stdin);
    } while (safeMax <= 0 && safeMax > 9);
    
    int correctCombination[5] =
    {
        arc4random_uniform(safeMax+1),
        arc4random_uniform(safeMax+1),
        arc4random_uniform(safeMax+1),
        arc4random_uniform(safeMax+1),
        '\0'
    };
    
    
    correctCombination[4] = '\0';
    fpurge(stdin);
    int guess[5] = {'\0'};
    int correct = 0;
    int numberGuesses = 1;
    int guessMax = 6;
    printf("How many guesses would you like?\n");
    scanf("%2d", &guessMax);
    int guessesLeft = guessMax;
    printf("You have %d guesses\nWhat is your guess? (4 numbers please: ie \"0000\")\n: ", guessesLeft);
    scanResults = scanf("%1d%1d%1d%1d", &guess[0], &guess[1], &guess[2], &guess[3]);
    for (int i = 0; i < 4; i++)
    {
        if (guess[i] == correctCombination[i])
        {
            correct++;
        }
    }
    while (correct != 4 && guessesLeft > 1)
    {
        guessesLeft = (guessMax - numberGuesses);
        printf("That time you guessed %d of the numbers correctly with\n: %d, %d, %d, %d\nGuesses left: %d\n: ", correct, guess[0], guess[1], guess[2], guess[3], guessesLeft);
        correct = 0;
        fpurge(stdin);
        scanResults = scanf("%1d%1d%1d%1d", &guess[0], &guess[1], &guess[2], &guess[3]);
        printf("%d\n", scanResults);
        
        numberGuesses++;
        for (int i = 0; i < 4; i++)
        {
            if (guess[i] == correctCombination[i])
            {
                correct++;
            }
        }
        
    }
    if (correct == 4)
    {
        printf("Congratulations!\nYou correctly guessed the safe combination of\n%d, %d, %d, %d\nIn %d guesses!\n\n", correctCombination[0], correctCombination[1], correctCombination[2], correctCombination[3], (numberGuesses));
    } else
    {
        printf("Sorry, the combination was:\n%d, %d, %d, %d\n\n", correctCombination[0], correctCombination[1], correctCombination[2], correctCombination[3]);
    }
    printf("Would you like to play again?\n1: Yes\n0: No\n");
    int answer = askForNumber(1, "Would you like to play again?\n1: Yes\n0: No\n");
    if (answer == 1)
    {
        return 1;
    }
    return 0;
}

int askForNumber(int possibilities, char *prompt)
{
    int answer = -1;
    while (answer < 0 || answer > possibilities)
    {
        printf("Valid choices: 0..%d\n:", possibilities);
        fpurge(stdin);
        scanf("%d", &answer);
        if (answer < 0 || answer >= possibilities+1)
        {
            printf("Valid choices: 0..%d\nEnter %d for prompt\n:", possibilities, possibilities+1);
            fpurge(stdin);
            scanf("%d", &answer);
            if (answer == (possibilities+1))
            {
                printf("\n%s\n", prompt);
                printf("Valid choices: 0..%d\n:", possibilities);
                fpurge(stdin);
                scanf("%d", &answer);
            }
        }
    }
    return answer;
}


