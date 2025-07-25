#include <vector>

template <class T>
class Heap {
    std::vector<T> data;
public:
    Heap<T>();
    ~Heap<T>();
    void push_back();
    void insert(const T& element);
    T& borrowTop();
    const T& borrowTop() const;
    T extractTop();

private:
    void siftUp(int idx);
    void sifgtDown(int idx);

public:
    bool isEmpty();
    int size();
};