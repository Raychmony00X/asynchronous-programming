#include <list>
#include <future>
#include <iostream>

void SelectionSort(std::list<int>& unordered_list, std::promise<std::list<int>> promise) {
	if (unordered_list.empty()) {
		promise.set_value(unordered_list);
		return;
	}

	auto it = unordered_list.begin();
	while (it != unordered_list.end()) {
		auto min = it;
		auto scan = std::next(it);
		while (scan != unordered_list.end()) {
			if (*scan < *min) {
				min = scan;
			}
			++scan;
		}

		if (min != it) {
			std::iter_swap(it, min);
		}

		++it;
	}

	promise.set_value(unordered_list);
}

int main() {
	std::list<int> unordered_list = { 29, 10, 14, 37, 13, 55, 2, 48, 61, 7 };
	std::promise<std::list<int>> promise;
	auto result = promise.get_future();
	std::jthread jthread(SelectionSort, std::ref(unordered_list), std::move(promise));
	std::list<int> sorted_list = result.get();
	for (auto i : sorted_list) {
		std::cout << i << " ";
	}

	std::cout << std::endl;

	return 0;
}