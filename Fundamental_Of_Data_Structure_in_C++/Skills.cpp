#include <iostream>
#include <random>
#include <memory>
#include <vector>
using namespace std;


void RandomFunction(){
    /*
    이 외에도 다양하게 Bernoulli, Normal distribution등이 
    있으니 필요시 찾아볼 것.
    */
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0,99);

    int randNum = dist(mt);
    cout << randNum;
}

template<typename Container, typename Index>
decltype(auto)
authAndAccess(Container&& c, Index i) // &&는 lvalue rvalue를 모두 받을 수 있게 하는 것.
{
    // authenticateUser();
    return forward<Container>(c)[i];
}

// type을 정확히 알고 싶을 때
// template<typename T>
// void print_type(const T& param){
//     using boost::typeindex::type_id_with_cvr; // 이건 boost 라이브러리를 깔아야만 가능하다.

//     cout << "T : " << type_id_with_cvr<T>().pretty_name() << endl;
//     cout << "param : " << tpye_id_with_cvr<T>().pretty_name() << endl;
// }


int main()
{
    vector<bool> feature;

    int x = 10;
    string y = "Hello";

    return 0;
}
