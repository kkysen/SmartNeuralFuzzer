//
// Created by Khyber on 6/3/2019.
//

#include <list>
#include <iostream>

/**
 * Test if std::list's iterators are not invalidated after deleting other elements.
 *
 * Answer: true
 */
int main() {
    std::list<int> L;
    const auto a = L.emplace(L.end(), 0);
    const auto b = L.emplace(L.end(), 1);
    const auto c = L.emplace(L.end(), 2);
    const auto d = L.emplace(L.end(), 3);
    const auto e = L.emplace(L.end(), 4);
    L.erase(b);
    L.erase(d);
    L.erase(c);
    std::cout << "a = " << *a << std::endl;
    std::cout << "e = " << *e << std::endl;
    for (const auto i : L) {
        std::cout << i << std::endl;
    }
}
