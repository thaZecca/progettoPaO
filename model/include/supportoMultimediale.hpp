#ifndef SUPP_MULT_HPP
#define SUPP_MULT_HPP

#include "digitale.hpp"
#include "../../visitor/visitorCMultimediale.hpp"
#include <vector>

using std::vector;

class supportoMultimediale{
public:
    virtual vector<contenutoMultimediale*> getTracce() const = 0;
    virtual void setTracce(const vector<contenutoMultimediale*>) = 0;
    virtual void accept(visitorCMultimediale&) = 0;
};

#endif