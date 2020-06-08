# Tokenizer
Tokenizer는 크게 3가지 방식으로 분류된다.
1. 가장 간단한 **공백**기반 tokenizer
2. 한국어에 적합한 **형태소 분석기**기반 tokenizer
3. Word Piece Model로 대표되는 **Byte Pair Encoding(BPE)**기반 tokenizer

## 공백 기반 Tokenizer
말 그대로 공백을 기준으로 문장을 잘라내는 방식. 가장 빠르고 심플하며 영어 데이터에 적합한 tokenizer이다.
한국어에서는 조사, 어미 변형등으로 인해 의미가 잘 분리되지 않아 제대로된 모델을 학습할 수 없다.

## 형태소 분석기 기반 Tokenizer
형태소를 비롯한 어근, 접두사/접미사, 품사 등의 다양한 언어적 속성에 대한 문법 구조를 파악하는 것이다. 아래의 예시와 같이 형태소 분석기는 문장의 문법적 구조를 파악하여 조사나 어미에 대한 tokenizer를 할 수 있다.
> 나는 밥을 먹는다 -> 나/NP + 는/JX + 밥/NNG + 을/JKO + 먹/VV + 는다/EC

#### 문제점
형태소 분석기는 기존에 구축된 사전을 기반으로 예측하기 때문에 `띄어쓰기 오류`, `오타`, `신조어` 등이 포함될 경우 잘못된 분석결과가 나타난다.

또 다른 문제점은 속도가 느리다는 것이다. 문자의 개수에 따라 기하급수적으로 소요시간이 증가한다.
![문자 개수에 따른 소요시간 (출처: KoNLPy - 형태소 분석 및 품사 태깅)](./img/KoNLPy_running_time.png)

마지막 문제는 OOV(Out of Vocabulary)문제이다. 사전에 포함되지 않은 단어는 모두 `<UNK>`로 치환된다. OOV의 비율이 커질수록 input 문장을 모델이 이해하기 어렵게 되어 제대로된 학습이 이루어지지 않고 성능 저하로 이어진다.

#### 관련 Tokenizer
> KoNLPy, SoyNLP, Khaiii

## BPE 기반 Tokenizer
OOV의 문제를 해결하기 위해 최근에는 데이터 압축 기법인 BPE 알고리즘을 통해 Subword Unit에 대한 사전을 만드는 기법이 많이 활용되고 있다. 빈도수가 높은 Subword Unit들을 병합시켜 나가면서 최종적으로 자주 나오는 단어는 그 자체를 그대로 저장하고 덜 나오는 단어는 subword로 나누어서 저장하므로 효율적인 사전 관리를 통해 OOV를 줄이는 목적을 가지고 있다. BPE기반의 tokenizer들은 굉장히 낮은 OOV를 보이며 접두사, 접미사가 비교적 규치적으로 잘 활용되는 영어의 경우 좋은 효과를 보인다. 다만 한글에 경우 워낙 변형이 다양하여 잘 동작하지 않을 수 있다는 한계점이 있다.

#### 관련 Tokenizer
> SentencePiece, BPE를 변형한 WordPieceModel(WPM)

## 비교하기
BPE를 대표하는 오픈소스 `SentencePiece`와 형태소 기반의 `Mecab`, 두 가지 tokenizer를 간단하게 비교하였다.

* SentencePiece
  * 속도 빠름
  * Subword의 빈도에 기반하기 때문에 unknown token 처리 가능
  * 의미 단위로 잘 나눠지지 않을 수 있음

* Mecab
  * SentencePiece 만큼은 아니지만 빠름
  * 형태소 분석을 기반으로 하기 때문에 의미 단위를 잘 포착
  * 신조어나 오타에 취약


## 결론
나라면 한국어 분석에 대해서는 SentencePiece보다는 형태소 분석기 기반의 Mecab을 사용할 것 같다. 의미 단위를 더 잘 포착하기도 하고 분석 시간도 다른 KoNLPy 대비 매우 빠르기 때문에 Soynlp로 일부 전처리를 해준 뒤, Mecab 사용자 사전에 신조어등을 넣어주면 훨씬 좋은 Tokenizing이 될 것 같다.

## Reference
* https://blog.pingpong.us/dialog-bert-tokenizer/#%EA%B3%B5%EB%B0%B1-%EA%B8%B0%EB%B0%98-tokenizer
* https://lovit.github.io/nlp/2018/04/02/wpm/
* https://konlpy-ko.readthedocs.io/ko/v0.4.3/morph/
