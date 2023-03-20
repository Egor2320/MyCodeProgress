#include <iostream>
#include <vector>
#include <string>

class bigint{
private:
    bigint amb (bigint &a, const bigint &b){
        int carry = 0;
        const int base = 10;
        for (size_t i=0; i<b._digits.size() || carry; ++i) {
            a._digits[i] -= carry + (i < b._digits.size() ? b._digits[i] : 0);
            carry = a._digits[i] < 0;
            if (carry)  a._digits[i] += base;
        }
        while (a._digits.size() > 1 && a._digits.back() == 0)
            a._digits.pop_back();

        return a;
    }

    void side (int cycles){
        while (cycles) {
            int n = _digits.size();
            _digits.push_back(0);

            for (int i = n - 1; i >= 0; --i)
                _digits[i + 1] = _digits[i];

            _digits[0] = 0;
            --cycles;
        }
    }

    int to_int()const{
        int n = _digits.size();
        int res = 0, deg = 1;
        for(int i = 0; i < n; ++i){
            res += deg * _digits[i];
            deg *= 10;
        }
        if (!sign) res *= -1;
        return res;
    }

    bool abs (){
        bool res = sign;
        sign = true;
        return res;
    }



public:
    bigint(){
        _digits.push_back(0);
        sign = true;
    }

    explicit bigint(const int &a) {
        int i = a;
        sign = i < 0 ? false : true;
        if(i < 0) i *= -1;
        while(i){
            _digits.push_back(i % 10);
            i = i / 10;
        }
    }

    bigint (const bigint &other): sign(other.sign), _digits(other._digits){}

    explicit bigint(const std::string &s){
        std::string cpy = s;
        int start = 0, size = cpy.length();
        if (s[0] == '-'){
            sign = false;
            for (int i = 1; i < size; ++i){
                cpy[i-1] = cpy[i];
            }
            cpy.pop_back();
            size = cpy.length();
        }
        else
            sign = true;

        for (int i = start; i < size; ++i){
            _digits.push_back(cpy[size - i - 1] - '0');
        }
    }

    ~bigint() = default;

    bigint minus()const{
        bigint res = bigint(*this);
        res.sign = !res.sign;
        return res;
    }

    bool operator == (const bigint &other)const{
        size_t n = _digits.size();
        size_t m = other._digits.size();
        if(n != m) return false;
        for (size_t i = 0; i < n; ++i){
            if (_digits[i] != other._digits[i])
                return false;
        }
        return true;
    }
    bool operator==(const int &a)const{
        bigint tmp = bigint(a);
        return this->operator==(tmp);
    }

    bigint operator +()const{
        return *this;
    }

    bigint operator-()const{
        return (*this).minus();
    }

    bool operator != (const bigint &other)const{
        return !this->operator==(other);
    }

    bool operator != (const int &a)const{
        bigint tmp = bigint(a);
        return this->operator!=(tmp);
    }

    bool operator < (const bigint &other)const{
        if((*this) == other) return false;

        if(!this->sign && other.sign) return true;
        if(this->sign && !other.sign) return false;

        int n = _digits.size();
        int m = other._digits.size();
        bool res = true;
        if(n < m) res = true;
        else if (n > m) res = false;
        else{
            for (int i = n-1; i >= 0; ++i){
                if(_digits[i] < other._digits[i]){
                    res = true;
                    break;
                }
                else if(_digits[i] > other._digits[i]){
                    res = false;
                    break;
                }
            }
        }
        if(!sign && !other.sign) res = !res;
        return res;
    }

    bool operator < (const int &a)const{
        bigint tmp = bigint(a);
        return this->operator<(tmp);
    }

    bool operator > (const bigint &other)const{
        if(this->operator==(other)) return false;
        return !this->operator<(other);
    }

    bool operator > (const int &a)const{
        bigint tmp = bigint(a);
        return this->operator>(tmp);
    }

    bool operator <= (const bigint &other)const{
        return (this->operator==(other) || this->operator<(other));
    }

    bool operator <= (const int &a)const{
        bigint tmp = bigint(a);
        return this->operator<=(tmp);
    }

    bool operator >= (const bigint &other)const{
        return (this->operator==(other) || this->operator>(other));
    }

    bool operator >= (const int &a)const{
        bigint tmp = bigint(a);
        return this->operator>=(tmp);
    }


    bigint &operator -= (const bigint &a){
        return *this+=a.minus();
    }

    bigint &operator += (const bigint &a) {
        if (sign == a.sign) {
            int rem = 0;
            int n = _digits.size();
            int m = a._digits.size();
            if (n >= m) {
                for (int i = 0; i < m; ++i) {
                    _digits[i] += a._digits[i] + rem;
                    rem = _digits[i] / 10;
                    _digits[i] = _digits[i] % 10;
                }
                for (int i = m; i < n; ++i) {
                    _digits[i] += rem;
                    rem = _digits[i] / 10;
                    _digits[i] %= 10;
                }
                if (rem) _digits.push_back(rem);
            }
            else {
                for (int i = 0; i < n; ++i) {
                    _digits[i] += a._digits[i] + rem;
                    rem = _digits[i] / 10;
                    _digits[i] = _digits[i] % 10;
                }
                for (int i = n; i < m; ++i) {
                    int res = a._digits[i] + rem;
                    rem = res / 10;
                    _digits.push_back(res % 10);
                }
            	if (rem) _digits.push_back(rem);
            }
        }

        else{
            bigint tmp = bigint(a);
            bool s1 = abs();
            bool s2 = tmp.abs();

            if(*this >= tmp){
                *this = amb(*this, tmp);
                this->sign = s1;
            }

            else{
                *this = amb(tmp, *this);
                this->sign = s2;
            }
        }
    	if (this->to_int() == 0) sign = true;

        return *this;
    }

    bigint &operator +=(const int &a){
        bigint tmp = bigint(a);
        (*this)+=tmp;
        return *this;
    }

    bigint &operator -=(const int &a){
        bigint tmp = bigint(a);
        (*this)-=tmp;
        return *this;    }

    bigint &operator *=(const int &a){
        bigint tmp = bigint(a);
        (*this)*=tmp;
        return *this;
    }

    bigint &operator ++(){
        bigint tmp = bigint(1);
        return (*this)+=tmp;
    }
    const bigint operator ++(int){
        bigint res = bigint(*this);
        bigint tmp = bigint(1);
        *this += tmp;
        return res;
    }

    bigint &operator --(){
        bigint tmp = bigint(1);
        return (*this)-=tmp;
    }
    const bigint operator --(int){
        bigint res = bigint(*this);
        bigint tmp = bigint(1);
        *this -= tmp;
        return res;
    }

    bigint &operator = (const bigint &a){
        _digits = a._digits;
        sign = a.sign;
        return *this;
    }

    bigint &operator *= (const bigint &a) {
        if(this->to_int() == 0 || a.to_int() == 0){
            (*this) = bigint();
            return *this;
        }
        const int base = 10;
    	int rem = 0;
        bigint res = bigint();
        int n = _digits.size(), m = a._digits.size();
        res._digits.resize(n+m);
        bool prev = sign;

        for (size_t i=0; i<n; ++i)
            for (int j=0, rem=0; j<m || rem; ++j) {
                long long cur = res._digits[i+j] + _digits[i] * 1ll * (j < m ? a._digits[j] : 0) + rem;
                res._digits[i+j] = int (cur % base);
                rem = int (cur / base);
            }
        while (res._digits.size() > 1 && res._digits.back() == 0)
            res._digits.pop_back();

        *this = res;
        if (prev == a.sign)
            sign = true;
        else
            sign = false;

        return *this;
    }

    explicit operator bool() const{
        if(this->to_int() == 0) return false;
        else return true;
    }

    std::string to_string()const{
        int n = _digits.size();
        std::string res;
        if(!sign) res.push_back('-');
        for (int i = n-1; i >= 0; --i){
            res.push_back(_digits[i] + '0');
        }
        return res;
    }

    std::vector<int> _digits;
    bool sign = true;

};

std::ostream &operator<<(std::ostream &os, const bigint &a){
    os << a.to_string();
    return os;
}

std::istream &operator>> (std::istream &is, bigint &a){
    std::string s;
    is>>s;
    int sz = s.size();
    int i = 0;
    if(s[0] == '-'){
        a.sign = false;
        ++i;
        --sz;
    }

    a._digits.resize(sz);
    for (int k = 0; k < sz; ++k) {
        a._digits[sz - 1 - k] = s[i] - '0';
        ++i;
    }
    return is;
}

bigint operator + (const bigint &a, const bigint &b){
    bigint c = bigint(a);
    return c+=b;
}

bigint operator * (const bigint &a, const bigint &b){
    bigint c = bigint(a);
    return c*=b;
}

bigint operator - (const bigint &a, const bigint &b){
    bigint c = b.minus();
    bigint d = bigint(a);
    return d+=c;
}

bool operator == (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a == tmp;
}

bool operator != (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a != tmp;
}

bool operator < (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a < tmp;
}

bool operator > (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a > tmp;
}

bool operator <= (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a <= tmp;
}

bool operator >= (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    return a >= tmp;
}

bigint operator + (const bigint &a, const int &b){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1+=tmp;
}

bigint operator + (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1+=tmp;
}

bigint operator - (const bigint &a, const int &b){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1-=tmp;
}

bigint operator - (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1-=tmp;
}

bigint operator * (const bigint &a, const int &b){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1*=tmp;
}

bigint operator * (const int &b, const bigint &a){
    bigint tmp = bigint(b);
    bigint tmp1 = bigint(a);
    return tmp1*=tmp;
}

int main(){
    return 0;
}