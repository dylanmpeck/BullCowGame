/* This is the console executable, that makes use of the BullCow class
 This acts as the view in a MVC pattern, and is responsible for all user interaction. For Game logic see the FBullCowGame class.
 */
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int32 AskForWordLength();
void SetWord();

FBullCowGame BCGame; // instantiate a new game, which is reused across plays

int main()
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);

    return 0;
}


void PrintIntro()
{
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
    std::cout << std::endl;
    std::cout << "          }   {             _____" << std::endl;
    std::cout << "          (o o)             (o o)" << std::endl;
    std::cout << "   /-------\\ /               \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O                 O | COW | \\" << std::endl;
    std::cout << " *  |------|                    |-----|  *" << std::endl;
    std::cout << "    ^      ^                    ^     ^" << std::endl;
    std::cout << "Can you guess the isogram?\n";
    std::cout << std::endl;
    return;
}

FText GetValidGuess() //TODO change to get valid guess
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        std::cout << "Try " << BCGame.GetCurrentTry();
        std::cout << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            default:
                break;
        }
    }
    while (Status != EGuessStatus::OK);
    return Guess;
}

// plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    SetWord();
    int32 MaxTries = BCGame.GetMaxTries();
    //loop for the number of turns asking for guesses
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        

        FBullCowCount BullCowCount = BCGame.SumbitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n)";
    FText Response = "";
    getline (std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon() == true)
        std::cout << "WELL DONE - YOU WIN!!\n";
    else
        std::cout << "Better luck next time!\n";
}

void SetWord()
{
    int32 WordLength = AskForWordLength();
    BCGame.SetWord(WordLength);
    std::cout << "You chose to guess a " << WordLength << " letter isogram!\n";
    std::cout << std::endl;
}

int32 AskForWordLength()
{
    FString Line = "";
    int32 WordLength = 0;
    std::cout << "Choose a word length from 3 letters to 6 letters.\n";
    do
    {
        getline(std::cin, Line);
        if (Line[0] > '9' || Line[0] < '0')
            std::cout << "--Please enter a digit from 3 to 6--\n";
        else
        {
            WordLength = stoi(Line);
            if (WordLength < 3 || WordLength > 6)
                std::cout << "--Please enter a digit from 3 to 6--\n";
        }
    } while (WordLength < 3 || WordLength > 6);
    return WordLength;
}
