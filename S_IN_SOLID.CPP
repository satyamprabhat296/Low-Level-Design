 #include<iostream>
 #include<vector>

 using namespace std;


 // product class representing any item in ecommerce
 class Product{
    public:
    string name;
    double price;

    Product(string name, double price){
        this->name=name;
        this->price=price;

    }
 };

 //1. shopping cart : Only responsible for cart related business logic.
 class ShoppingCart{
    private:
    vector<Product*>products; // store heap-allocated products

    public : 
    void addProduct(Product*p){
        products.push_back(p);

    }
    const vector<Product*>&getProducts(){
        return products;
    }
    // calculates total price in cart.
    double calculateTotal(){
        double total =0;
        for(auto p:products){
            total+=p->price;
        }
        return total;
    }

 };


 // shoppingcartprinter : only reesponsible for printing invoices
 class ShoppingCartPrinter{
    private:
    ShoppingCart*cart;


    public:
    ShoppingCartPrinter(ShoppingCart*cart){
        this->cart=cart;
    }
    void printInvoice(){
        cout<<"Shopping cart Invoice:\n";
        for(auto p:cart->getProducts()){
            cout<<p->name<<"-$"<< p->price<<endl;
        }
        cout<<"Total:$"<< cart ->calculateTotal()<<endl;
    }
 };
 // 3.ShoppingCartStorage:Only responsible for saving cart to DB
 class ShoppingCartStorage{
    private:
    ShoppingCart*cart;

    public:
    ShoppingCartStorage(ShoppingCart*cart){
        this->cart=cart;
    }
        void saveToDatabase(){
            cout<<"saving shopping cart to database..."<<endl;
        }
    };
    int main(){
        ShoppingCart*cart = new ShoppingCart();
        cart->addProduct(new Product("Laptop", 1500));
        cart->addProduct(new Product("Mouse",50));

        ShoppingCartPrinter*printer= new ShoppingCartPrinter(cart);
        printer->printInvoice();
        ShoppingCartStorage*db= new ShoppingCartStorage(cart);
        db->saveToDatabase();

        return 0;

    }
 
