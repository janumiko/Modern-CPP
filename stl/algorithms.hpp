#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename Container> void print(const Container &c)
{
    // 1.  Print elements of the container separated by ", "
    //     using std::copy and std::ostream_iterator
    //  <<>> (1 line)
    std::copy(c.begin(), c.end(), std::ostream_iterator<decltype(*c.begin())>(std::cout, ", "));
    std::cout << std::endl;
}

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1)
{
    // 2. Implement using stl algorithms only
    //    Hint: use remove_if, transform, erase
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](char c) { return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c) { return std::tolower(c); });
}
/**
  Checks if the first word is an anagram of the second word.

     - All non alphanumeric chars are ignored (remove them).
     - It is case insensitive (convert to lower case).
     - Words cannot be the same (at least one change needed).
     - They should contain the same letters (sort letters in each word to compare).

  @param word1 not empty string
  @param word2 not empty string
  @return true if and only if word1 is an anagram of word2.
*/

bool isAnagram(std::string word1, std::string word2)
{
    // 3. Implement isAnagram function using stl algorithms only
    //    Hint: use toLowerAlpha, sort, equal
    //  <<>> (several lines)
    toLowerAlpha(word1);
    toLowerAlpha(word2);

    if (word1 == word2)
    {
        return false;
    }

    std::sort(word1.begin(), word1.end());
    std::sort(word2.begin(), word2.end());

    return std::equal(word1.begin(), word1.end(), word2.begin(), word2.end());
}

#endif // ALGORITHMS_HPP