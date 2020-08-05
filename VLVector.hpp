//
// Created by Dan Regev on 8/4/2020.
//

#ifndef CPP_FINAL_PROJECT_VLVECTOR_HPP
#define CPP_FINAL_PROJECT_VLVECTOR_HPP

#include <iterator>
#include <memory>
#define AT_EXCEPTION_MSG "In function \"at\": Index was not found"
#define DEF_STATIC_CAPACITY 16

template<typename T, size_t StaticCapacity = DEF_STATIC_CAPACITY>
class VLVector
{
private:
    bool stackMode;
    std::size_t _size;
    std::size_t _capacity;
    std::unique_ptr<T[]> heapVec;
    T stackVec[StaticCapacity];

    /**
     * @brief An iterator for the vector.
     */
    class iterator
    {
    public:

        /**
         * @brief Returns the current element the iterator points at.
         * @return the current element the iterator points at.
         */
        T &operator*(){}

        /**
         * @brief Returns a pointer to the current element the iterator points at.
         * @return a pointer to the current element the iterator points at.
         */
        T *operator->(){}

        /**
         * @brief Increments the iterator so that it points to the next element in the vector.
         * @return the iterator after it was incremented.
         */
        iterator &operator++(){}

        /**
         * @brief Increments the iterator so that it points to the next element in the vector.
         * @return the element that the iterator pointed to before it was incremented.
         */
        iterator operator++(int){}

        /**
         * @brief Decrements the iterator so that it points to the previous element in the vector.
         * @return the iterator after it was decremented.
         */
        iterator &operator--(){}

        /**
         * @brief Decrements the iterator so that it points to the previous element in the vector.
         * @return the element that the iterator pointed to before it was decremented.
         */
        iterator operator--(int){}

        /**
         * @brief Concatenates this iterator with another one and returns the result.
         * @param other the other iterator to concatenate to this one.
         * @return the result of the concatenation.
         */
        iterator operator+(const iterator &other){}

        iterator operator-(const iterator &other){}

        iterator &operator+=(const iterator &other){}

        iterator &operator-=(const iterator &other){}

        /**
         * @brief Checks if the iterator points to the same element that another iterator points to.
         * @param other the other iterator.
         * @return true iff both iterators point to the same element.
         */
        bool operator==(const iterator &other) const{}

        /**
         * @brief Checks if the iterator doesn't point to a the same element
         * that another iterator points to.
         * @param other the other iterator.
         * @return true iff the iterators don't point to the same element.
         */
        bool operator!=(const iterator &other) const
        {
            return !operator==(other);
        }

        bool operator<(const iterator &other) const{}

        bool operator>(const iterator &other) const{}

        bool operator<=(const iterator &other) const{}

        bool operator>=(const iterator &other) const{}

        /**
         * @brief Iterator traits.
         */
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    private:
    };

    /**
     * @brief Copies the elements of the vector from the stack to the heap.
     * Sets the flag stackMode to false.
     */
    void copyToHeap()
    {
        stackMode = false;
        heapVec = std::make_unique<T[]>(_capacity);
        for (int i = 0; i < (int) StaticCapacity; ++i)
        {
            heapVec[i] = stackVec[i];
        }
    }

    /**
     * @brief Copies the elements of the vector from the heap to the stack.
     * Sets the flag stackMode to true.
     */
    void copyToStack()
    {
        stackMode = true;
        for (int i = 0; i < (int) _size; ++i)
        {
            stackVec[i] = heapVec[i];
        }
        heapVec.reset(nullptr);
    }
public:
    /**
     * @brief Default constructor. Initialises an empty VLVector.
     */
    VLVector() : stackMode(true), _size(0), _capacity(StaticCapacity), heapVec(nullptr){}

    /**
     * @brief Constructs a VLVector object.
     * Receives an iterator to a group of T values and stores them in the vector.
     * @tparam InputIterator the type of iterator to T values.
     * @param first iterator to the first T value in the group.
     * @param last iterator to the last T value in the group.
     */
    template<class InputIterator> //TODO
    VLVector(InputIterator& first, InputIterator& last) : stackMode(true), _size(0), _capacity(StaticCapacity)
    {
//        for (auto &it = first; it != last; ++it)
//        {
//            insert();
//        }
    }

    /**
     * @brief Returns the number of elements that are stored in the vector.
     * @return the number of elements that are stored in the vector.
     */
    std::size_t size() const {return _size;}

    /**
     * @brief Returns the capacity of the vector according to the formula given in the exam.
     * @return the capacity of the vector.
     */
    std::size_t capacity() const
    {
        if ((int)_size + 1 <= StaticCapacity)
        {
            return StaticCapacity;
        }
        return (size_t)(3 * (_size + 1) / 2);
    }

    /**
     * @brief Checks if the vector is empty.
     * @return true iff the vector is empty.
     */
    bool empty() const {return _size == 0;}

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Throws an exception if the index was not found.
     * @param index the index of the value in the vector.
     * @return a reference to the value that is associated to the index.
     */
    T &at(const int index)
    {
        if (index >= 0 && index <= (int)_size)
        {
            if (stackMode)
            {
                return stackVec[index];
            }
            return heapVec[index];
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
        if (index >= 0 && index <= (int)_size)
        {
            if (stackMode)
            {
                return stackVec[index];
            }
            return heapVec[index];
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
        if (stackMode) //We are in stack mode - values are stored on the stack:
        {
            //If the capacity that was calculated before does not exceed the static capacity:
            if (newCapacity <= StaticCapacity)
            {
                stackVec[_size] = val;
            }
            else //If the capacity that was calculated before exceeds the static capacity:
            {
                _capacity = newCapacity;
                copyToHeap();
                heapVec[_size] = val;
            }
        }
        else //We are in heap mode - values are stored on the heap:
        {
            if (_size + 1 > _capacity)
            {
                auto newHeap = std::make_unique<T[]>(newCapacity);
                for (int i = 0; i < _size; ++i)
                {
                    newHeap[i] = heapVec[i];
                }
                _capacity = newCapacity;
                heapVec.swap(newHeap);
            }
            heapVec[_size] = val;
        }
        ++_size;
    }

    /**
     * @brief Adds a given value to the end of the vector.
     * @param val the value to add, given as an r-value.
     */
    void push_back(const T &&val)
    {
        std::size_t newCapacity = capacity();
        if (stackMode) //We are in stack mode - values are stored on the stack:
        {
            //If the capacity that was calculated before does not exceed the static capacity:
            if (newCapacity <= StaticCapacity)
            {
                stackVec[_size] = val;
            }
            else //If the capacity that was calculated before exceeds the static capacity:
            {
                _capacity = newCapacity;
                copyToHeap();
                heapVec[_size] = val;
            }
        }
        else //We are in heap mode - values are stored on the heap:
        {
            if (_size + 1 > _capacity)
            {
                //Increase size of vector on heap:
                auto newHeap = std::make_unique<T[]>(newCapacity);
                for (int i = 0; i < _size; ++i)
                {
                    newHeap[i] = heapVec[i];
                }
                _capacity = newCapacity;
                heapVec.swap(newHeap);
            }
            heapVec[_size] = val;
        }
        ++_size;
    }

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an l-value.
     * @return an iterator that points to the added value.
     */ //TODO
    iterator insert(const iterator &position, const T &val){}

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an r-value.
     * @return an iterator that points to the added value.
     */ //TODO
    iterator insert(const iterator &position, const T &&val){}

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
            if (!stackMode && capacity() <= StaticCapacity)
            {
                _capacity = StaticCapacity;
                copyToStack();
            }
        }
    }

    /**
     * @brief Removes from the vector the value that the given iterator points to.
     * @param position an iterator that points to the value that is to be removed.
     * @return an iterator to the value that appeared after the removed value.
     */ //TODO
    iterator erase(iterator &position){}

    /**
     * @brief Removes all elements from the vector.
     */ //TODO
    void clear()
    {
        if (stackMode)
        {
            for (int i = 0; i < (int) _size; ++i)
            {
                stackVec[i] = T();
            }
        }
        else
        {
            heapVec.reset(nullptr);
            _capacity = StaticCapacity;
            stackMode = true;
        }
        _size = 0;
    }

    /**
     * @brief Returns a pointer to the data type that currently contains the vector.
     * @return a pointer to the data type that currently contains the vector.
     */
    T *data() const
    {
        if (stackMode)
        {
            return stackVec;
        }
        return heapVec.get();
    }

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Allows changing the value associated to the key.
     * @param index the given index.
     * @return a reference to the value associated to the index.
     */
    T &operator[](const int index) noexcept
    {
        if (index >= 0 && index < (int)_size)
        {
            return data()[index];
        }
//        return T();
    }

    /**
     * @brief Gets an index and returns the value associated to it.
     * Does not allow changing the value associated to the key.
     * @param index the given index.
     * @return the value associated to the index.
     */
    const T &operator[](const int index) const noexcept
    {
        if (index >= 0 && index < (int)_size)
        {
            return data()[index];
        }
//        return T();
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
            if (*this[i] != other[i])
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
    bool operator!=(const VLVector &other) const {return !operator==(other);}

    //TODO
    iterator begin(){return iterator();}
};


#endif //CPP_FINAL_PROJECT_VLVECTOR_HPP
