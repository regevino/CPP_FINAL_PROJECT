//
// Created by Dan Regev on 8/4/2020.
//

#ifndef CPP_FINAL_PROJECT_VLVECTOR_HPP
#define CPP_FINAL_PROJECT_VLVECTOR_HPP

#include <iterator>
#include <memory>
#include <algorithm>

#define AT_EXCEPTION_MSG "In function \"at\": Index was not found"
#define DEF_STATIC_CAPACITY 16

/**
 * @brief Represents a Virtual Length Vector object.
 * @tparam T the type of values stored in the vector.
 * @tparam StaticCapacity the amount of space the vector will occupy on the stack.
 */
template<typename T, size_t StaticCapacity = DEF_STATIC_CAPACITY>
class VLVector
{
private:
    bool _stackMode;
    std::size_t _size;
    std::size_t _capacity;
    T _stackVec[StaticCapacity];
    T *_heapVec;

    /**
     * @brief An iterator for the vector.
     */
    template<typename Val>
    class VLVectorIterator
    {
    private:
        unsigned int _index;
        std::size_t _size;
        Val *_vec;

    public:

        /**
         * @brief Iterator traits.
         */
        typedef Val value_type;
        typedef Val *pointer;
        typedef Val &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        /**
         * @brief Constructor for iterator objects.
         * Initialises the iterator to point at the first element in the vector.
         * @param index
         * @param size
         * @param vec
         */
        VLVectorIterator(unsigned int index, size_t size, Val *vec)
                : _index(index), _size(size), _vec(vec)
        {
        }

        /**
         * @brief Returns the current element the iterator points at.
         * @return the current element the iterator points at.
         */
        Val &operator*() const
        {
            return _vec[_index];
        }

        /**
         * @brief Returns a pointer to the current element the iterator points at.
         * @return a pointer to the current element the iterator points at.
         */
        Val *operator->() const
        {
            return &_vec[_index];
        }

        /**
         * @brief Increments the iterator so that it points to the next element in the vector.
         * @return the iterator after it was incremented.
         */
        VLVectorIterator &operator++()
        {
            if (_index < _size)
            {
                ++_index;
            }
            return *this;
        }

        /**
         * @brief Increments the iterator so that it points to the next element in the vector.
         * @return the element that the iterator pointed to before it was incremented.
         */
        VLVectorIterator operator++(int)
        {
            VLVectorIterator temp = *this;
            if (_index < _size)
            {
                ++_index;
            }
            return temp;
        }

        /**
         * @brief Decrements the iterator so that it points to the previous element in the vector.
         * @return the iterator after it was decremented.
         */
        VLVectorIterator &operator--()
        {
            if (_index > 0)
            {
                --_index;
            }
            return *this;
        }

        /**
         * @brief Decrements the iterator so that it points to the previous element in the vector.
         * @return the element that the iterator pointed to before it was decremented.
         */
        VLVectorIterator operator--(int)
        {
            VLVectorIterator temp = *this;
            if (_index > 0)
            {
                --_index;
            }
            return temp;
        }

        /**
         * @brief Returns an iterator that points to the value that is stored in a given
         * distance after this iterator.
         * @param distance the distance between this iterator to the result.
         * @return the result of the addition.
         */
        VLVectorIterator operator+(const difference_type distance) const
        {
            VLVectorIterator res = *this;
            return res.operator+=(distance);
        }

        /**
         * @brief Returns an iterator that points to the value that is stored in a given
         * distance before this iterator.
         * @param distance the distance between this iterator to the result.
         * @return the result of the subtraction.
         */
        VLVectorIterator operator-(const difference_type distance) const
        {
            VLVectorIterator res = *this;
            return res.operator-=(distance);
        }

        /**
         * @brief Returns an iterator that points to the value that is stored in a given
         * distance before this iterator.
         * @param distance the distance between this iterator to the result.
         * @return the result of the subtraction.
         */
        difference_type operator-(const VLVectorIterator &other) const
        {
            return _index - other._index;
        }

        /**
         * @brief Moves this iterator to point at the value that is stored in a given
         * distance after this iterator.
         * @param distance the distance between this iterator to the result.
         * @return this iterator after the addition.
         */
        VLVectorIterator &operator+=(const difference_type distance)
        {
            if (std::size_t(_index + distance) <= _size)
            {
                _index += distance;
            }
            return *this;
        }

        /**
         * @brief Moves this iterator to point at the value that is stored in a given
         * distance before this iterator.
         * @param distance the distance between this iterator to the result.
         * @return this iterator after the subtraction.
         */
        VLVectorIterator &operator-=(const difference_type distance)
        {
            if (_index - distance >= 0)
            {
                _index -= distance;
            }
            return *this;
        }

        /**
         * @brief Returns the value that is stored i steps from the position this iterator is at.
         * @param i the interval.
         * @return the value that is stored i steps from the position this iterator is at.
         */
        Val &operator[](const difference_type i) const noexcept
        {
            if (_index + i < _size)
            {
                return _vec[_index + i];
            }
        }

        /**
         * @brief Checks if the iterator points to the same element that another iterator points to.
         * @param other the other iterator.
         * @return true iff both iterators point to the same element.
         */
        bool operator==(const VLVectorIterator &other) const
        {
            //Edge case: both iterators are end():
            if (_index == _size && other._index == other._size)
            {
                return true;
            }

            //Edge case: one of the iterators is end() but the other isn't:
            if (_index != _size && other._index == other._size)
            {
                return false;
            }

            //Edge case: same as previous, the other way around:
            if (_index == _size && other._index != other._size)
            {
                return false;
            }

            return _index == other._index && *(*this) == *other;
        }

        /**
         * @brief Checks if the iterator doesn't point to a the same element
         * that another iterator points to.
         * @param other the other iterator.
         * @return true iff the iterators don't point to the same element.
         */
        bool operator!=(const VLVectorIterator &other) const
        {
            return !operator==(other);
        }

        /**
         * @brief Checks if this iterator points to a value that is stored before the value
         * that the given iterator points to.
         * @param other the other iterator.
         * @return true iff this iterator points to a value that is stored before the value
         * that the given iterator points to.
         */
        bool operator<(const VLVectorIterator &other) const
        {
            return _index < other._index;
        }

        /**
         * @brief Checks if this iterator points to a value that is stored after the value
         * that the given iterator points to.
         * @param other the other iterator.
         * @return true iff this iterator points to a value that is stored after the value
         * that the given iterator points to.
         */
        bool operator>(const VLVectorIterator &other) const
        {
            return _index > other._index;
        }

        /**
         * @brief Checks if this iterator points to a value that is stored before the value
         * that the given iterator points to or if they point to the same value.
         * @param other the other iterator.
         * @return true iff this iterator points to a value that is stored before the value
         * that the given iterator points to or if they point to the same value.
         */
        bool operator<=(const VLVectorIterator &other) const
        {
            return !operator>(other);
        }

        /**
         * @brief Checks if this iterator points to a value that is stored after the value
         * that the given iterator points to or if they point to the same value.
         * @param other the other iterator.
         * @return true iff this iterator points to a value that is stored after the value
         * that the given iterator points to or if they point to the same value.
         */
        bool operator>=(const VLVectorIterator &other) const
        {
            return !operator<(other);
        }
    };

    /**
     * @brief Copies the elements of the vector from the stack to the heap.
     * Sets the flag stackMode to false.
     */
    void _copyToHeap()
    {
        _stackMode = false;
        _heapVec = new T[_capacity];
        for (int i = 0; i < (int) StaticCapacity; ++i)
        {
            _heapVec[i] = _stackVec[i];
        }
    }

    /**
     * @brief Copies the elements of the vector from the heap to the stack.
     * Sets the flag stackMode to true.
     */
    void _copyToStack()
    {
        _stackMode = true;
        for (int i = 0; i < (int) _size; ++i)
        {
            _stackVec[i] = _heapVec[i];
        }
        delete[] _heapVec;
        _heapVec = nullptr;
    }

    /**
     * @brief Increases the size of the vector on heap.
     * @param newCapacity the new capacity of the vector.
     */
    void _increaseHeap(size_t newCapacity)
    {
        T *newHeap = new T[newCapacity];
        for (int i = 0; i < (int) _size; ++i)
        {
            newHeap[i] = _heapVec[i];
        }
        _capacity = newCapacity;
        delete[] _heapVec;
        _heapVec = newHeap;
    }

public:

    /**
     * @brief Typedefs for const and non-const iterators for the vector.
     */
    typedef VLVectorIterator<T> iterator;
    typedef VLVectorIterator<const T> const_iterator;

    /**
     * @brief Default constructor. Initialises an empty VLVector.
     */
    VLVector() : _stackMode(true), _size(0), _capacity(StaticCapacity), _heapVec(nullptr)
    {
    }

    /**
     * @brief Copy constructor.
     * @param other the vector to copy from.
     */
    VLVector(const VLVector &other)
            : _stackMode(other._stackMode), _size(other._size), _capacity(other._capacity),
              _heapVec(nullptr)
    {
        if (_stackMode)
        {
            std::copy(other._stackVec, other._stackVec + StaticCapacity, _stackVec);
        }
        else
        {
            _heapVec = new T[_capacity];
            std::copy(other._heapVec, other._heapVec + _size, _heapVec);
        }
    }

    /**
     * @brief Move constructor.
     * @param other the vector to move from.
     */
    VLVector(VLVector && other) noexcept
            : _stackMode(other._stackMode), _size(other._size), _capacity(other._capacity)
    {
        std::copy(other._stackVec, other._stackVec + StaticCapacity, _stackVec);
        _heapVec = other._heapVec;
        other._heapVec = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    /**
     * @brief Destructor.
     */
    ~VLVector()
    {
        delete[] _heapVec;
    }

    /**
     * @brief Implements the "swap" part of the "Copy and Swap" idiom.
     * @param first the vector to assign to.
     * @param second the vector to assign from.
     */
    friend void swap(VLVector &first, VLVector &second) noexcept
    {
        using std::swap;
        swap(first._stackMode, second._stackMode);
        swap(first._size, second._size);
        swap(first._capacity, second._capacity);
        swap(first._stackVec, second._stackVec);
        swap(first._heapVec, second._heapVec);
    }

    /**
     * @brief Assignment operator, both regular and move since other is received by value,
     * thus received via copy constructor for l-values and via move constructor for r-values.
     * @param other the other vector to assign from.
     * @return this vector after assignment.
     */
    VLVector &operator=(VLVector other)
    {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Constructs a VLVector object.
     * Receives an iterator to a group of T values and stores them in the vector.
     * @tparam InputIterator the type of iterator to T values.
     * @param first iterator to the first T value in the group.
     * @param last iterator to the last T value in the group.
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last)
            : _stackMode(true), _size(0), _capacity(StaticCapacity), _heapVec(nullptr)
    {
        for (auto it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    /**
     * @brief Returns the number of elements that are stored in the vector.
     * @return the number of elements that are stored in the vector.
     */
    std::size_t size() const
    {
        return _size;
    }

    /**
     * @brief Returns the capacity of the vector according to the formula given in the exam.
     * @return the capacity of the vector.
     */
    std::size_t capacity() const
    {
        if (_size + 1 <= StaticCapacity)
        {
            return StaticCapacity;
        }
        return (size_t) (3 * (_size + 1) / 2);
    }

    /**
     * @brief Checks if the vector is empty.
     * @return true iff the vector is empty.
     */
    bool empty() const
    {
        return _size == 0;
    }

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Throws an exception if the index was not found.
     * @param index the index of the value in the vector.
     * @return a reference to the value that is associated to the index.
     */
    T &at(const int index)
    {
        if (index >= 0 && index < (int) _size)
        {
            return data()[index];
        }
        throw std::out_of_range(AT_EXCEPTION_MSG);
    }

    /**
     * @brief Gets an index and returns the value associated to it.
     * Throws an exception if the index was not found.
     * @param index the index of the value in the vector.
     * @return the value that is associated to the index.
     */
    T at(const int index) const
    {
        if (index >= 0 && index < (int) _size)
        {
            return data()[index];
        }
        throw std::out_of_range(AT_EXCEPTION_MSG);
    }

    /**
     * @brief Adds a given value to the end of the vector.
     * @param val the value to add, given as an l-value.
     */
    void push_back(const T &val)
    {
        std::size_t newCapacity = capacity();
        // We are in stack mode - values are stored on the stack,
        // and the capacity that was calculated before exceeds the static capacity:
        if (_stackMode && newCapacity > StaticCapacity)
        {
            _capacity = newCapacity;
            _copyToHeap();
        }
        else if (_size + 1 > _capacity)
        {
            // We are in heap mode - values are stored on the heap,
            // and the capacity needs to be increased:
            _increaseHeap(newCapacity);
        }
        data()[_size] = val;
        ++_size;
    }

    /**
     * @brief Adds a given value to the end of the vector.
     * @param val the value to add, given as an r-value.
     */
    void push_back(const T && val)
    {
        std::size_t newCapacity = capacity();

        // We are in stack mode - values are stored on the stack,
        // and the capacity that was calculated before exceeds the static capacity:
        if (_stackMode && newCapacity > StaticCapacity)
        {
            _capacity = newCapacity;
            _copyToHeap();
        }
        else if (_size + 1 > _capacity)
        {
            // We are in heap mode - values are stored on the heap,
            // and the capacity needs to be increased:
            _increaseHeap(newCapacity);
        }
        data()[_size] = val;
        ++_size;
    }

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an l-value.
     * @return an iterator that points to the added value.
     */
    iterator insert(const iterator position, const T &val)
    {
        std::size_t newCapacity = capacity();

        // We are in stack mode - values are stored on the stack,
        // and the capacity that was calculated before exceeds the static capacity:
        if (_stackMode && newCapacity > StaticCapacity)
        {
            _capacity = newCapacity;
            _copyToHeap();
        }
        else if (_size + 1 > _capacity)
        {
            // We are in heap mode - values are stored on the heap,
            // and the capacity needs to be increased:
            _increaseHeap(newCapacity);
        }
        // Move the values of the vector that should appear
        // after the new value one step to the right:
        for (auto it = end(); it != position; --it)
        {
            *it = *(it - 1);
        }
        *position = val;
        ++_size;
        return position;
    }

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an r-value.
     * @return an iterator that points to the added value.
     */
    iterator insert(const iterator position, const T && val)
    {
        auto last = end();
        if (position == last)
        {
            push_back(val);
            return position;
        }
        std::size_t newCapacity = capacity();

        // We are in stack mode - values are stored on the stack,
        // and the capacity that was calculated before exceeds the static capacity:
        if (_stackMode && newCapacity > StaticCapacity)
        {
            _capacity = newCapacity;
            _copyToHeap();
        }
        else if (_size + 1 > _capacity)
        {
            // We are in heap mode - values are stored on the heap,
            // and the capacity needs to be increased:
            _increaseHeap(newCapacity);
        }
        // Move the values of the vector that should appear
        // after the new value one step to the right:
        for (auto it = last; it != position; --it)
        {
            *it = *(it - 1);
        }
        *position = val;
        ++_size;
        return position;
    }

    /**
     * @brief Removes the last element from the vector.
     */
    void pop_back()
    {
        if (_size > 0)
        {
            --_size;
            data()[_size] = T();

            // If we are in heap mode and following the pop action
            // the capacity decreased to static capacity:
            if (!_stackMode && capacity() <= StaticCapacity)
            {
                _capacity = StaticCapacity;
                _copyToStack();
            }
        }
    }

    /**
     * @brief Removes from the vector the value that the given iterator points to.
     * @param position an iterator that points to the value that is to be removed.
     * @return an iterator to the value that appeared after the removed value.
     */
    iterator erase(iterator position)
    {
        auto last = end();
        if (position + 1 == last)
        {
            pop_back();
            return position;
        }
        //Move the values of the vector that were after the erased value one step to the left:
        for (auto it = position; it != last; ++it)
        {
            *it = *(it + 1);
        }
        --_size;
        // If we are in heap mode and following the erase action
        // the capacity decreased to static capacity:
        if (!_stackMode && capacity() <= StaticCapacity)
        {
            _capacity = StaticCapacity;
            _copyToStack();
        }
        return position;
    }

    /**
     * @brief Removes all elements from the vector.
     */
    void clear()
    {
        // If we need to remove elements from the heap:
        if (!_stackMode)
        {
            delete[] _heapVec;
            _heapVec = nullptr;
            _capacity = StaticCapacity;
            _stackMode = true;
        }

        std::fill(_stackVec, _stackVec + _capacity, T());
        _size = 0;
    }

    /**
     * @brief Returns a pointer to the data type that currently contains the vector.
     * @return a pointer to the data type that currently contains the vector.
     */
    T *data()
    {
        if (_stackMode)
        {
            return _stackVec;
        }
        return _heapVec;
    }

    /**
     * @brief Returns a pointer to the data type that currently contains the vector.
     * @return a pointer to the data type that currently contains the vector.
     */
    const T *data() const
    {
        if (_stackMode)
        {
            return _stackVec;
        }
        return _heapVec;
    }

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Allows changing the value associated to the key.
     * @param index the given index.
     * @return a reference to the value associated to the index.
     */
    T &operator[](const int index) noexcept
    {
        return data()[index];
    }

    /**
     * @brief Gets an index and returns the value associated to it.
     * Does not allow changing the value associated to the key.
     * @param index the given index.
     * @return the value associated to the index.
     */
    const T &operator[](const int index) const noexcept
    {
        return data()[index];
    }

    /**
     * @brief Checks if this object equals to another VLVector object.
     * @param other the other VLVector object.
     * @return true iff the objects are the same.
     */
    bool operator==(const VLVector &other) const
    {
        //Check if this vector's size matches the other vector's size:
        if (_size != other._size)
        {
            return false;
        }

        // Check that each element in this vector compares equal
        // with the element in the other vector at the same position:
        for (int i = 0; i < (int) _size; ++i)
        {
            if ((*this)[i] != other[i])
            {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Checks if this object differs from another VLVector object.
     * @param other the other VLVector object.
     * @return true iff the objects differ from each other.
     */
    bool operator!=(const VLVector &other) const
    {
        return !operator==(other);
    }

    /**
     * @brief Returns an iterator to the beginning of the vector.
     * @return an iterator to the beginning of the vector.
     */
    iterator begin()
    {
        return iterator(0, _size, data());
    }

    /**
     * @brief Returns an iterator to the end of the vector.
     * @return an iterator to the end of the vector.
     */
    iterator end()
    {
        return iterator(_size, _size, data());
    }

    /**
     * @brief Returns a const iterator to the beginning of the vector.
     * @return an iterator to the beginning of the vector.
     */
    const_iterator begin() const
    {
        return const_iterator(0, _size, data());
    }

    /**
     * @brief Returns a const iterator to the end of the vector.
     * @return an iterator to the end of the vector.
     */
    const_iterator end() const
    {
        return const_iterator(_size, _size, data());
    }

    /**
     * @brief Returns a const iterator to the beginning of the vector.
     * @return an iterator to the beginning of the vector.
     */
    const_iterator cbegin() const
    {
        return const_iterator(0, _size, data());
    }

    /**
     * @brief Returns a const iterator to the end of the vector.
     * @return an iterator to the end of the vector.
     */
    const_iterator cend() const
    {
        return const_iterator(_size, _size, data());
    }
};


#endif //CPP_FINAL_PROJECT_VLVECTOR_HPP
