#include "vault.h"
#include <string>

int main() {
    // vault for ints
    Vault<int> intVault;

    // vault items
    VaultItem<int> t1(25, "piggy bank", 25, 2008, "Tony", 1);
    VaultItem<int> t2(650, "phone", 650, 2021, "Tony", 2);
    VaultItem<int> t3(999, "macbook", 999, 2019, "Tony", 3);
    VaultItem<int> t4(150000, "college fund", 150000, 2020, "Tony", 4);

    vector<VaultItem<int>> items;
    items.push_back(t3);
    items.push_back(t4);

    intVault.storeItem(t1);
    intVault.storeItem(t2);
    intVault.storeItems(items);

    // Opps, someone break into the vault, and broke Tony's
    // most precious piggy bank. Damn it!
    VaultItem<int> t1New(0, "piggy bank", 0, 2024, "Tony", 1);
    intVault.storeItem(t1New);

    // Display the number of items
    std::cout << "Items in vault: " << intVault.getCount() << std::endl;

    // Dear piggy bank, your flesh may decay, your soul lingers on...
    intVault.remove(1);

    // Display the number of items after removal
    std::cout << "Items in vault after removal: " << intVault.getCount() << std::endl;

    return 0;
}
