#include <iostream>
using namespace std;

class Currency{
    private:
        int doller, cent;
    public:
        Currency(int doller, int cent):doller(doller), cent(cent){}
        ~Currency(){}
        Currency operator+(const Currency &r){
            int all_doller = doller + r.doller;
            int all_cent = cent + r.cent;
            if(all_cent>100){
                all_cent -= 100;
                all_doller++;
            }
            return Currency(all_doller,all_cent);
        }
        Currency operator-(const Currency &r){
            int all_doller = doller - r.doller;
            int all_cent = cent - r.cent;
            if (all_cent<0){
                all_cent += 100;
                all_doller--;
            }
            if(all_doller<0) return Currency(0,0);

            return Currency(all_doller,all_cent);
        }

        friend ostream &operator<<(ostream &os, Currency &r);
        friend istream &operator>>(istream &is, Currency &r);
};
ostream &operator<<(ostream &os, Currency &r){
    os << "Your Money : " << r.doller << " Doller " << r.cent << " Cent" << endl;
    return os;
}
istream &operator>>(istream &is, Currency &r){
    cout << "Changing doller : ";
    is >> r.doller;
    cout << "Changing cent : ";
    is >> r.cent;
    if (r.cent < 0)
    {
        r.cent += 100;
        r.doller--;
    }
    if (r.cent > 100){
        r.cent -= 100;
        r.doller++;
    }
    return is;
}

int main(){
    Currency a(10,25);
    Currency b(15,95);
    cout << a;
    cin >>a;
    cout <<a << endl;
    Currency temp = a+b;
    cout << temp << endl;
    temp = a-b;
    cout << temp << endl;

    return 0;
}