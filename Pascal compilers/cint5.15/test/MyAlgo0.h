// MyAlgo0.h

#if defined(__GNUC__) && (__GNUC__>=3)
#include <iostream>
using namespace std;
#else
#include <iostream.h>
#endif

// �R���e�i���̑S�v�f��\������A���S���Y��
template<class InputIter> 
void Disp(InputIter first,InputIter last)
{
  while(first!=last) cout << *first++ << " " ;
  cout << endl;
}

// �R���e�i���̑S�v�f�̑��a�����߂�A���S���Y��
template<class T,class InputIter> 
T Sum(InputIter first,InputIter last,const T initval)
{
  T sum = initval;
  while(first!=last) sum += *first++ ;
  return(sum);
}
