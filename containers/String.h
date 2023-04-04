#include <algorithm>
#include <iostream>
#include <memory>

#include "MyString.h"
using namespace std;

class String
{
    using string = emcpp::MyString;
    //    using string = std::string;

    /// Store a pointer to dynamically allocated string!

  private:
    std::shared_ptr<string> text{nullptr};

  public:
    String()
    {
        this->text = std::make_shared<string>();
    }; /// creates an empty string

    String(const char *str)
    {
        this->text = std::make_shared<string>(str);
    }; /// copy C-string

    String(const String &s)
    {
        this->text = s.text;
    }; /// no copy

    String operator=(const String &s)
    {
        this->text = s.text;
        return *this;
    }; /// no copy

    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch)
    {
        if (text.use_count() > 1)
        {
            this->text = std::make_shared<string>(*this->text);
        }

        (*this->text)[index] = ch;
    }

    /// no copy
    char get(int index) const
    {
        return (*this->text)[index];
    }

    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b)
    {
        if (*a.text == "")
        {
            return b;
        }

        if (*b.text == "")
        {
            return a;
        }

        return String((*a.text + *b.text).c_str());
    };

    friend std::ostream &operator<<(std::ostream &out, String s)
    {
        out << *s.text;
        return out;
    };
};
