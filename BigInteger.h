#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class BigInteger
{
private:
    char *a;
    bool sign;
public:
    BigInteger()
    {
        a= new char;
        a[0] = '\0';
        sign = true;
    }
    BigInteger(const BigInteger &b)
    {
        this->sign = b.sign;
        this->a = new char[b.getNdigit()+1];
        strcpy(this->a,b.a);
    }
    BigInteger(BigInteger &&b)
    {
        // cout << this << endl;
        // cout << &b << endl;
        if(b.a != NULL)
        {
           this->sign = b.sign;
            this->a = b.a;
            b.a = NULL;
        }
    }
    BigInteger& operator=(const BigInteger& b)
    {
        if(this != &b)
        {
            if(this->a != NULL)
            {
                delete[] this->a;
            }
            this->sign = b.sign;
            this->a = new char[b.getNdigit()+1];
            strcpy(this->a,b.a);
        }
        return *this;
    }
    BigInteger& operator=(BigInteger&& b)
    {
        if(this != &b && b.a != NULL)
        {
            // cout << this << endl;
            if(this->a != NULL)
            {
                delete[] this->a;
            }
            this->sign = b.sign;
            this->a = b.a;
            b.a = NULL;
        }
        return *this;
    }
    BigInteger(const long long &b)
    {
        a = NULL;
        if(b == 0)
        {
            a = new char[2];
            a[1] = '\0';
            a[0] = '0';
            sign = true;
            return;
        }
        if(b > 0) sign = true;
        else sign = false;
        long long temp = abs(b);
        long long Ndigit = 0;
        while(temp > 0)
        {
            Ndigit+=1;
            temp/=10;
        }
        temp = abs(b);
        a = new char[Ndigit+1];
        a[Ndigit] = '\0';
        while(temp > 0)
        {
            a[Ndigit-1] = temp %10 + 48; 
            Ndigit--;
            temp/=10;
        }
    }
    BigInteger(const int &N,const short &b, bool sig = true) : sign(sig)
    {
        a = NULL;
        try
        {
            if(N < 0 || b < 0 || b > 9 || N > 1000)
            {
                throw "error input";
            }
            if(b == 0)
            {
                a = new char[2];
                a[1] = '\0';
                a[0] = '0';
                return;
            }
            a = new char[N+1];
            a[N] = '\0';
            for (int i = 0; i < N; i++)
            {
                a[i] = b+48;
            }
        }
        catch(const char* c)
        {
            cout << c << endl;
        }
    }
    BigInteger operator+(const BigInteger & b)
    {
        BigInteger result;
        delete[] result.a;
        result.a = NULL;
        if(this->sign == b.sign)
        {
            result.sign = this->sign;
        }
        else
        {
            if(this->sign == false && b.sign == true)
            {
                result = b.ABS() - this->ABS();
                return result;
            }
            if(this->sign == true && b.sign == false)
            {
                result = this->ABS() - b.ABS();
                return result;
            }
        }
        short Nthis = this->getNdigit();
        short Nb = b.getNdigit();
        short Nresult = (Nthis > Nb) ? Nthis : Nb;
        result.a = new char[Nresult+2];
        result.a[Nresult+1] = '\0';
        short carry = 0;
        short digi = 0;
        for (int i = Nresult; i > 0; i--)
        {
            digi = 0;
            if(Nthis > 0)
            {
                digi += this->a[Nthis-1]-48;
            }
            if(Nb > 0)
            {
                digi += b.a[Nb-1]-48;
            }
            digi += carry;
            if(digi >= 10)
            {
                digi=digi%10;
                carry = 1;
            }
            else carry = 0;
            result.a[i] = digi+48;
            // cout << digi;
            Nthis--;
            Nb--;
        }
        if(carry == 1) result.a[0] = 49;
        else result.a[0] = 48;
        // cout << &result << endl;
        if(result.a[0] == 48)
        {
            BigInteger Finalresult;
            // cout << &Finalresult << endl;
            short NFinal = result.getNdigit();
            Finalresult.a = new char[NFinal];
            for (int i = 0; i < NFinal; i++)
            {
                Finalresult.a[i] =  result.a[i+1];
            }
            Finalresult.sign = result.sign;
            return Finalresult;
        }
        return result;
    }
    BigInteger operator+(const long long& c)
    {
        BigInteger ctemp(c);
        // cout << &ctemp << endl;
        return *this + ctemp;
    }
    BigInteger operator-(const long long& c)
    {
        BigInteger ctemp(c);
        return *this - ctemp;
    }
    friend BigInteger operator+(const long long& c, BigInteger &b)
    {
        BigInteger ctemp(c);
        // cout << &ctemp << endl;
        return b + ctemp;
    }
    friend BigInteger operator-(const long long& c, BigInteger &b)
    {
        BigInteger ctemp(c);
        // cout << &ctemp << endl;
        return ctemp-b;
    }
    BigInteger operator*(const BigInteger & b)
    {
        BigInteger result;
        delete[] result.a;
        result.a = NULL;
        if(this->a[0] == 48 || b.a[0] == 48)
        {
            result.a = new char[2];
            result.a[1] = '\0';
            result.a[0] = '0';
            result.sign = true;
            return result;
        }
        if(this->sign != b.sign)result.sign = false;
        else result.sign = true;
        short Nthis = this->getNdigit();
        short Nb = b.getNdigit();
        short Nresult = Nthis+Nb;
        result.a = new char[Nresult+1];
        result.a[Nresult] = '\0';
        for (int i = 0; i < Nresult; i++)
        {
            result.a[i] = 48;
        }
        short carry = 0;
        short carry1 = 0;
        short multi = 0;
        short sum = 0;
        short k = Nresult-1;
        for (short i = Nb-1; i >= 0; i--)
        {
            k = Nresult - 1 -(Nb-1-i);
            carry1 = 0;
            carry = 0;
            for (short j = Nthis-1; j >= 0; j--)
            {
                multi = (this->a[j]-48)*(b.a[i]-48) + carry;
                // cout << this->a[j]<< endl;
                if(multi >= 10)
                {
                    carry = multi/10;
                    multi = multi%10;
                }
                else carry = 0;
                sum = result.a[k]-48 + multi + carry1;
                // cout << sum << endl;
                if(sum >= 10)
                {
                    carry1 = 1;
                    sum = sum%10;
                }
                else carry1 = 0;
                result.a[k] = sum + 48;
                // cout << sum << endl;
                k--;
            }
            // cout << result << endl;
            if(carry != 0)
            {
                result.a[k] = 0 + carry+carry1 + 48;
            }
            // cout << result << endl;
        }
        // cout << result << endl;
        if(result.a[0] == 48)
        {
            short Num0 = 0;
            while(result.a[Num0] == 48)
            {
                Num0++;
            }
            BigInteger Finalresult;
            // cout << &Finalresult << endl;
            short NFinal = result.getNdigit()-Num0+1;
            Finalresult.a = new char[NFinal];
            for (int i = 0; i < NFinal; i++)
            {
                Finalresult.a[i] =  result.a[i+Num0];
            }
            Finalresult.sign = result.sign;
            return Finalresult;
        }
        return result;
    }
    BigInteger& operator ++()
    {
        if(this->a != NULL || this->getNdigit() >= 1)
            *this = *this + 1;
        return *this;
    }
    BigInteger operator++(int a)
    {
        BigInteger temp = *this;
        ++(*this);
        return temp;
    }
    BigInteger operator*(const long long &b)
    {
        BigInteger btemp(b);
        return btemp*(*this);
    }
    friend BigInteger operator*(const long long &b,const BigInteger &c)
    {
        BigInteger btemp(b);
        return btemp*c;
    }
    char& operator[](int index)
    {
        try
        {
            int Nthis = this->getNdigit();
            if(index < 0 && abs(index) <  Nthis + 1)
            {
                index = Nthis + index;
                return this->a[index];
            }
            else if(index > Nthis &&  index < 2*Nthis)
            {
                index = index - Nthis;
                return this->a[index];
            }
            else if(index <0 || index > Nthis)
                throw "error input";
        }
        catch(const char * c)
        {
            cout << c << endl;
        }
        return this->a[index];
    }
    BigInteger ABS() const
    {
        BigInteger result;
        delete[] result.a;
        result.a = NULL;
        result.sign = true;
        result.a = new char[this->getNdigit()+1];
        strcpy(result.a,this->a);
        return result;
    }
    BigInteger operator-(const BigInteger & b)
    {
        BigInteger result;
        delete[] result.a;
        result.a = NULL;
        if(*this == b)
        {
            result.a = new char[2];
            result.a[1] = '\0';
            result.a[0] = '0';
            result.sign = true;
            return result;
        }
        if(this->sign != b.sign)
        {
            result = this->ABS() + b.ABS();
            result.sign = this->sign;
            return result;
        }
        else{
            if(this->sign == false)
            {
                result = b.ABS() - this->ABS();
                
                return result;
            }
        }
        bool checkGreater = true;
        result.sign = true;
        if(*this < b)
        {
            checkGreater = false;
            result.sign = false;
        }
        short Nthis = this->getNdigit();
        short Nb = b.getNdigit();
        short Nresult = (Nthis > Nb) ? Nthis : Nb;
        result.a = new char[Nresult+1];
        result.a[Nresult] = '\0';
        short carry = 0;
        short digi = 0;
        for (int i = Nresult-1; i >= 0; i--)
        {
            digi = 0;
            if(Nthis > 0)
            {
                if(checkGreater) digi += this->a[Nthis-1]-48;
                else digi -= this->a[Nthis-1]-48;
            }
            if(Nb > 0)
            {
                if(!checkGreater) digi += b.a[Nb-1]-48;
                else digi -= b.a[Nb-1]-48;
            }
            digi -= carry;
            if(digi < 0)
            {
                digi+=10;
                carry = 1;
            }
            else carry = 0;
            result.a[i] = digi+48;
            Nthis--;
            Nb--;
        }
        if(result.a[0] == 48)
        {
            int Num0 = 0;
            while(result.a[Num0] == 48)
            {
                Num0++;
            }
            BigInteger Finalresult;
            // cout << &Finalresult << endl;
            short NFinal = result.getNdigit()-Num0+1;
            Finalresult.a = new char[NFinal];
            for (int i = 0; i < NFinal; i++)
            {
                Finalresult.a[i] =  result.a[i+Num0];
            }
            Finalresult.sign = result.sign;
            return Finalresult;
        }
        return result;
    }
    bool operator<(const long long &b)
    {
        
    }
    bool operator<(const BigInteger&b)
    {
        if(this->sign == false && b.sign == true)
        {
            return true;
        }
        else if(this->sign == b.sign)
        {
            short thisN = this->getNdigit();
            short bN = b.getNdigit();
            if((thisN < bN && this->sign == true)||(thisN > bN && this->sign == false))
            {
                return true;
            }
            else if(thisN == bN)
            {
                for (int i = 0; i < thisN; i++)
                {
                    if((this->a[i] < b.a[i] && this->sign == true) || (this->a[i] > b.a[i] && this->sign == false))
                    {
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
        }
        return false;
    }
    bool operator==(const BigInteger&b)
    {
        if(this->sign != b.sign)return false;
        short thisN = this->getNdigit();
        short bN = b.getNdigit();
        if(thisN != bN)
        {
            return false;
        }
        else{
            for (int i = 0; i < thisN; i++)
            {
                if(this->a[i] != b.a[i])
                {
                    return false;
                }
            }
        }
        return true;
    }
    friend bool lessABSvalue(const BigInteger&a, const BigInteger&b)
    {
        short aN = a.getNdigit();
        short bN = b.getNdigit();
        if(aN < bN)
        {
            return true;
        }
        else if(aN == bN)
        {
            for (int i = 0; i < aN; i++)
            {
                if(a.a[i] < b.a[i])
                {
                    return true;
                }
            }
        }
        return false;
    }
    short getNdigit() const
    {
        if(a != NULL)
        {
            return strlen(a);
        }
        return 0;
    }
    friend ostream& operator<<(ostream& out,const BigInteger& b)
    {
        if(b.a != NULL)
            out <<((b.sign == false) ? "-" : "")<<b.a;
        return out;
    }
    ~BigInteger()
    {
        // cout << this << endl;
        if(a != NULL)
            delete[] a;
    }
};
