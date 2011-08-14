#ifndef FIND_END_TYPE_H_INCLUDED
#define FIND_END_TYPE_H_INCLUDED
namespace se
{
  namespace utils
  {
    template < typename T > struct find_end_type
    {
      typedef T value_type;
    };

    template < typename T, template < typename > class CLASS >
    struct find_end_type <CLASS < T > > : public find_end_type < T >
    {
    };

  }
}
#endif
