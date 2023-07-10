#include <new>
#include <type_traits>
#include <utility>
template<typename vt>
class smart_ptr{
public:
    smart_ptr()noexcept(std::is_nothrow_default_constructible_v<vt>){
        ptr = new(std::nothrow)vt();
    }

    ~smart_ptr()noexcept(std::is_nothrow_destructible_v<vt>){
        if(ptr != nullptr) {
            (*ptr).~vt();
            operator delete(ptr, std::nothrow);
        }
    }

    smart_ptr(const smart_ptr &other) = delete;
    smart_ptr &operator=(const smart_ptr &other) = delete;

    smart_ptr(smart_ptr <vt> &&other)noexcept{
        ptr = std::exchange(other.ptr, nullptr);
    }

    smart_ptr &operator=(smart_ptr<vt> &&other)noexcept(std::is_nothrow_destructible_v<vt>){
        (*ptr).~vt();
        operator delete(ptr, std::nothrow);
        ptr = std::exchange(other.ptr, nullptr);
        return *this;
    }

    vt* get()const noexcept{
        return ptr;
    }

    vt &operator*()const noexcept{
        return *ptr;
    }
    vt* operator->()const noexcept{
        return ptr;
    }

private:
    vt *ptr;
};
