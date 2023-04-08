#ifndef PROXY_HPP
#define PROXY_HPP

#include <iostream>

template <typename... Args> void showNames(Args... args)
{
    int counter = 0;
    ((std::cout << ++counter << " > "
                << "[" << typeid(args).name() << "]"
                << " = " << args << std::endl),
     ...);
}

template <typename F> class Proxy
{
  private:
    F _functor;

  public:
    Proxy(F f) : _functor(f)
    {
    }

    template <typename... Args> auto operator()(Args &&...args)
    {
        std::cout << std::endl << "Proxy" << std::endl;
        showNames(std::forward<Args>(args)...);
        return _functor(std::forward<Args>(args)...);
    }
};

#endif