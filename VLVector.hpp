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
    std::unique_ptr<T> heapVec;
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
public:
    /**
     * @brief Default constructor. Initialises an empty VLVector.
     */
    VLVector() : stackMode(true), _size(0)
    //, heapVec(new T[0], [&](T *p){delete[] p;})
    {
        heapVec = std::make_unique<T>();
        heapVec.get()[0] = 1;
        std::cerr << heapVec.get()[0]<<'\n';//TODO CHECK IF MEMORY WAS RELEASED PROPERLY
    }
    /** stackVec()*///TODO IS THIS NEEDED?

    /**
     * @brief Constructs a VLVector object.
     * Receives an iterator to a group of T values and stores them in the vector.
     * @tparam InputIterator the type of iterator to T values.
     * @param first iterator to the first T value in the group.
     * @param last iterator to the last T value in the group.
     */
    template<class InputIterator>
    VLVector(InputIterator& first, InputIterator& last){}

    /**
     * @brief Returns the number of elements that are stored in the vector.
     * @return the number of elements that are stored in the vector.
     */
    inline std::size_t size() const {return this->_size;}

    /**
     * @brief Returns the capacity of the vector.
     * @return the capacity of the vector.
     */
    std::size_t capacity() const
    {
        if ((int)this->_size + 1 <= StaticCapacity)
        {
            return StaticCapacity;
        }
        return (size_t)(3 * (this->_size + 1) / 2);
    }

    /**
     * @brief Checks if the vector is empty.
     * @return true iff the vector is empty.
     */
    inline bool empty() const {return _size == 0;}

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Throws an exception if the index was not found.
     * @param index the index of the value in the vector.
     * @return a reference to the value that is associated to the index.
     */
    T &at(const int index)
    {
        if (index >= 0 && index <= (int)this->_size)
        {

        }
        throw std::out_of_range(AT_EXCEPTION_MSG);
    }

    /**
     * @brief Gets an index and returns the value associated to it.
     * Throws an exception if the index was not found.
     * @param index the index of the value in the vector.
     * @return the value that is associated to the index.
     */
    T at(const int index) const {}

    /**
     * @brief Adds a given value to the end of the vector.
     * @param val the value to add, given as an l-value.
     */
    void push_back(const T &val){}

    /**
     * @brief Adds a given value to the end of the vector.
     * @param val the value to add, given as an r-value.
     */
    void push_back(const T &&val){}

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an l-value.
     * @return an iterator that points to the added value.
     */
    iterator insert(const iterator &position, const T &val){}

    /**
     * @brief Adds a given value to the vector at the position before
     * the given position.
     * @param position the position to add the value before it.
     * @param val the value to add, given as an r-value.
     * @return an iterator that points to the added value.
     */
    iterator insert(const iterator &position, const T &&val){}

    /**
     * @brief Removes the last element from the vector.
     */
    void pop_back(){}

    /**
     * @brief Removes from the vector the value that the given iterator points to.
     * @param position an iterator that points to the value that is to be removed.
     * @return an iterator to the value that appeared after the removed value.
     */
    iterator erase(iterator &position){}

    /**
     * @brief Removes all elements from the vector.
     */
    void clear(){}

    /**
     * @brief Returns a pointer to the data type that currently contains the vector.
     * @return a pointer to the data type that currently contains the vector.
     */
    T *data() const
    {
        if (stackMode)
        {
            return &this->stackVec;
        }
        return this->heapVec;
    }

    /**
     * @brief Gets an index and returns a reference to the value associated to it.
     * Allows changing the value associated to the key.
     * @param index the given index.
     * @return a reference to the value associated to the index.
     */
    T &operator[](const int index) noexcept{}

    /**
     * @brief Gets an index and returns the value associated to it.
     * Does not allow changing the value associated to the key.
     * @param index the given index.
     * @return the value associated to the index.
     */
    T operator[](const int index) const noexcept{}

    /**
     * @brief Checks if this object equals to another VLVector object.
     * @param other the other VLVector object.
     * @return true iff the objects are the same.
     */
    bool operator==(const VLVector &other) const{}

    /**
     * @brief Checks if this object differs from another VLVector object.
     * @param other the other VLVector object.
     * @return true iff the objects differ from each other.
     */
    bool operator!=(const VLVector &other) const
    {
        return !operator==(other);
    }

    inline iterator begin(){return iterator();}
};


#endif //CPP_FINAL_PROJECT_VLVECTOR_HPP
