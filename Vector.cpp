//William Martell CS2370: Project 4

#include "Vector.h"
#include <stdexcept>

void Vector::grow() { //Grows the vector when the capacity is equal to n_elems.
    capacity *= 1.6;
    int* array = new int[capacity];
    for (int i=0; i < n_elems; ++i) {
        array[i] = data_ptr[i];
    }
    delete [] data_ptr;
    data_ptr = array;
}


Vector::Vector() //Constructor
    : n_elems(0),
      capacity(CHUNK),
      data_ptr(new int[capacity])
{
}


Vector::Vector(const Vector& v)  // Copy constructor
    : n_elems(v.n_elems),
      capacity(v.capacity),
      data_ptr(new int[capacity])
{
    for (int i=0; i< v.size(); ++i) {
        data_ptr[i] = v.data_ptr[i];
    }
}  


Vector& Vector::operator=(const Vector& v) {  // Copy assignment operator
    if (v.n_elems > n_elems) {
        delete [] data_ptr;
        capacity = v.n_elems * 1.6;
        data_ptr = new int[capacity];
    }
    for (int i = 0; i < v.size(); ++i){
        data_ptr[i] = v.data_ptr[i];
    }
    n_elems = v.n_elems;
    return *this;
}


Vector::~Vector() {  //Destructor
    delete[] data_ptr;
}


int Vector::front() const {  // Return the int in position 0, if any
    if (n_elems == 0)
        throw std::range_error("The vector is empty");
    else
        return *data_ptr;  
}  


int Vector::back() const {  // Return last element (position n_elems-1)
    if (n_elems == 0)
        throw std::range_error("The vector is empty");
    else
        return *data_ptr + n_elems - 1;
}


int Vector::at(size_t pos) const {  // Return element in position "pos" (0-based)
    if (pos >= n_elems)
        throw std::range_error("Position exceeds number of elements.");
    int number = *(data_ptr + pos);
    return number;
}


size_t Vector::size() const {  // Return n_elems
    return n_elems;    
}


bool Vector::empty() const {  // Return n_elems == 0
    return n_elems == 0;    
}


int& Vector::operator[](size_t pos) {  // Same as at but no bounds checking
    return data_ptr[pos];
}


void Vector::push_back(int item) {  // Append a new element at the end of the array
    if (n_elems < capacity) {
        data_ptr[n_elems] = item;
        ++n_elems;
    } else {
        grow();
        ++n_elems;  
    }    
}


void Vector::pop_back() {  // --n_elems (nothing else to do; returns nothing)
    if (n_elems == 0){
        throw std::range_error("You can't pop_back on an empty vector.");
    }
    --n_elems;
}


void Vector::erase(size_t pos) {  // Remove item in position pos and shuffles following items left
    if (n_elems == 0){
        throw std::range_error("You can't perform erase on an empty vector.");   
    }
    if ((pos < 0) || (pos >= n_elems)) {
        throw std::range_error("That position is out of range."); 
    }
    for (int i = pos; i < n_elems-1; ++i) {
        data_ptr[i] = data_ptr[i + 1];
    }
    --n_elems;
}


void Vector::insert(size_t pos, int item) {  // Shuffle items right to make room for a new element
    if (n_elems != capacity) {
        for (int i = n_elems-1; i >= pos; --i) {
            data_ptr[i+1] = data_ptr[i];
            if (i <= 0) {
                break;
            }
        }
        data_ptr[pos] = item;
        ++n_elems;
    } 
    else {
        grow();
        insert(pos,item);
    }    
}


void Vector::clear() {  // n_elems = 0 (nothing else to do; keep the current capacity)
    n_elems = 0;    
}


int* Vector::begin() {  // Return a pointer to 1st element, or nullptr if n_elems == 0
if (n_elems == 0) {
    return nullptr;
} else {
    return data_ptr;
}   
}


int* Vector::end() {  // Return a pointer to 1 past last element, or nullptr if n_elems == 0
    if (n_elems == 0) {
        return nullptr; 
    } else {
        return data_ptr + n_elems;
    }   
}


bool Vector::operator==(const Vector& v) const {
    if (size() != v.size()) {
        return false;
    }

    for (int i=0; i< size(); i++) {
        if (data_ptr[i] != v.data_ptr[i]){
            return false;
        }
    }
    return true;
}


bool Vector::operator!=(const Vector& v) const {
    return !(*this == v);    
}
