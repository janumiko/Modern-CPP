#include <iostream>
//-------------------------------------------
/// ADD FORWARD DECLARATIONS HERE
template <typename T, typename S> class Pair;

template <typename T, typename S> std::ostream &operator<<(std::ostream &, const Pair<T, S> &);

//-------------------------------------------
// DO NOT CHANGE CLASS Pair
template <typename T, typename S> class Pair
{
  private:
    const T first;
    const S second;
    static int numberOfPairs;

  public:
    Pair(T first, S second); // Constructor, increases numberOfPairs
    template <typename P, typename R>
    explicit Pair(const Pair<P, R> &pair);   // Converting constructor, increases numberOfPairs
    ~Pair();                                 // Destructor, decreases numberOfPairs
    constexpr T getFirst() const;            // returns first, mark it inline
    constexpr S getSecond() const;           // returns second, mark it inline
    constexpr Pair<S, T> reverse() const;    // returns a reversed Pair
    constexpr static int getNumberOfPairs(); // return the number of existing objects of Pair<T,S>
    // friend declaration with single template function operator<<(std::ostream, const Pair<T,S> &)
    friend std::ostream &operator<< <>(std::ostream &out, const Pair &pair);

    // friend declaration with class template (any Pair<P,R>)
    template <typename, typename> friend class Pair;
};
//-------------------------------------------
/// IMPLEMENTATION SECTION: Implement methods here
template <typename T, typename S> int Pair<T, S>::numberOfPairs;

template <typename T, typename S> Pair<T, S>::Pair(T f, S s) : first(f), second(s)
{
    Pair<T, S>::numberOfPairs++;
}

template <typename T, typename S>
template <typename P, typename R>
Pair<T, S>::Pair(const Pair<P, R> &pair) : first(pair.first), second(pair.second)
{
    Pair<T, S>::numberOfPairs++;
}

template <typename T, typename S> Pair<T, S>::~Pair()
{
    Pair<T, S>::numberOfPairs--;
}

template <typename T, typename S> inline constexpr T Pair<T, S>::getFirst() const
{
    return this->first;
}

template <typename T, typename S> inline constexpr S Pair<T, S>::getSecond() const
{
    return this->second;
}

template <typename T, typename S> constexpr Pair<S, T> Pair<T, S>::reverse() const
{
    return Pair<S, T>(this->getSecond(), this->getFirst());
}

template <typename T, typename S> constexpr int Pair<T, S>::getNumberOfPairs()
{
    return Pair<T, S>::numberOfPairs;
}

template <typename T, typename S> std::ostream &operator<<(std::ostream &out, const Pair<T, S> &pair)
{
    out << "(" << pair.getFirst() << ", " << pair.getSecond() << ")";
    return out;
}

//-------------------------------------------
using namespace std;
int main()
{
    Pair<int, double> p{1, 3.1415};
    cout << p.getFirst() << " " << p.getSecond() << endl;
    cout << p << endl;
    auto p2 = p.reverse();
    cout << p2 << endl;
    {
        Pair<int, int> p3(p);
        cout << p3 << endl;
        cout << Pair<int, int>::getNumberOfPairs() << endl;
    }
    cout << Pair<int, int>::getNumberOfPairs() << endl;
}
/** Expected output
1 3.1415
(1, 3.1415)
(3.1415, 1)
(1, 3)
1
0
 */