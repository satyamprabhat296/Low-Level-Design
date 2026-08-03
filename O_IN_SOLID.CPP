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
    public:
    void addProduct(Product*p){
        products.push_back(p);
    }
    const vector<Product*> &getProducts(){
        return products;
    }

    // calculate total price in cart
    double calculateTotal(){
        double total=0;
        for(auto p:products){
            total+=p->price;

        }
        return total;
    }
    };
    //2.shoppingcartPrinter: only responsible for printing invoices
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
 // ABSTRACT CLASS
 class Persistence{
    private:
    ShoppingCart*cart;

    public:
    virtual void save (ShoppingCart*cart)=0;  // pure virtual function
 };
 class SQLPersistence: public Persistence{
    public:

    void save (ShoppingCart*cart) override{
        cout<< " Saving Shopping cart to SQL DB..."<<endl;

    }
 };
 class MongoPersistence:public Persistence{
    public:
        void save (ShoppingCart*cart) override{
cout<<" saving shopping cart to Mongo DB..."<<endl;
 }
 };

 class FilePersistence : public Persistence{
    public:
        void save (ShoppingCart*cart) override{
            cout<<"saving shopping cart to a file..."<<endl;
        }
 };
 int main(){
    ShoppingCart*cart= new ShoppingCart();
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",150));
    ShoppingCartPrinter*printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();
    Persistence*db = new SQLPersistence();
    Persistence*mongo=  new MongoPersistence();
    Persistence*file= new FilePersistence();
    db->save(cart);
    mongo->save(cart);
    file->save(cart);
    return 0;

 }