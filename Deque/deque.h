//https://github.com/pilot7747/Deque
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>

template<typename T> class Deque;

template<typename T, typename DequePointer>
class DequeIterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
    using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
    friend class Deque<T>;
    DequeIterator() : _deq(nullptr), _ind(0) {}
    DequeIterator(const DequeIterator &it) : _deq(it._deq), _ind(it._ind) {}
    DequeIterator(DequePointer deq) : _deq(deq), _ind(0) {}
    //DequeIterator(const Deque<const T> *deq) : _deq(deq), _ind(0) {}
    inline DequeIterator& operator+=(difference_type rhs);
    inline DequeIterator& operator-=(difference_type rhs);
    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](difference_type rhs);
    inline T& operator[](difference_type rhs) const;
    
    inline DequeIterator& operator++();
    inline DequeIterator& operator--();
    inline DequeIterator operator++(int);
    inline DequeIterator operator--(int);
    inline DequeIterator operator+(const DequeIterator& rhs);
    //inline DequeIterator operator-(const DequeIterator& rhs);
    inline difference_type operator-(const DequeIterator& rhs) const;
    inline DequeIterator operator+(difference_type rhs) const;
    inline DequeIterator operator-(difference_type rhs) const;
    template<typename type, typename Deque_Pointer> friend inline DequeIterator operator+(difference_type lhs, const DequeIterator<type, Deque_Pointer>& rhs);
    template<typename type, typename Deque_Pointer> friend inline DequeIterator operator-(difference_type lhs, const DequeIterator<type, Deque_Pointer>& rhs);
    
    inline bool operator==(const DequeIterator& rhs) const;
    inline bool operator!=(const DequeIterator& rhs) const;
    inline bool operator>(const DequeIterator& rhs) const;
    inline bool operator<(const DequeIterator& rhs) const;
    inline bool operator>=(const DequeIterator& rhs) const;
    inline bool operator<=(const DequeIterator& rhs) const;
private:
    DequePointer _deq;
    size_t _ind;
};

template<typename T>
class Deque {
public:
    typedef DequeIterator<T, Deque<T>*> iterator;
    typedef DequeIterator<const T, const Deque<T>*> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    void push_back(const T value);
    void push_front(const T value);
    void pop_back();
    void pop_front();
    void clear();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    bool empty() const;
    size_t size() const;
    T& operator[](size_t n);
    const T& operator[](size_t n) const;
    
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    Deque() {}
    Deque(const Deque &tmp);
private:
    std::vector<T> _leftStack;
    std::vector<T> _rightStack;
    void _balance();
};
//Implementation

//----FUNCTIONS WITH ITERATORS----
template<typename T>
DequeIterator<T, Deque<T>*> Deque<T>::begin() {
    return iterator(this);
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::begin() const {
    return const_iterator(this);
}

template<typename T>
DequeIterator<T, Deque<T>*> Deque<T>::end() {
    iterator it(this);
    it += this->size();
    return it;
}

template<typename T>
typename Deque<T>::const_iterator Deque<T>::end() const {
    const_iterator it(this);
    it += this->size();
    return it;
}

template<typename T>
DequeIterator<const T, const Deque<T>*> Deque<T>::cbegin() const {
    return const_iterator(this);
}

template<typename T>
DequeIterator<const T, const Deque<T>*> Deque<T>::cend() const {
    const_iterator it(this);
    it += this->size();
    return it;
}

template<typename T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin() {
    return reverse_iterator(end());
}

template<typename T>

typename Deque<T>::reverse_iterator Deque<T>::rend() {
    return reverse_iterator(begin());
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const {
    return const_reverse_iterator(begin());
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const {
    return const_reverse_iterator(cend());
}

template<typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const {
    return const_reverse_iterator(cbegin());
}
//---IMPLEMENTATION OF Deque FUNCTIONS---
template<typename T>
void Deque<T>::push_back(const T value) {
    _leftStack.push_back(value);
}

template<typename T>
void Deque<T>::push_front(const T value) {
    _rightStack.push_back(value);
}

template<typename T>
void Deque<T>::_balance() {
    std::vector<T>* emptyVec;
    std::vector<T>* balancingVec;
    if (_leftStack.empty())
    {
        emptyVec = &_leftStack;
        balancingVec = &_rightStack;
    }
    else
    {
        emptyVec = &_rightStack;
        balancingVec = &_leftStack;
    }
    std::stack<T> localStack;
    size_t balancingSize = balancingVec->size();
    for (size_t i = 0; i < balancingSize / 2; ++i)
    {
        localStack.push(balancingVec->back());
        balancingVec->pop_back();
    }
    while (!balancingVec->empty())
    {
        emptyVec->push_back(balancingVec->back());
        balancingVec->pop_back();
    }
    while (!localStack.empty())
    {
        balancingVec->push_back(localStack.top());
        localStack.pop();
    }
}

template<typename T>
void Deque<T>::pop_back() {
    if (_leftStack.empty())
        _balance();
    _leftStack.pop_back();
}

template<typename T>
void Deque<T>::pop_front() {
    if (_rightStack.empty())
        _balance();
    _rightStack.pop_back();
}

template<typename T>
T& Deque<T>::back() {
    if (_leftStack.empty())
        _balance();
    return _leftStack.back();
}

template<typename T>
const T& Deque<T>::back() const {
    if (_leftStack.empty())
        return _rightStack.front();
    return _leftStack.back();
}

template<typename T>
T& Deque<T>::front() {
    if (_rightStack.empty())
        _balance();
    return _rightStack.back();
}

template<typename T>
const T& Deque<T>::front() const {
    if (_rightStack.empty())
        return _leftStack.front();
    return _rightStack.back();
}

template<typename T>
const T& Deque<T>::operator[](size_t n) const {
    if (n < _rightStack.size())
        return _rightStack[_rightStack.size() - n - 1];
    else
        return _leftStack[n - _rightStack.size()];
}


template<typename T>
T& Deque<T>::operator[](size_t n) {
    if (n < _rightStack.size())
        return _rightStack[_rightStack.size() - n - 1];
    else
        return _leftStack[n - _rightStack.size()];
}

template<typename T>
size_t Deque<T>::size() const {
    return _leftStack.size() + _rightStack.size();
}

template <typename T>
bool Deque<T>::empty() const {
    return (_leftStack.empty() && _rightStack.empty());
}

template<typename T>
void Deque<T>::clear() {
    _leftStack.clear();
    _rightStack.clear();
}

template <typename T>
Deque<T> :: Deque (const Deque<T> &tmp) {
    _leftStack = tmp._leftStack;
    _rightStack = tmp._rightStack;
}

//---IMPLEMENTATION OF ITERATORS
template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer>& DequeIterator<T, DequePointer>::operator+=(difference_type rhs) {
    _ind += rhs;
    return *this;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer>& DequeIterator<T, DequePointer>::operator-=(difference_type rhs) {
    _ind -= rhs;
    return *this;
}

template<typename T, typename DequePointer>
inline T& DequeIterator<T, DequePointer>::operator*() const {
    return (*_deq)[_ind];
}

template<typename T, typename DequePointer>
inline T* DequeIterator<T, DequePointer>::operator->() const {
    return &(*_deq)[_ind];
}


template<typename T, typename DequePointer>
inline T& DequeIterator<T, DequePointer>::operator[](difference_type rhs) {
    return (*_deq)[_ind + rhs];
}

template<typename T, typename DequePointer>
inline T& DequeIterator<T, DequePointer>::operator[](difference_type rhs) const {
    return (*_deq)[_ind + rhs];
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer>& DequeIterator<T, DequePointer>::operator++() {
    *this += 1;
    return *this;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer>& DequeIterator<T, DequePointer>::operator--() {
    *this -= 1;
    return *this;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> DequeIterator<T, DequePointer>::operator++(int) {
    DequeIterator<T, DequePointer> temp = *this;
    ++*this;
    return temp;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> DequeIterator<T, DequePointer>::operator--(int) {
    DequeIterator<T, DequePointer> temp = *this;
    --*this;
    return temp;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> DequeIterator<T, DequePointer>::operator+(const DequeIterator& rhs) {
    DequeIterator<T, DequePointer> it(_deq);
    it += _ind + rhs._ind;
    return it;
}


template<typename T, typename DequePointer>
inline typename std::iterator<std::random_access_iterator_tag, T>::difference_type DequeIterator<T, DequePointer>::operator-(const DequeIterator<T, DequePointer> &rhs) const {
    return (static_cast<difference_type>(_ind) - static_cast<difference_type>(rhs._ind));
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> DequeIterator<T, DequePointer>::operator+(difference_type rhs) const {
    DequeIterator<T, DequePointer> it(_deq);
    it += (_ind + rhs);
    return it;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> DequeIterator<T, DequePointer>::operator-(difference_type rhs) const {
    DequeIterator<T, DequePointer> it(_deq);
    it += (_ind - rhs);
    return it;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> operator+(typename std::iterator<std::random_access_iterator_tag, T>::difference_type lhs, const DequeIterator<T, DequePointer>& rhs) {
    DequeIterator<T, DequePointer> it(rhs._deq);
    it += (lhs + rhs._ind);
    return it;
}

template<typename T, typename DequePointer>
inline DequeIterator<T, DequePointer> operator-(typename std::iterator<std::random_access_iterator_tag, T>::difference_type lhs, const DequeIterator<T, DequePointer>& rhs) {
    DequeIterator<T, DequePointer> it(rhs._deq);
    it += (lhs - rhs._ind);
    return it;
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator==(const DequeIterator<T, DequePointer>& rhs) const {
    return (_deq == rhs._deq) && (_ind == rhs._ind);
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator!=(const DequeIterator<T, DequePointer>& rhs) const {
    return !(*this == rhs);
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator<(const DequeIterator<T, DequePointer>& rhs) const {
    return (_deq == rhs._deq) && (_ind < rhs._ind);
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator<=(const DequeIterator<T, DequePointer>& rhs) const {
    return (*this < rhs) || (*this == rhs);
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator>(const DequeIterator<T, DequePointer>& rhs) const {
    return !(*this <= rhs);
}

template<typename T, typename DequePointer>
inline bool DequeIterator<T, DequePointer>::operator>=(const DequeIterator<T, DequePointer>& rhs) const {
    return !(*this < rhs);
}
