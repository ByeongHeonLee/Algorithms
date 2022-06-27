#include "search.h"

template <typename T>
size_t binary_search(const T list[], size_t size, const T &key)
{
    size_t start = 0;
    size_t end = size - 1;
    size_t mid;

    while (start <= end)
    {
        mid = (start + end) / 2;

        if (list[mid] == key)
        {
            while(mid > 0 && list[mid-1] == list[mid])
                --mid;

            return mid;
        }            
        else if (list[mid] < key)
            start = mid + 1;
        else // list[mid] > key
            end = mid - 1;
    }

    throw "Error: No keys found on the list";
}

template <typename T>
bool binary_search(const T list[], size_t size, const T &key, size_t &location)
{
    size_t start = 0;
    size_t end = size - 1;
    size_t mid;

    while (start <= end)
    {
        mid = (start + end) / 2;

        if (list[mid] == key)
        {
            while(mid > 0 && list[mid-1] == list[mid])
                --mid;

            location = mid;
            return true;
        } 
        else if (list[mid] < key)
            start = mid + 1;
        else // list[mid] > key
            end = mid - 1;
    }

    return false;
}

template <typename T>
queue<size_t> binary_search(const T list[], size_t size, const T &key)
{
    queue<size_t> locations;

    size_t start = 0;
    size_t end = size - 1;
    size_t mid;

    while (start <= end)
    {
        mid = (start + end) / 2;

        if (list[mid] == key)
        {
            while(mid > 0 && list[mid-1] == list[mid])
                --mid;

            locations.push(mid);

            while(mid < size-1 && list[mid+1] == list[mid])
                locations.push(++mid);

            return locations;
        } 
        else if (list[mid] < key)
            start = mid + 1;
        else // list[mid] > key
            end = mid - 1;
    }

    return locations;
}

template <typename T>
bool binary_search(const T list[], size_t size, const T &key, queue<size_t> &loc_vec)
{
    locations.clear();

    size_t start = 0;
    size_t end = size - 1;
    size_t mid;

    while (start <= end)
    {
        mid = (start + end) / 2;

        if (list[mid] == key)
        {
            while(mid > 0 && list[mid-1] == list[mid])
                --mid;

            locations.push(mid);

            while(mid < size-1 && list[mid+1] == list[mid])
                locations.push(++mid);

            return true;
        } 
        else if (list[mid] < key)
            start = mid + 1;
        else // list[mid] > key
            end = mid - 1;
    }

    return false;
}
