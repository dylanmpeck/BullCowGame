#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
uint64 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 16}};
    return WordLengthToMaxTries[(int32)MyHiddenWord.length()];
    
}

void FBullCowGame::Reset()
{
    //constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "ant";

    bGameIsWon = false;
    //MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) // if guess isn't an isogram
        return EGuessStatus::Not_Isogram;
    else if (!IsLowercase(Guess)) // if guess isn't all lowercase
        return EGuessStatus::Not_Lowercase;
    else if (GetHiddenWordLength() != Guess.length())
        return EGuessStatus::Wrong_Length;
    else
        return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SumbitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    uint64 WordLength = MyHiddenWord.length(); // assuming same length as guess
    
    // loop through all letters in the hidden word
    for (int32 i = 0; i < WordLength; i++ )
    {
        // compare letters against the guess
        for (int32 j = 0; j < WordLength; j++)
        {
            if (Guess[i] == MyHiddenWord[j])
            {
                if (i == j)
                    BullCowCount.Bulls++;
                else
                    BullCowCount.Cows++;
            }
        }
    }
    if (BullCowCount.Bulls == WordLength)
        bGameIsWon = true;
    else
        bGameIsWon = false;
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter])
            return false;
        else
            LetterSeen[Letter] = true;
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    for (auto Letter : Word)
    {
        if (Letter < 'a' || Letter > 'z')
            return false;
    }
    return true;
}

void FBullCowGame::SetWord(int32 WordLength)
{
    TMap<int32, FString> WordLengthToWord { {3, "ant"}, {4, "fire"}, {5, "guard"}, {6, "planet"} };
    MyHiddenWord = WordLengthToWord[WordLength];
}











