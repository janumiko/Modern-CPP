#ifndef VECTOR_OPERATORS_HPP
#define VECTOR_OPERATORS_HPP

#include <iostream>

template <int N> class Vector
{
    int data[N];

  public:
    Vector()
    {
        std::cout << " Default constr" << std::endl;
    }

    Vector(std::initializer_list<int> list)
    {
        std::cout << " Init list constr" << std::endl;
        auto it = list.begin();
        for (int i = 0; i < N; i++)
        {
            data[i] = *it++;
        }
    }
    Vector(const Vector &m)
    {
        std::copy(m.data, m.data + N, data);
        std::cout << " Copy constr" << std::endl;
    }
    int operator[](int index) const
    {
        return data[index];
    }
    int &operator[](int index)
    {
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &m)
    {
        for (auto x : m.data)
        {
            std::cout << x << ", ";
        }
        return out;
    }
};

template <typename Left, typename Right> class Node
{
  protected:
    const Left &left;
    const Right &right;

  public:
    Node(Left &&l, Right &&r) : left(std::forward<Left>(l)), right(std::forward<Right>(r))
    {
    }

    virtual int operator[](int index) const = 0;

    template <int N> operator Vector<N>()
    {
        Vector<N> result;
        for (int i = 0; i < N; i++)
        {
            result[i] = (*this)[i];
        }
        return result;
    }
};

template <typename Left, typename Right> class AdditionNode : public Node<Left, Right>
{
  public:
    AdditionNode(Left &&l, Right &&r) : Node<Left, Right>(std::forward<Left>(l), std::forward<Right>(r))
    {
    }

    int operator[](int index) const override
    {
        return this->left[index] + this->right[index];
    }
};

template <typename Left, typename Right> class SubtractionNode : public Node<Left, Right>
{
  public:
    SubtractionNode(Left &&l, Right &&r) : Node<Left, Right>(std::forward<Left>(l), std::forward<Right>(r))
    {
    }

    int operator[](int index) const override
    {
        return this->left[index] - this->right[index];
    }
};

template <typename Left, typename Right> class MultiplicationNode : public Node<Left, Right>
{
  public:
    MultiplicationNode(Left &&l, Right &&r) : Node<Left, Right>(std::forward<Left>(l), std::forward<Right>(r))
    {
    }

    int operator[](int index) const override
    {
        return this->left * this->right[index];
    }
};

template <typename Left, typename Right> AdditionNode<Left, Right> operator+(Left &&l, Right &&r)
{
    return AdditionNode<Left, Right>(std::forward<Left>(l), std::forward<Right>(r));
}

template <typename Left, typename Right> SubtractionNode<Left, Right> operator-(Left &&l, Right &&r)
{
    return SubtractionNode<Left, Right>(std::forward<Left>(l), std::forward<Right>(r));
}

template <typename Left, typename Right> MultiplicationNode<Left, Right> operator*(Left &&l, Right &&r)
{
    return MultiplicationNode<Left, Right>(std::forward<Left>(l), std::forward<Right>(r));
}

#endif // VECTOR_OPERATORS_HPP