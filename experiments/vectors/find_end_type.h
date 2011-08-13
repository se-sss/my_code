#ifndef FIND_END_TYPE_H_INCLUDED
#define FIND_END_TYPE_H_INCLUDED

/*
find_end_type<
 Type1<Type2<Type3<...TypeN<NonTemplateClass> ...> >
  >::value_type is NonTemplateClass.

find_end_type<NonTemplateClass>::value_type
is NonTemplateClass
*/

template < typename T > struct find_end_type
{
  typedef T value_type;
};

template < typename T, template < typename > class TemplateT >
  struct find_end_type <TemplateT < T > >:find_end_type < T >
{
};

#endif
