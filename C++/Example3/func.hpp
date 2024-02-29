#ifndef FUNC_HPP
#define FUNC_HPP
#include <vector>
namespace func {
int NOD(unsigned int a, unsigned int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        }
        else b = b % a;
    }
    if (a != 0)
        return a;
    else
        return b;
}

int NOD(int a, int b) {
    if (a < 0 && b < 0) {
        unsigned int a_pos = a*(-1);
        unsigned int b_pos = b*(-1);
        return -1*NOD(a_pos, b_pos);
    } else if (a < 0) {
        unsigned int a_pos = a*(-1);
        return NOD(a_pos, (unsigned int) b);
    } else if (b < 0) {
        unsigned int b_pos = b*(-1);
        return NOD((unsigned int) a, b_pos);
    } else {
        return NOD((unsigned int) a, (unsigned int) b);
    }
}

long long NOK(unsigned int a, unsigned int b) {
    return (long long) a * b / NOD(a, b);
}

template <class T>
T step(int a, unsigned int b) {
    if (b == 0) return 1;
    T c = 1;
    while (b != 0) {
        if (b % 2 == 1) {
            c = c * a;
            b--;
        }
        a = a * a;
        b = b / 2;
    }
    return c;
}

template <class T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <class T>
void QuickSort(int L, int R, T* M) {
    int i = L, j = R;
    int base = *(M +(R+L) / 2);
    while (i <= j) {
        while (*(M + i) < base && i < R) i++;
        while (*(M + j) > base && j > L) j--;
        if (i <= j) {
            swap(*(M + i), *(M + j));
            i++; j--;
        }
    }

    if (L < j && i < R) {
        QuickSort(L, j, M);
        QuickSort(i, R, M);
    }
    else {
        if (L < j)
            QuickSort(L, j, M);
        if (i < R)
            QuickSort(i, R, M);
    }
}

template <class T>
void QuickSort(int L, int R, std::vector<T>& M) {
    int i = L, j = R;
    T base = M[(R+L) / 2];
    while (i <= j) {
        while (M[i] < base && i < R) i++;
        while (M[j] > base && j > L) j--;
        if (i <= j) {
            swap(M[i], M[j]);
            i++; j--;
        }
    }

    if (L < j && i < R) {
        QuickSort(L, j, M);
        QuickSort(i, R, M);
    }
    else {
        if (L < j)
            QuickSort(L, j, M);
        if (i < R)
            QuickSort(i, R, M);
    }
}

template <class T>
int BinarySearch(int L, int R, std::vector<T>& Arr, T ser) {
    int i = (L + R - 1) / 2;
    bool flag = false;
    while(!flag) {
        int i_checkB{0}, i_checkL{0};
        while (Arr[i] > ser) {
            i = i - (L + R - i) / 2;
            i_checkB++;
            if (i_checkB % 2 == 0)
                i_checkB = i;
            flag = true;
        }

        while (Arr[i] < ser) {
            i = i + (L + R - i) / 2;
            i_checkL++;
            if (i_checkL % 2 == 0)
                i_checkL = i;
            flag = true;
        }

        if (Arr[i] != ser)
            flag = false;

        if (flag)
            return i;
        if (i_checkB == i || i_checkL == i)
            return -1;
    }
    return -2;
}
}

#endif // FUNC_HPP
