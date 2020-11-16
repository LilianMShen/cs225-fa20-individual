/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            vector<string> letters;
            for (int i = 0; i < (int) word.length(); i++) {
                letters.push_back(word.substr(i, 1));
            }
            std::sort(letters.begin(), letters.end());
            dict[word] = letters;
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (string word : words) {
        vector<string> letters;
        for (int i = 0; i < (int) word.length(); i++) {
            letters.push_back(word.substr(i, 1));
        }
        std::sort(letters.begin(), letters.end());
        dict[word] = letters;
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> toReturn;

    if (dict.find(word) != dict.end()) {
        vector<string> letters = dict.find(word)->second;

        for (auto& w : dict) {
            if (letters == w.second && word != w.first) {
                if (toReturn.size() == 0) {
                    toReturn.push_back(word);
                }
                toReturn.push_back(w.first);
            }
        }
    }
    return toReturn;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> toReturn;

    for (auto& w : dict) {
        vector<string> anagrams = get_anagrams(w.first);

        if (anagrams.size() > 0) {
            toReturn.push_back(anagrams);
        }
    }

    return toReturn;
}
