/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <iostream>
#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    string wordFirst, wordSecond;
    if (wordsFile.is_open()) {
        while(getline(wordsFile,word)) {
            wordFirst = word.substr(1);
            wordSecond = word.substr(0, 1) + word.substr(2);

            bool firstTwo = d.homophones(word, wordFirst);
            bool secondTwo = d.homophones(word, wordSecond);
            bool thirdTwo = d.homophones(wordFirst, wordSecond);

            if (firstTwo && secondTwo && thirdTwo) {
                ret.push_back(std::tuple<string, string, string> (word, wordFirst, wordSecond));
            }
        }
    }
    return ret;
}
