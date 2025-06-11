#include "vault.h"
#include <string>


//class for Painting
class Painting {
public:
    std::string title;
    std::string artist;
    int year;
    double price;

    Painting(std::string title, std::string artist, int year, double price)
        : title(std::move(title)), artist(std::move(artist)), year(year), price(price) {}

    bool operator==(const Painting& other) const {
        return title == other.title && artist == other.artist && year == other.year;
    }

    bool operator!=(const Painting& other) const {
        return !(*this == other);
    }
};

int main() {
    // vault for ints
    Vault<Painting> paintingVault;
    Painting p1("Mona Lisa", "Leonardo da Vinci", 1503, 100000000);
    Painting p2("The Last Supper", "Leonardo da Vinci", 1498, 200000000);
    Painting p3("The Starry Night", "Vincent van Gogh", 1889, 300000000);
    Painting p4("Self Portrait: IV", "Tony Lyu", 2021, 0);


    // vault items
    VaultItem<Painting> t1(p1, p1.title, p1.price, p1.year, "Museum", 1);
    VaultItem<Painting> t2(p2, p2.title, p2.price, p2.year, "Museum", 2);
    VaultItem<Painting> t3(p3, p3.title, p3.price, p3.year, "Museum", 3);
    VaultItem<Painting> t4(p4, p4.title, p4.price, p4.year, "Tony", 4);

    vector<VaultItem<Painting>> items;
    items.push_back(t3);
    items.push_back(t4);

    paintingVault.storeItem(t1);
    paintingVault.storeItem(t2);
    paintingVault.storeItems(items);

    // Tony's self portrait is sold to admirer for 25 bucks
    VaultItem<Painting> t4New(p4, p4.title, 25, p4.year, "Tony's Admirer", 4);
    paintingVault.storeItem(t4New);

    // Display the number of items
    std::cout << "Items in vault: " << paintingVault.getCount() << std::endl;

    // Since Tony's self portrait is sold, take it out of the vault
    paintingVault.remove(4);

    // Display the number of items after removal
    std::cout << "Items in vault after removal: " << paintingVault.getCount() << std::endl;

    return 0;
}
