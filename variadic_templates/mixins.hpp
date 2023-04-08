#ifndef MIXINS_HPP
#define MIXINS_HPP

template <typename... Types> class Mixins : public Types...
{
  public:
    Mixins(Types... types) : Types(types)...
    {
    }
};

#endif