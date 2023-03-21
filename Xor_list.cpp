#include<iostream>
#include<new>
#include<utility>

template <class T>
class Node {
public:
    T val;
    Node<T> *pointer;

    Node() = default;
    explicit Node(const T &value){
        val = value;
    }
};

template <class T>
class XorList {
public:
    XorList(){
        first = nullptr;
        last = nullptr;
    }
    ~XorList()noexcept{
        Node<T> *tmp = first;
        Node<T> *prev = first;
        Node<T> *cur = tmp;
        tmp = tmp->pointer;
        operator delete(cur, std::nothrow);

        while (tmp != last){
            cur = tmp;
            tmp = reinterpret_cast<Node<T>*>
            ((reinterpret_cast<unsigned long long>(prev) ^ reinterpret_cast<unsigned long long>((tmp->pointer))));
            prev = cur;
            operator delete(cur, std::nothrow);
        }
        operator delete(tmp, std::nothrow);
    }

    XorList(const XorList &other); // TODO
    XorList(XorList &&other); // TODO

    XorList& operator=(const XorList &other); // TODO
    XorList& operator=(XorList &&other); // TODO

    XorList& insert_back(const T& node_value){
        if (empty()){
            T val = node_value;
            insert_front(std::move(val));
        }
        else{
            auto *new_last = new Node<T>();
            new_last->val = node_value;
            new_last->pointer = last;
            last->pointer = reinterpret_cast<Node<T>*>
                    ((reinterpret_cast<unsigned long long>(new_last) ^ reinterpret_cast<unsigned long long>(last->pointer)));
            last = new_last;
        }

        return *this;
    }

    XorList& insert_front(T&& node_value){
        if(empty()){
            auto *head = new Node<T>();
            head->val = node_value;
            head->pointer = nullptr;
            first = head;
            last = head;
        }
        else{
            auto *new_first = new Node<T>();
            new_first->val = node_value;
            new_first->pointer = first;
            first->pointer = reinterpret_cast<Node<T> *>
                    ((reinterpret_cast<unsigned long long>(new_first) ^ reinterpret_cast<unsigned long long>(first->pointer)));
            first = new_first;
        }
        return *this;
    }

    XorList& erase_back(); // TODO
    XorList& erase_front(); // TODO

    XorList& merge(const XorList& other); // TODO
    XorList& merge(XorList&& other); // TODO

    bool empty(){
        if (first == nullptr) return true;
        else return false;
    }

    Node<T>* getFirst()const{
        return first;
    }

    Node<T>* getLast()const{
        return last;
    }

private:
    Node<T>* first;
    Node<T>* last;


};

template<typename T>
std::ostream& operator<<(std::ostream& out, const XorList<T>& xor_list){
    Node<T> *tmp = xor_list.getFirst();
    Node<T> *prev = xor_list.getFirst();
    out << tmp->val << ' ' << std::endl;
    tmp = tmp->pointer;
    while (tmp != xor_list.getLast()){
        out << tmp->val << ' ' << std::endl;
        Node<T> *cur = tmp;
        tmp = reinterpret_cast<Node<T>*>
        ((reinterpret_cast<unsigned long long>(prev) ^ reinterpret_cast<unsigned long long>((tmp->pointer))));
        prev = cur;
    }
    out << tmp->val << ' ' << std::endl;
    return out;
}

int main(){
    XorList list = XorList<int>();
    list.insert_front(12);
    list.insert_front(13);
    list.insert_back(232);
    list.insert_front(14);
    list.insert_back(15);
    std::cout << list;
    return 0;
}