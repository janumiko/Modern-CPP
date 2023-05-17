#ifndef TRIE_HPP
#define TRIE_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code.
 */
class Trie
{
  private:
    std::map<std::string, std::unique_ptr<Trie>> children{};
    bool is_sentence = false;

    void printAllSentences(const std::string &sentence)
    {
        if (is_sentence)
        {
            std::cout << sentence << "\n";
        }
        for (const auto &child : children)
        {
            child.second->printAllSentences(sentence + " " + child.first);
        }
    }

  public:
    static void printSentence(const std::vector<std::string> &sentence)
    {
        for (const auto &w : sentence)
        {
            std::cout << w << " ";
        }
    }

    void add(const std::vector<std::string> &sentence)
    {
        std::cout << "Adding : ";
        printSentence(sentence);
        std::cout << "\n";

        auto cursor = this;
        for (const auto &word : sentence)
        {
            if (cursor->children.find(word) == cursor->children.end())
            {
                cursor->children[word] = std::make_unique<Trie>();
            }
            cursor = cursor->children[word].get();
        }
        cursor->is_sentence = true;
    }

    void printPossibleEndings(const std::vector<std::string> &beginningOfSentece)
    {
        std::cout << "Endings for \"";
        printSentence(beginningOfSentece);
        std::cout << "\" are :\n";

        // print the trie sentences with begginning
        auto cursor = this;
        std::string sentence;
        for (const auto &word : beginningOfSentece)
        {
            if (cursor->children.find(word) == cursor->children.end())
            {
                std::cout << "No endings found\n";
                return;
            }
            cursor = cursor->children.at(word).get();
        }

        // print all sentences
        cursor->printAllSentences("");
    }

    void load(const std::string &fileName)
    {
        std::ifstream file(fileName);
        if (!file)
        {
            std::cerr << "Error when openning file " << fileName << std::endl;
            return;
        }
        std::string word;
        std::vector<std::string> sentence;
        while (file >> word)
        {
            sentence.push_back(word);
            // is it end of the sentence?
            if (word.find_last_of('.') != std::string::npos)
            {
                add(sentence);
                sentence.clear();
            }
        }
    }
};

#endif // TRIE_HPP