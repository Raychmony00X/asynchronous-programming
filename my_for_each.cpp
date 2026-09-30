#include <vector>
#include <future>
#include <iostream>
#include <thread>

void Decrement(int& x) {
    --x;
}

template<typename Iterator, typename Func>
void ForEach(Iterator it_begin, Iterator it_end, Func& func) {
    auto dist = std::distance(it_begin, it_end);
    if (dist <= 0) return;

    if (dist == 1) {
        func(*it_begin);
        return;
    }

    auto mid = std::next(it_begin, dist / 2);
    std::jthread t([&] { ForEach(it_begin, mid, func); });
    ForEach(mid, it_end, func);
}

int main() {
    std::vector<int> v = { 2, 3, 4, 5, 6, 7 };

    {
        std::jthread thread{ ForEach<decltype(v.begin()), decltype(Decrement)>,
                             v.begin(), v.end(), std::ref(Decrement) };
    } 

    for (int x : v) std::cout << x << ' ';
    std::cout << std::endl;

    return 0;
}