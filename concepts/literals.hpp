#ifndef LITERALS_HPP
#define LITERALS_HPP

long double operator"" _m(unsigned long long int distance)
{
    return distance;
};

long double operator"" _m(long double distance)
{
    return distance;
};

long double operator"" _km(unsigned long long int distance)
{
    return distance * 1000;
};

long double operator"" _km(long double distance)
{
    return distance * 1000;
};

long double operator"" _cm(unsigned long long int distance)
{
    return (long double)distance / 100;
};

long double operator"" _cm(long double distance)
{
    return distance / 100;
};

long double operator"" _s(unsigned long long int time)
{
    return time;
};

long double operator"" _s(long double time)
{
    return time;
};

long double operator"" _ms(unsigned long long int time)
{
    return time / 1000;
};

long double operator"" _ms(long double time)
{
    return (long double)time / 1000;
};

long double operator"" _h(unsigned long long int time)
{
    return time * 3600;
};

long double operator"" _h(long double time)
{
    return time * 3600;
};

#endif // LITERALS_HPP