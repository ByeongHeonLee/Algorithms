#pragma once

// Header Files
#include <queue>

// Namespaces
using std::queue;

// Sequential Search
template<typename T>
size_t sequential_search(const T list[], size_t size, const T& key);

template<typename T>
bool sequential_search(const T list[], size_t size, const T& key, size_t& location);

template<typename T>
queue<size_t> sequential_search(const T list[], size_t size, const T& key);

template<typename T>
bool sequential_search(const T list[], size_t size, const T& key, queue<size_t>& loc_vec);

// Binary Search
template<typename T>
size_t binary_search(const T list[], size_t size, const T& key);

template<typename T>
bool binary_search(const T list[], size_t size, const T& key, size_t& location);

template<typename T>
queue<size_t> binary_search(const T list[], size_t size, const T& key);

template<typename T>
bool binary_search(const T list[], size_t size, const T& key, queue<size_t>& loc_vec);
