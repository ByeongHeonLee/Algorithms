#include "search.h"

template <typename T>
size_t sequential_search(const T list[], size_t size, const T &key)
{
    size_t idx = 0;

    while (idx < size && list[idx] != key)
        idx++;

    if (idx >= size)
        throw "Error: No keys found on the list";

    return idx;
}

template <typename T>
bool sequential_search(const T list[], size_t size, const T &key, size_t &location)
{
    size_t idx = 0;

    while (idx < size && list[idx] != key)
        idx++;

    if (idx >= size)
        return false;

    location = idx;
    return true;
}

template <typename T>
queue<size_t> sequential_search(const T list[], size_t size, const T &key)
{
    size_t idx = 0;
    queue<size_t> locations;

    while (idx < size)
    {
        if (list[idx] == key)
            locations.push(idx);
        idx++;
    }

    return locations;
}

template <typename T>
bool sequential_search(const T list[], size_t size, const T &key, queue<size_t> &locations)
{
    size_t idx = 0;
    locations.clear();

    while (idx < size)
    {
        if (list[idx] == key)
            locations.push(idx);
        idx++;
    }

    if (locations.empty())
        return false;

    return true;
}
