#include "BigInteger.h"
int main()
{
    BigInteger a(3334433444);
    BigInteger b(500,1);
    BigInteger resu = a*b;
    cout<< resu << endl;
    // if(a < b)
    // {
    //     cout << "a < b";
    // }
    // else
    //     cout << "a >= b";
    // neu khong nap chong phep gan
    // sau khi thuc hien phep con, ket qua luu vao finalresult(hoac result neu a[0] ==1), return ve thi finalresult(hoac result) se gan vao mot bien ko ten, sau do xoa luon finalresult va result
    // dong thoi xoa luon bien tam ko ten do
    // neu co nap chong phep gan
    //no se tao ra bien tam ko ten xong gan result hoac finalresult cho bien do truoc, roi xoa result va final result, sau do bien tam khong ten
    // nay lai gan cho resu ham main bang ham nap chong = , sau do xoa luon bien tam khong ten nay
    // char *a  = new char;
    // a[0] = '\0';
    // cout << strlen(a);
    // if(a < b)
    // {
    //     cout << "a < b";
    // }
    // else
    //     cout << "a >= b";
}