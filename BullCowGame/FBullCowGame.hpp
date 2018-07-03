/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind
 */
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;
using uint64 = unsigned long;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    uint64 GetHiddenWordLength() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    void SetWord(int32);

    FBullCowCount SumbitValidGuess(FString);
    // provide a method for counting bulls and cows, & increasing try number
    
private:
    int32 MyCurrentTry;
    //int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
