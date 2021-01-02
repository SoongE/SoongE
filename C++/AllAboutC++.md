# C++

## 1. C++의 특징, GC, Exception

* 비용이 들지 않는 추상화
C++은 Satck에 객체를 배치하지만 java는 객체들이 힙 공간에 별도로 할당되어있다.

* 참조를 이용한 null 객체의 해방
    다음 코드는 null 값이 허용되지 않는 참조로 전달된다.
    ```cpp
    auto get_volume1(const Sphere& s){
        auto cube = pow(s.radius(),3);
        return cube * 3.14f;
    }
    ```
    다음 코드에서는 인수가 널값이 처리될 수 있음을 보여주는 포인터로 전달된다.
    ```cpp
    auto get_volume2(const Sphere* s){
        auto cube = pow(s.radius(),3);
        return cube * 3.14f;
    }
    ```

* ***클레스 인터페이스와 예외처리***
C++의 고성능에 대한 개념으로 더 깊이 들어가기 전에 C++코드를 작성하면서 분명히 해둘 몇가지 개념을 강조하고자 한다.
    * 엄격한 클래스 인터페이스
        ```cpp
        class Boat{
            private:
                Boat(const Boat& b) = delete;
                auto operator=(const Boat& b) -> Boat& = delete;
        }
        ```
        `Boat`클래스를 복사하지 못하도록 하는 방법

## 2. Move Semantics, Forwarding References, optional, any, lambda

* function signatures 에 auto 서명
  ```cpp
  auto x = Foo{} 와 Foo x{}는 같다.
  ```
* const 참조
  const참조는 어느 것과도 바인드 가능. const로 생성된 변수는 불변이므로 수정을 원하지 않는 변수에 대한 기본적인 선택이다.

* 가변참조
  `auto&`는 감변 참조를 표시하며, 객체 참조를 변경하고자 하는 경우에만 사용한다. 또한 임시 객체와 바인드되지 않는다.

* 전달 참조
  `auto&&`은 어떤것과도 바인드 할 수 있고 임시 객체의 수명을 확장한다. 하지만 `const참조`와는 다르게 임시 객체를 포함한 해당 객체 참조의 변경을 허용한다.

  `auto&&`을 사용하면 다른 코드에 변수를 전달한다. 전달 과정에서 변수가 const인지 변경 가능한지를 염려할 필요가 거의 업고, 일부 코드에 실제 사용할 변수를 전달해주면 된다.

> 결론적으로 가능하면 `const auto&`를 항상 사용할 것을 권하고, 그로 인해 다른 의심스러운 작업 없이 값만 읽어가기를 원한다는 의사표현을 할 수 있다. 

* Lambda Function
  ```cpp
  class Foo{
      public:
        auto member_function(){
            auto a = 0;
            auto b = 1.0f;
            // 복사로 모든 변수 캡쳐
            auto lambda0 = [=]() {cout<<a<<b<<m_;};
            // 참조로 모든 변수 캡쳐
            auto lambda0 = [&]() {cout<<a<<b<<m_;};
            // 참조로 멤버 변수 캡쳐
            auto lambda0 = [this]() {cout<<m_;};
            // 복사로 멤버 변수 캡쳐
            auto lambda0 = [this*]() {cout<<m_;};
        }
      private:
        int m_{};
  }
  ```

* 이동의미론
  * 객체 복사 생성
    객체를 복사할 때는 새로운 자원이 할당돼야 하며, 원본 객체에서의 자원이 복사돼 두 개의 객체가 완전히 구분돼야 한다. `auto a = Object{}; auto b=a;`
  * 두 객체의 교환
    객체의 포인터만 서로 교환된다.
  * 객체 이동 생성
    생성될 객체가 먼저 원본 객체의 자원을 가져오고 나서 원본 객체의 초기화가 이루어진다.
  * noexcept
    이동생성자와 이동할당자를 생성할 때는 `noexcept`로 표시하는것을 잊지 말자


## 3. STL Container
각 컨테이너를 간단히 소개하고 선으 위주로 무엇을 중요하게 고려해야 하는지 알아본다.

### 1. Sequence Container - array,vector,deque,basic_string,list,forward_list
시퀀스 컨테이너를 선택하기 전에 알아야 할 사항은 다음과 같다.
  * 요소의 개수(계산 차수(order of magnitude))
  * 사용 유형 : 데이터 추가 횟수, 데이터 읽기/순회, 데이터 삭제/재정렬
  * 요소의 정렬이 필요한가

#### Vector
벡터는 가장 널리 사용되는 컨테이너 유형이며, 필요할 때 `동적`으로 확장하는 배열이다. 벡터에 추가된 요소는 메모리에서 **인접하게 배치**되는 것이 보장되는데, 일정한 시간 내에 인덱스를 사용해 배열 안의 요소에 접근할 수 있다. 또한 공간 구역성 덕택에 배치된 순서대로 요소들을 순회할 때 성능이 뛰어나다. 벡터는 `크기`와 `용량`을 가지고 있는데 크기는 보유한 요소의 수이고, 용량은 벡터가 추가로 공간을 할당하기 전까지 가질 수 있는 요소이다.

새로 생성한 객체를 벡터에 추가하는 경우에는 `emplace_back` 함수를 활용하는데, 이 함수는 객체를 생성하고 나서 `push_back`함수로 벡터에 복사하거나 이동하는 대신, 객체를 올바른 위치에 생성한다
> 따라서, 왠만하면 push_back보다는 emplace_back을 사용하는 것이 성능면에서 더 좋다.

또한, 벡터의 용량은 다음과 같은 방법으로 변경할 수 있다.
* 용량과 크기가 같아졌을 때 벡터에 요소 추가
* reserve()를 호출
* shrink_to_fit()을 호출

#### Deque(데크)
요소를 맨 마지막이나 `앞`에 추가할 때 사용한다. 일정 시간에 해당 인덱스를 사용해 요소에 접근할 수 있지만, 모든 요소가 벡터처럼 메모리에 인접 배치되지는 않는다.

#### List & Forward_list
리스트는 각각의 요소가 이전요소와 다음요소로 연결되어 있는 `양쪽으로 연결된 리스트`이다. 이 리스트는 순방향이나 역방향으로 반복 연산할 수 있다. 반면 역방향을 가리키는 포인터가 **지나치게 메모리를 차지**할 수 있기 때문에 필요한 경우가 아니라면 지향한다. 따라서 역방향 리스트를 순회할 필요가 없다면 `단방향 리스트`인 `forward_list`를 사용하는 것을 추천한다. 순방향 리스트는 짧은 리스트에 최적화돼 있는데 리스트가 비어있는 경우 1워드의 용량만 차지한다. 

요소들이 시퀀스 내에 정렬되 있는 겨우라도 벡터처럼 메모리에서 인접해 있지 않을 수 있다는 점을 유념해야 한다. 이는 연결된 리스트로 반복연산을 할 때 벡터에 비해 캐시의 적중에 실패하는 경우가 많이 발생할 수 있다는 의미이다.

### 2. Associative Container
연관 컨테이너는 요소 자신을 기준으로 다른 요소를 위치시킨다. 요소를 앞이나 뒤에 추가할 수는 없지만 컨테이너를 검색하지 안호도 요소를 찾을 수 있도록 요소가 추가된다. 그러므로 연관 컨테이너는 컨테이너에 저장할 객체에 대해 약간의 요구 사항이 생긴다. 이런 요구사항은 나중에 살펴본다. 연관 컨테이너는 다음과 같이 크게 두 가지 종류로 나뉜다.
* 정령된 연관 컨테이너 : Tree구조를 기반으로 하는 컨테이너이다. 요소를 저장하기 위해 트리를 사용하고 비교 연산자(<)를 사용해 요소들이 정렬돼 있어야 한다. 트리 기반 컨테이너는 모두 O(log n)이며 `set`,`map`,`multiset`,`multimap`등이 있다.
* 비정렬 연관 컨테이너 : Hash테이블을 기반으로 하는 컨테이너이다. 이러한 컨테이너는 요소를 저장하고자 *해시 테이블*을 사용하고 동등연산자(==)를 사용해 요소를 비교할 수 있으면서 요소의 해시 값을 계산할 방법이 있어야한다. 모두 O(1)이며 `unordered_set`,`unordered_map`,`unordered_multiset`,`unordered_multimap`등이 있다.
다음은 해쉬 테이블을 만드는 한가지 예이다.
```cpp
auto person_eq = [](const Person& lhs, const Person& rhs){ // Person class는 name과 age를 가지고 있고, 동등한지 판단하는것 부터 시작한다.
  return lhs.name() == rhs.name() && lhs.age() == rhs.age();
};

auto person_hash = [](const Person& person){ // 해시값을 조합해서 해시값을 검증한다. Boost라이브러리를 활용한다.
  auto seed = size_t{0};
  boost::hash_combine(seed,person.name());
  boost::hash_combine(seed,person.age());
  return seed;
};

using Set = unordered_set<Person, decltype(person_hash),decltype(person_eq)>;
auto persons = Set{100,person_hash,person_eq};
```
해시값을 생성할 때 동등 함수에서 활용되는 **모든 데이터 멤버**를 사용하는 것이 경험적으로 좋은 방법이다. 동등함수와 해시 간의 약속을 지킬 수 있고, 결과적으로 효과적인 해시 값을 얻을 수 있다.

### 3. Container Adapter
STL에는 3 종류의 어댑터로 `stack`,`queue`,`priority_queue`가 있다. 

> 각각의 성능들이 얼마나 좋은지 비교할 때 `ScopedTimer`를 사용하면 좋다.

## 4. ScopedTimer
작성한 각각의 함수들의 성능을 측정하기 위해 사용하면 좋다. 다음과 같이 사용하면 되지 잘 숙지해놓으면 큰 도움이 될 것 같다.
```cpp
#include <chrono>

#define USE_TIMER 1
#if USE_TIMER
#define MEASURE_FUNCTION() ScopedTimer timer{__func__}
#else
#define MEASURE_FUNCTION()
#endif

class ScopedTimer {
public:
    using ClockType = std::chrono::steady_clock;

  ScopedTimer(const char* func)
    : function_{func}, start_{ClockType::now()} {
  }

  ScopedTimer(const ScopedTimer&) = delete;
  ScopedTimer(ScopedTimer&&) = delete;
  auto operator=(const ScopedTimer&) -> ScopedTimer& = delete;
  auto operator=(ScopedTimer&&) -> ScopedTimer& = delete;

  ~ScopedTimer() {
    using namespace std::chrono;
    auto stop = ClockType::now();
    auto duration = (stop - start_);
    auto ms = duration_cast<milliseconds>(duration).count();
    std::cout << ms << " ms " << function_ <<  '\n';
  }

private:
  const char* function_ = {};
  const ClockType::time_point start_ = {};
};

///Example
auto cout_function(int x){
  MEASURE_FUNCTION();
  for (int i = 0; i < 5000; i++)
  {
    cout << 1;
  }
};
```

## 5. Iterator
* 선형 범위 반복자 구성법
  ```cpp
  auto r = LinearRange<float>{0,1,4};
  auto vec = vector<float>{};
  copy(r.begin(),r.end(),back_inserter(vec));
  ```
  굳이 for loop를 사용하지 않아도 이런식으로 iterator를 활용하면 간편하게 구현 가능
  
* 선형 범위 함수
  ```cpp
  auto r = LinearRange<double>{0,1,4} // 0.0 0.33 0.66 1.0
  auto r = make_linear_range(0.0,1.0,4) // 상동
  for(auto t:make_linear_range){cout<<t} // 0.0 0.33 0.66 1.0 출력

## 6. STL 알고리즘
STL을 사용하는 장점을 배우고 좀 더 알기 쉬운 코드 베이스를 위한 알고리즘을 구성할 수 있는 범위 라이브러리를 살펴본다.

### remove & unique
remove와 unique는 실제로 요소를 삭제하지 않고 제거하려는요소가 뒷부분에 배치되도록 재정렬한다. 그 다음에 제거된 요소의 첫 번째 요소에 대한 반복자를 반환한다
  ```cpp
  auto v = vector<int>{1,1,2,2,3,3};
  auto new_end = remove(v.begin(),v.end(),2);
  vec.erase(new_end,vec.end());
  ```

### copy & transform
copy나 transform과 같은 출력 반복자에 데이터를 기록하는 알고리즘은 출력하려면 이미 할당된 데이터가 필요하다. 알고리즘이 동작하는 대상 컨테이너를 확장하려면 반복 연산을 하는 컨테이너를 확장하는 기능을 가진 반복자가 필요하다.
  ```cpp
  auto squared_func = [](int v){return v*v;};
  auto vals = vector<int>{1,2,3,4};
  auto squared = vector<int>{};
  squared.resize(vals.size()); // 컨테이너를 확장시켜야한다.
  transform(vals.begin(),vals.end(),squared.begin(),squared_func);
  ```
  또는
  ```cpp
  auto squared_func = [](int v){return v*v;};
  auto vals = vector<int>{1,2,3,4};
  //back_inserter사용법
  auto squared_vec = vector<int>{};
  auto dst_vec = back_inserter(squared_vec);
  transform(vals.begin(),vals.end(),dst_vec,squared_func)
  //inserter 사용법
  auto squared_set = set<int>{};
  auto dst_set = inserter(squared_set,squared_set.end());
  transform(vals.begin(),vals.end(),dst_set,squared_func));
  ```

### operator==와 operator<를 기본으로 사용하는 함수
`find`는 operator==를 사용하고 `max_element`는 operator<를 사용한다.
  ```cpp
  struct Flower{
    auto operator==(const Flower &f) const{
      return height_ == f.height_;
    }
    auto operator<(const Flower &f) const{
      return height_ < f.height_;
    }
    int height_{};
  };

  auto garden = vector<Flower>{Flower{2},Flower{13},Flower{7}};
  auto tallest_flower = max_element(garden.begin(), garden.end()); // operator< 사용
  auto magic_flower = find(garden.begin(),garend.end(),Flower{13}); // operator== 사용
  ```

### rotate
rotate함수는 데이터를 밀거나 당길 때 사용하기 유용하다.
  ```cpp
  auto s = string{"ABCD"};
  //만약 A를 D뒤로 옮기고 싶다면
  rotate(s.begin(),s.begin()+1,s.end());
  //만약 D를 맨 앞으로 가지고 오고 싶다면
  rotate(s.rbegin(),s.rbegin()+1,s.rend());
  ```

### 사용자 정의 함수
`find()`와 같이 원래의 알고리즘이 값을 사용하는 반면, 특정 연산자를 가진 경우에는 끝부분에 _if를 붙여 동일한 이름을 갖는다.
  ```cpp
  auto names = vector<string>{'eeeee','dddd','ccc','bb','a'};
  sort(names.begin(),names.end(),[](const string& a, const string& b){return a.size() < b.size();});
  // a bb ccc dddd eeeee순으로 정렬된다.
  auto target_size = 3;
  auto x = find_if(names.begin(),names.end(),[target_size](const auto& v){return v.size == target_size;});
  // X는 ccc
  ```

### range_v3(범위 라이브러리)
이후 버전의 C++20에서 다루어질 범위 라이브러리이다. 사용법과 안정성 측면에서 뛰어나므로 눈여겨볼 필요가 있다.
```cpp
  namespace rv = ranges::view;
  auto numbers = std::vector<int>{1,2,3,4,5,6,7};
  auto odd_squares_view = numbers
    | rv::transform([](auto v){ return v * v; }) // 1 4 9 16 25 36 49
    | rv::filter([](auto v){ return (v % 2) == 1; }); // 1 9 25 49

  namespace ra = ranges::action;
  auto ints = std::vector<int>{ 1, 2, 1, 3, 2, 4 }
  | ra::sort // 1 1 2 2 3 4
  | ra::unique; // 1 2 3 4
```


### 나머지 소소한 것들

* Random함수 사용법
  ```cpp
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
  ```