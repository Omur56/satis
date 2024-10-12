#include <iostream>
#include <cstring>
using namespace std;

class Product {
private:
    int id;
    string name;
    string description;
    double price;
    double discount;  // Bir faiz olaraq endirim (0-100)

public:
    // Konstruktor
    Product(int id = 0, string name = "", string description = "", double price = 0.0, double discount = 0.0) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->price = price;
        this->discount = discount;
    }

    // Getter ve Setter ucun ID
    int getId() const {
        return id;
    }
    void setId(int id) {
        this->id = id;
    }

    // Getter ve Setter ucun Name
    string getName() const {
        return name;
    }
    void setName(string name) {
        this->name = name;
    }

    // Getter ve Setter ucun Description
    string getDescription() const {
        return description;
    }
    void setDescription(string description) {
        this->description = description;
    }

    // Getter ve Setter ucun Price
    double getPrice() const {
        return price;
    }
    void setPrice(double price) {
        this->price = price;
    }

    // Getter ve Setter ucun Discount
    double getDiscount() const {
        return discount;
    }
    void setDiscount(double discount) {
        this->discount = discount;
    }

    // Məhsul təfərrüatlarını göstərmək üçün funksiya
    void showProduct() const {
        cout << "Mehsul ID: " << id << "\n";
        cout << "Ad: " << name << "\n";
        cout << "Tesvir: " << description << "\n";
        cout << "Qiymet: $" << price << "\n";
        cout << "Endirim: " << discount << "%\n";
        cout << "Endirimden sonra qiymet: $" << getPriceWithDiscount() << "\n";
        cout << "------------------------\n";
    }

    // endirimdən sonra qiyməti hesablamaq üçün funksiya
    double getPriceWithDiscount() const {
        return price * (1 - discount / 100);
    }
};

class Stock {
private:
    char* address;
    Product* products;
    int count;  // Məhsulların sayı
    int capacity; // Dinamik serial üçün tutum

    // məhsul serialını ölçmək üçün xüsusi funksiya
    void resizeProducts(int newCapacity) {
        Product* newProducts = new Product[newCapacity];
        for (int i = 0; i < count; i++) {
            newProducts[i] = products[i];
        }
        delete[] products;
        products = newProducts;
        capacity = newCapacity;
    }

public:
    // konstruktor
    Stock(const char* address = "", int initialCapacity = 2) {
        this->address = new char[strlen(address) + 1];
        this->address, address;
        count = 0;
        capacity = initialCapacity;
        products = new Product[capacity]; // Məhsullar üçün yaddaş ayırın
    }

    // Destructor
    ~Stock() {
        delete[] address;
        delete[] products;
    }
    // Bütün məhsulları stokda göstərmək üçün funksiya
    void showStock() const {
        cout << "Stok ve unvan: " << address << "\n";
        cout << "Umumi mehsullar: " << count << "\n";
        for (int i = 0; i < count; i++) {
            products[i].showProduct();
        }
    }
    // Bir məhsulu id ilə silmək üçün funksiya
    void DeleteProduct(int id) {
        int index = -1;
        for (int i = 0; i < count; i++) {
            if (products[i].getId() == id) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < count - 1; i++) {
                products[i] = products[i + 1];
            }
            count--;
            cout << "ID ile mehsul " << id << " silindi.\n";
        }
        else {
            cout << "ID ile mehsul " << id << " Tapilmadi.\n";
        }
    }

    // Bir məhsulun ID-nin endirimini dəyişdirmək üçün funksiya
    void ChangeProductDiscount(int id, double newDiscount) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (products[i].getId() == id) {
                products[i].setDiscount(newDiscount);
                found = true;
                cout << "Mehsul ID ucun endirim" << id << " YENILENIB " << newDiscount << "%.\n";
                break;
            }
        }
        if (!found) {
            cout << "ID ile mehsul " << id << " Tapilmadi.\n";
        }
    }

    // id ilə bir məhsul axtarmaq üçün funksiya
    Product SearchProduct(int id) const {
        for (int i = 0; i < count; i++) {
            if (products[i].getId() == id) {
                return products[i];
            }
        }
        return Product();  // tapılmadıqda standart bir məhsulu qaytarın
    }

    // yeni bir məhsul yaratmaq və stoka əlavə etmək üçün funksiya
    void CreateProduct(int id, string name, string description, double price, double discount) {
        if (count == capacity) {
            resizeProducts(capacity * 2);  // limiti çatdıqda tutumu iki dəfə artırın
        }
        products[count] = Product(id, name, description, price, discount);
        count++;
        cout << "ID ile mehsul " << id << " Elave edildi.\n";
    }

    // id ilə bir məhsul əldə etmək üçün funksiya
    Product getProduct(int id) const {
        return SearchProduct(id);
    }
};

int main() {
    // bir ünvan və ilkin tutumlu bir fond yaradın
    Stock stock("123 Esas st");

    // məhsulları yaradın
    stock.CreateProduct(1, "Laptop", "Yuksek effektiv bir noutbuk", 1200.00, 10.0);
    stock.CreateProduct(2, "Smartfon", "Yeni nesil smartfon", 800.00, 15.0);

    // cari fondu göstərin
    stock.showStock();

    // bir məhsul endirimini dəyişdirin
    stock.ChangeProductDiscount(1, 20.0);

    // endirim dəyişdikdən sonra səhmləri göstərin
    stock.showStock();

    // bir məhsul axtarın
    Product p = stock.SearchProduct(1);
    cout << "Axtarish mehsulu: \n";
    p.showProduct();

    // Bir məhsulu şəxsiyyət sənədini silin
    stock.DeleteProduct(2);

    // silindikdən sonra səhmləri göstərin
    stock.showStock();

    return 0;
}

