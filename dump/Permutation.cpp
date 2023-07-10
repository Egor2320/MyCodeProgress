#include <iostream>
#include <vector>
void swap(unsigned &a, unsigned &b){
    a ^= b;
    b ^= a;
    a ^= b;
}

template <size_t n>
class permutation{
    std::vector<unsigned> per;

public:
    permutation(){
        for (int i = 0; i < n; ++i){
            per.push_back(i);
        }
    }
    explicit permutation(unsigned *array){
        for (int i = 0; i < n; ++i){
            per.push_back(array[i]);
        }
    }

    permutation(const permutation &other){
        per = other.per;
    }

    ~permutation() = default;

    void operator()(unsigned *values) const{
        unsigned t[n];
        for (int i = 0; i < n; ++i){
            t[i] = values[i];
        }
        for (int i = 0; i < n; ++i){
            values[per[i]] = t[i];
        }
    }


    const unsigned &operator[](int i)const{
        return per[i];
    }

    permutation inverse()const{
        permutation tmp = permutation(*this);
        for (int i = 0; i < n; ++i){
            tmp.per[per[i]] = i;
        }
        return tmp;
    }

    permutation &operator = (const permutation &other){
        per.clear();
        per = other.per;
        return  *this;
    }

    permutation &operator *= (const permutation &other){
        permutation tmp = permutation(*this);
        for (int i = 0; i < n; ++i){
            per[i] = tmp.per[other.per[i]];
        }
        return *this;
    }

    bool operator< (const permutation &other)const {
        if((*this) == other) return false;
        int i = 0;
        while(per[i] == other.per[i]) ++i;

        if(per[i] < other.per[i]) return true;
        else return false;

    }

    bool operator> (const permutation &other)const{
        if((*this) == other) return false;
        return !(operator<(other));
    }

    bool operator== (const permutation & other)const{
        int i = 0;
        while (i < n){
            if (per[i] != other.per[i]) return false;
            ++i;
        }
        return true;
    }

    bool operator!= (const permutation & other)const{
        return !(operator==(other));
    }

    bool operator<= (const permutation &other)const{
        return ((operator<(other)) || operator==(other));
    }

    bool operator >= (const permutation &other)const{
        return ((operator>(other)) || operator==(other));
    }

    permutation next()const{
        int idx1 = -1, idx2 = -1;
        permutation tmp = permutation(*this);
        for (int i = n-2; i >= 0; --i){
            if(per[i] < per[i + 1]){
                idx1 = i;
                break;
            }
        }
        if (idx1 == -1){
            for (int i = 0; i < n/2; ++i){
                swap(tmp.per[i], tmp.per[n-1-i]);
            }
            return tmp;
        }

        for (int i = n-1; i >= 0; --i){
            if(per[i] > per[idx1]){
                idx2 = i;
                break;
            }
        }
        swap(tmp.per[idx1], tmp.per[idx2]);
        int sz = n-1;
        idx1++;
        while (idx1 < sz){
            swap(tmp.per[idx1], tmp.per[sz]);
            idx1++;
            --sz;
        }
        return tmp;
    }

    permutation prev()const{
        int idx1 = -1, idx2 = -1;
        permutation tmp = permutation(*this);
        for (int i = n-2; i >= 0; --i){
            if(per[i] > per[i + 1]){
                idx1 = i;
                break;
            }
        }
        if (idx1 == -1){
            for (int i = 0; i < n/2; ++i){
                swap(tmp.per[i], tmp.per[n-1-i]);
            }
            return tmp;
        }

        for (int i = n-1; i >= 0; --i){
            if(per[i] < per[idx1]){
                idx2 = i;
                break;
            }
        }
        swap(tmp.per[idx1], tmp.per[idx2]);
        int sz = n-1;
        idx1++;
        while (idx1 < sz){
            swap(tmp.per[idx1], tmp.per[sz]);
            idx1++;
            --sz;
        }
        return tmp;
    }

    permutation &operator++(){
        *this = (*this).next();
        return *this;
    }

    const permutation operator++(int){
        permutation tmp = permutation(*this);
        *this = (*this).next();
        return tmp;
    }

    const permutation operator--(int){
        permutation tmp = permutation(*this);
        *this = (*this).prev();
        return tmp;
    }

    permutation &operator--(){
        *this = (*this).prev();
        return *this;
    }

    void printper(){
        for (int i = 0; i < n; ++i){
            std::cout << i << ':' << per[i] << ' ';
        }
        std::cout << '\n';
    }

};

template <size_t n>
permutation<n> operator * (const permutation<n> &a, const permutation<n> &b){
    permutation tmp = permutation(a);
    return tmp *= b;
}
