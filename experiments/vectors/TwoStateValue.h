#ifndef TWO_STATE_VALUE_H_INCLUDED
#define TWO_STATE_VALUE_H_INCLUDED

template<typename T>
class TwoStateValue
{
private:
T val1, val2;
T* p;
T* p_new;

public:
TwoStateValue():val1(), val2(), p(&val1), p_new(&val2)
{
}


TwoStateValue(const T& initial):
val1(initial), val2(initial), p(&val1), p_new(&val2)
{
}

void operator=(const T& val)
{
   *p_new = val;
}

void operator+=(const T& val)
{
   *p_new += val;
}
void operator-=(const T& val)
{
   *p_new -= val;
}

const T& operator()() const
{
	return *p;
}

const T& value() const
{
	return *p;
}

T& direct_access_to_new_value()
{
	return *p_new;
}



void commit()
{
   T* tmp = p_new;
   p_new = p;
   p = tmp;
}

};


#endif

