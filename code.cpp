template <class T> class SegmentTree {
private:
    const T DEFAULT = 0;
    vector<T> segtree;
    int len;

public:
    T f(T a, T b) { return a + b; }
    SegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

    void set(int ind, T val) {
        ind += len;
        segtree[ind] = val;
        for (; ind > 1; ind /= 2) {
            int ID1 = ind, ID2 = ind ^ 1;
            if (ID1 > ID2) swap(ID1, ID2);
            segtree[ind / 2] = f(segtree[ID1], segtree[ID2]);
        }
    }

    T range(int start, int end) {
        T sum1 = DEFAULT;
        T sum2 = DEFAULT;
        for (start += len, end += len; start < end; start /= 2, end /= 2) {
            if (start % 2 == 1) { sum1 = f(sum1, segtree[start++]); }
            if (end % 2 == 1) { sum2 = f(segtree[--end], sum2); }
        }
        return f(sum1, sum2);
    }
};