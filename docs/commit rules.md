# Commit Rules

프로젝트를 여러개 시작하고 코딩을 많이 하다 보니 commit을 해야하는 경우가 엄청 많아졌는데 항상 규칙이 없고 중구난방 형식으로 커밋을 하는 경우가 많았어서, 시간 여유가 있는 이번 기회에 나름의 커밋 규칙을 정하고 실천해보려고 합니다. 항상 어떤 단어를 선택해야할지 막막했었는데 잘 정리해 주신 분이 계셔서 그 중 제가 자주 쓸 것 같은 것만 추려왔습니다.



커밋을 할 때 지켜야하는 규칙

1. 동명사 대신 **명사** 사용
2. 부정문 사용 가능(Don't ~)
3. 관사 사용하지 않기(a, an, the)
4. **마침표** 사용하지 않기



### Commit Vocabulary

<p align="center">
    <a href="####fix">FIX</a> • 
    <a href="####add">ADD</a> • 
    <a href="####remove">REMOVE</a> • 
    <a href="####refactor">REFACTOR</a> • 
    <a href="####simplify">SIMPLIFY</a> • 
    <a href="####update">UPDATE</a> • 
    <a href="####improve">IMPROVE</a> • 
    <a href="####implement">IMPLEMENT</a> • 
    <a href="####correct">CORRECT</a> • 
    <a href="####set">SET</a>
</p>



#### FIX

보통 올바르지 않은 동작을 고치는 경우

##### Fix A : A를 수정

> 오타를 수정할 경우 보통 `Fix typo`정도만 한다.

```
Fix data directory
Fix typo
```

##### Fix A in B : B에 있는 A를 수정

```
Fix loading function in utils.py
```

##### Fix A where B, Fix A when B : B처럼, B일 때 발생하는 A를 수정

> 보통 'issue', 'error', 'crash'등이 자주 들어가게 된다.

```
Fix crush when closing activity
```



#### ADD

코드, 문서등을 추가할 때 경우

##### Add A : A를 추가

##### Add A for B : B를 위해 A를 추가

```
Add test for data loader
Add error description for navative integer in workers
```



#### REMOVE

코드를 삭제할 경우

##### Remove A : A 삭제

##### Remove A  from B: B에서 A삭제

```
Remove loding function from utils.py
Remove test.py
```



#### REFACTOR

전면적인 수정이 있을 경우

```
Refactor activity life cycle
Refactor main function
```



#### SIMPLIFY

복잡한 코드를 단순화 할 경우, Refactoring보다 약한 수정의 경우

```
Simplify for loop
Simplify code and remove unnacessary line
```



#### UPDATE

fix와 다르게 잘못된 것을 고치는게 아니라 수정, 추가, 보완하는 경우, 코드보다는 주로 **문서, 리소스, 라이브러리**에 많이 사용

```
Update repo docs
```



#### IMPROVE

성능을 향상 시킬 경우



#### IMPLEMENT

어떤 동작을 하는 코드를 구현할 경우

##### Implement A to B : B를 위해 A를 구현

```
Implement nn network to model training
```



#### Correct

문서에서 문법의 오류나 타입 변경, 이름 변경 등의 경우

```
Correct grammatical error in README.md
Correct parameters, return type in README.md
```



#### SET

변수 값을 변경하는 작은 수정의 경우

```
Set config.model_path to './result/model'
```



---

commit template이라고 치면 template을 만들어서 사용할 수 있도록 많은 사람들이 방법을 올려놓았습니다. 저 같은 경우는 템플릿을 사용하면 시간이 더 오래 걸릴 것 같아서 거대하고 중요한 프로젝트를 시작하기 전까지는 그냥 간단하게 커밋의 규칙을 만들어 놓고 정하려고 합니다. 저보다 더 자세하게 설명해주시는 분을 아래에 남겨놓으니 한번 방문해도 좋을 것 같아요!



### Reference

* https://blog.ull.im/engineering/2019/03/10/logs-on-git.html