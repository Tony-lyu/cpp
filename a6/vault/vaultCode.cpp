#include "vault.h"
#include <string>


//class for Code
class Code {
public:
    std::string company;
    int lines;
    string author;

    Code(std::string company, int lines, std::string author)
        : company(std::move(company)), lines(lines), author(std::move(author)) {}

    bool operator==(const Code& other) const {
        return company == other.company && author == other.author && lines == other.lines;
    }

    bool operator!=(const Code& other) const {
        return !(*this == other);
    }
};

int main() {
    // vault for codes
    Vault<Code> codeVault;
    Code p1("Google Chrome", 31000000, "Google employee");
    Code p2("VS Code", 50000000, "VS Code employee");
    Code p3("Amazon", 60000000, "Amazon employee");
    Code p4("Snake Game", 1200, "Tony et. al.");


    // vault items
    VaultItem<Code> t1(p1, "Chrome source code", 99999999, 2000, "Google", 1);
    VaultItem<Code> t2(p2, "VS Code source code", 99999999, 2010, "VS Code", 2);
    VaultItem<Code> t3(p3, "Amazon source code", 99999999, 2002, "Amazon", 3);
    VaultItem<Code> t4(p4, "Snake Game source code", 0, 2024, "Tony", 4);

    vector<VaultItem<Code>> items;
    items.push_back(t3);
    items.push_back(t4);

    codeVault.storeItem(t1);
    codeVault.storeItem(t2);
    codeVault.storeItems(items);

    // An anonymous buyer is willing to pay 50 bucks for Tony's Masterpiece
    // -- The Snake Game 
    VaultItem<Code> t4New(p4, "Snake Game source code", 50, 2024, "Tony's Admirer", 4);
    codeVault.storeItem(t4New);

    // Display the number of items
    std::cout << "Items in vault: " << codeVault.getCount() << std::endl;

    // After careful investigation, the anonymous buyer is someone who is 
    // taking c++ next semester. The cheating behavior is absolutely not
    // tolorable. So Tony has to revoke the purchase and remove Snake from
    // the vault. 
    codeVault.remove(4);

    // Display the number of items after removal
    std::cout << "Items in vault after removal: " << codeVault.getCount() << std::endl;

    return 0;
}
