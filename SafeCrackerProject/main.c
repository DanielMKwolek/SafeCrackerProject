//
//  main.c
//  SafeCrackerProject
//
//  Created by Daniel Kwolek on 8/10/16.
//  Copyright © 2016 Arcore. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int safeCrackerGame(void);
int askForNumber(int possibilities, char *prompt);
int main(int argc, const char * argv[])
{
    int replay = 1;
    while (replay == 1)
    {
    replay = safeCrackerGame();
    }
}
int safeCrackerGame(void)
{
/*
 Ask the user for their name and use it to address them in the other steps.
 The safe in our game should have 4 randomly generated numbers from 0-3.
 The user should enter guesses 4 numbers at a time
 if the user guesses correctly, they win and the game ends.
 if the user guesses incorrectly, tell them how many they guessed correctly and allow them to try again
 */
    
    printf("Hello, what would you like to be called? (99 char or less please)\n: ");
    fpurge(stdin);
    char name[100] = {'\0'};
    int scanResults = scanf("%99s", name);
    printf("Hello, %s\n", name);
    int correctCombination[5] =
    {
        arc4random_uniform(3),
        arc4random_uniform(3),
        arc4random_uniform(3),
        arc4random_uniform(3),
        '\0'
    };
    printf("The safe combination is\n%d, %d, %d, %d\n\n", correctCombination[0], correctCombination[1], correctCombination[2], correctCombination[3]); //Delete this later
    printf("What is your guess?\n: ");
    fpurge(stdin);
    int guess[5] = {'\0'};
    int correct = 0;
    int numberGuesses = 0;
    scanResults = scanf("%1d%1d%1d%1d", &guess[0], &guess[1], &guess[2], &guess[3]);
    for (int i = 0; i < 4; i++)
    {
            if (guess[i] == correctCombination[i])
            {
                correct++;
            }
    }
    while (correct != 4)
    {
        numberGuesses++;
        printf("That time you guessed %d of the numbers correctly with\n: %d%d%d%d\nGuess again\n: ", correct, guess[0], guess[1], guess[2], guess[3]);
        correct = 0;
        fpurge(stdin);
        scanResults = scanf("%1d%1d%1d%1d", &guess[0], &guess[1], &guess[2], &guess[3]);
        printf("%d\n", scanResults);
        for (int i = 0; i < 4; i++)
        {
            if (guess[i] == correctCombination[i])
            {
                correct++;
            }
        }
        
    }
    numberGuesses++;
    printf("Congratulations!\nYou correctly guessed the safe combination of\n%d, %d, %d, %d\nIn %d guesses!\n\n", correctCombination[0], correctCombination[1], correctCombination[2], correctCombination[3], numberGuesses);
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
