#include "vault.h"
#include <string>

int main() {
    // vault for strings
    Vault<std::string> stringVault;

    // vault items
    VaultItem<std::string> t1("ticket", "concert ticket", 125, 2024, "Tony", 1);
    VaultItem<std::string> t2("ticket2", "plane ticket", 200, 2024, "Tony", 2);
    VaultItem<std::string> t3("ticket3", "game ticket", 30, 2024, "Tony", 3);
    VaultItem<std::string> t4("ticket4", "NBA ticket", 235, 2024, "Tony", 4);

    vector<VaultItem<std::string>> items;
    items.push_back(t3);
    items.push_back(t4);

    stringVault.storeItem(t1);
    stringVault.storeItem(t2);
    stringVault.storeItems(items);

    // Gotta support the artists, Tony decides to buy a better seat for the concert
    VaultItem<std::string> t1New("ticket", "concert ticket front seat", 500, 2024, "Tony", 1);
    stringVault.storeItem(t1New);

    // Display the number of items
    std::cout << "Items in vault: " << stringVault.getCount() << std::endl;

    // JT is overrated. Tony is not spending 200+ to watch JT crying on the floor 
    // like a baby, no way. 
    stringVault.remove(4);

    // Display the number of items after removal
    std::cout << "Items in vault after removal: " << stringVault.getCount() << std::endl;

    return 0;
}
