#pragma once
#include <iostream>
#include <memory>
#include "Box.h"

using std::cout;
using std::endl;

class Container{
    // Exercise 2: Use smart pointer.
    std::unique_ptr<Box> pbox{nullptr};
public:
    static bool verbose;
    Container(int content): pbox(new Box{content}){
        if(verbose) cout << "Creating Container" << endl;
    }
    Container(const Container & container): pbox(new Box{*(container.pbox)}){
        if(verbose) cout << "Creating copy of Container\n";
    }

    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }

    Container(Container && container) = default;
    Container& operator=(Container&& container) = default;

    ~Container(){
        if(verbose) cout << "Destroying Container \n";
    }
    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
