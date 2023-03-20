#include<iostream>
#include <vector>
#include<utility>
template<typename T>
class bucket_allocator{
public:
    using value_type = T;
    bucket_allocator(){
        buff_size = threshold_size;
    }

    bucket_allocator(const size_t &thr_size){
        buff_size = thr_size;
    }

    bucket_allocator(const bucket_allocator &other) = delete;
    bucket_allocator &operator=(const bucket_allocator &other) = delete;
    ~bucket_allocator() = default;

    T* allocate(const size_t &n){
        if(n > buff_size) {
            bucket b_new;
            b_new.size = n;
            b_new.buff = ::operator new[](sizeof(T) * n);
            b_new.all_obj = n;
            b_new.deall_obj = 0;
            T* res = static_cast<T*>(b_new.buff);
            buck.push_back(std::move(b_new));
            return res;
        }

        else{
            size_t len = buck.size();
            for(size_t i = 0; i < len; ++i){
                if(buck[i].size - buck[i].all_obj >= n){
                    size_t s = buck[i].all_obj;
                    buck[i].all_obj += n;
                    return static_cast<T*>(buck[i].buff) + s;
                }
            }
            bucket b_new;
            b_new.size = buff_size;
            b_new.buff = ::operator new[](sizeof(T) * buff_size);
            b_new.all_obj = n;
            b_new.deall_obj = 0;
            T* res = static_cast<T*>(b_new.buff);
            buck.push_back(std::move(b_new));
            return res;
        }
    }

    void deallocate(T* ptr, size_t n){
        size_t len = buck.size();
        for (size_t i = 0; i < len; ++i){
            T *start = static_cast<T*>(buck[i].buff);
            for(size_t j = 0; j < buck[i].all_obj; ++j) {
                if (ptr == start + j) {
                    buck[i].deall_obj += n;
                    if (buck[i].deall_obj == buck[i].all_obj) {
                        ::operator delete[](static_cast<T *>(buck[i].buff));
                        buck.erase(buck.begin() + i);
                    }
                }
            }
        }
    }
private:
    struct bucket{
        void *buff;
        size_t size, all_obj, deall_obj;
    };
    const size_t threshold_size = 1024;
    size_t buff_size;
    std::vector<bucket>buck;
};

int main(){
    return 0;
}