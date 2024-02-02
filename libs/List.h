#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

template <typename T>
struct List {
    T elements[100];
    int size;

    List() {
        size = 0;
    }

    void add(T element) {
        elements[size] = element;
        size++;
    }

    bool remove(int index) {

        if (index < 0 || index >= size) {
            return false;
        }

        for (int i = index; i < size - 1; i++) {
            elements[i] = elements[i + 1];
        }
        size--;

        return true;
    }

    T get(int index) {
        return elements[index];
    }

    bool contains(T element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        size = 0;
    }

    List<T> copy() {
        List<T> newList;

        for (int i = 0; i < size; i++) {
            newList.add(elements[i]);
        }

        return newList;
    }

    string toString() {
        string result = "[";
        for (int i = 0; i < size; i++) {
            result += elements[i];
            if (i < size - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    bool operator==(List<T> other) {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }

        return true;
    }
};

#endif /* MYHEADER_H */