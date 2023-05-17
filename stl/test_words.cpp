#include <algorithm>
#include <cctype>
#include <chrono>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1)
{
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](char c) { return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c) { return std::tolower(c); });
}

int main()
{
    int count = 0;
    std::string word;
    std::map<std::string, int> words;

    while (std::cin >> word)
    {
        toLowerAlpha(word);

        if (word.empty())
        {
            continue;
        }

        words[word]++;
    }

    std::cout << "Number of distinct words : " << words.size() << std::endl;
    std::cout << "\nThe top 20 most popular words: \n";

    std::multimap<int, std::string> sortedWords;
    std::for_each(words.begin(), words.end(),
                  [&sortedWords](auto p) { sortedWords.insert(std::make_pair(p.second, p.first)); });

    std::for_each_n(sortedWords.rbegin(), 20,
                    [&count](auto &p) { std::cout << p.second << " : " << p.first << std::endl; });

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */