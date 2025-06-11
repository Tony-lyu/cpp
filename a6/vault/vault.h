#ifndef VAULT_HPP
#define VAULT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>

using namespace std;

template<typename T>
struct VaultItem {
    T item;
    string name;
    double price;
    int age; 
    string owner;
    int id;

    VaultItem(T item, string name, double price, int age, string owner, int id)
        : item(item), name(move(name)), price(price), age(age), owner(move(owner)), id(id) {}

    bool operator==(const VaultItem& other) const {
        return id == other.id;
    }
};

template<typename T>
class Vault {
private:
    vector<VaultItem<T>> items;

public:
    // Store an item, or update info if item is already in the vault
    void storeItem(const VaultItem<T>& newItem) {
        auto it = find(items.begin(), items.end(), newItem);
        if (it != items.end()) {
            *it = newItem; 
        } else {
            items.push_back(newItem); 
        }
    }

    // Add a vector of items at the same time
    void storeItems(const vector<VaultItem<T>>& newItems) {
        for (const auto& item : newItems) {
            storeItem(item);
        }
    }

    // return the age of given item
    int getAge(int itemId) const {
        auto it = find_if(items.begin(), items.end(), [itemId](const VaultItem<T>& item) {
            return item.id == itemId;
        });
        if (it != items.end()) {
            return it->age;
        }
        return -1; // not found
    }

    // Remove an item
    void remove(int itemId) {
        items.erase(remove_if(items.begin(), items.end(), [itemId](const VaultItem<T>& item) {
            return item.id == itemId;
        }), items.end());
    }

    // Return the number of items in the vault
    size_t getCount() const {
        return items.size();
    }
};

#endif 
