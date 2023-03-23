#include "matrixWithLabel.hpp"

const std::string& MatrixWithLabel::getLabel() const
{
    return this->label;
}

void MatrixWithLabel::setLabel(const std::string& label)
{
    this->label = label;
}