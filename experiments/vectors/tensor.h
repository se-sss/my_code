#ifndef TENSOR_H_INCLUDED
#define TENSOR_H_INCLUDED

template <int RANK, int DIM, typename TYPE>
class matrix;

template <int RANK>
class matrix_index;


template <int RANK, int DIM, typename TYPE>
class matrix<RANK, DIM, TYPE>
{
private:
    matrix<RANK-1, DIM, TYPE> data[DIM];

public:

   typedef int matrix_index_array[RANK];

   matrix<RANK-1, DIM, TYPE>&  operator[](int index)
   {
	   return data[index];
   }

   TYPE&  operator[](matrix_index_array index)
   {
	   return data[index];
   }

};

template <int RANK>
class matrix_index
{
private:
    int index;
	matrix_index<RANK-1> next;

};

template <>
class matrix_index<0>
{
};



template<int DIM, typename TYPE>
class matrix<1, DIM, TYPE>
{private:
    TYPE data[DIM];

public:
    TYPE& operator[](int index)
    {
	return data[index];
    }
};

enum tensor_index_type
{	
	COVARIANT,
	CONTRAVARIANT		
};


template <int RANK, int DIM, typename TYPE>
class tensor;

template <int RANK, int DIM, typename TYPE>
class tensor
{
private:
matrix<RANK, DIM, TYPE> data;
tensor_index_type index_type_array[RANK];

};

template <int DIM, typename TYPE>
class tensor<0, DIM, TYPE>
{
private:
TYPE data;
};

template<int RANK1, int RANK2, int DIM, typename TYPE>
tensor<RANK1 + RANK2, DIM, TYPE>
operator* (     const tensor<RANK1, DIM, TYPE>& t1,
		const tensor<RANK2, DIM, TYPE>& t2)
{
	tensor<RANK1 + RANK2, DIM, TYPE> t;
	return t;
}

template<int RANK2, int DIM, typename TYPE>
tensor<RANK2, DIM, TYPE>
operator* (     const tensor<0, DIM, TYPE>& t1,
		const tensor<RANK2, DIM, TYPE>& t2)
{
	tensor<RANK2, DIM, TYPE> t;
	return t;
}

template<int RANK1, int DIM, typename TYPE>
tensor<RANK1, DIM, TYPE>
operator* (     const tensor<RANK1, DIM, TYPE>& t1,
		const tensor<0, DIM, TYPE>& t2)
{
	tensor<RANK1, DIM, TYPE> t;
	return t;
}

template<int DIM, typename TYPE>
tensor<0, DIM, TYPE>
operator* (     const tensor<0, DIM, TYPE>& t1,
		const tensor<0, DIM, TYPE>& t2)
{
	tensor<0, DIM, TYPE> t;
	t.data = t1.data * t2.data;
	return t;
}

#endif

