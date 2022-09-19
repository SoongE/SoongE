### Objective summary in general

- intro
  - kXk convolution을 $$k^2$$의 individual 1x1 convoluiton으로 분해
  - 1x1 convolution으로 interpret해서 self-attention 진행

- literature review (or theoretical background)
  - Transformer는 large “upstream” dataset에서 잘 학습한 뒤 특정 데이터셋에서 “downstream”하는 것이 전형적인 방법이다.
  - SENet, CBAM은 self-attention이 convolution module의 augmentation의 역할을 할 수 있음을 보임
  - SAN, BoTNet은 전형적인 CNN대신 self-attention을 individual blocks으로 사용
  - AA-ResNet, Container는 self-attention과 convolution을  결합하려고함


- method
  - Providing new perspectives on understanding the connection between two modules and inspirations for designing new learning paradigms
  - Elegant integration
- results: 결과
- conclusion: 결론 및 임플리케이션


### Subjective comments in general

- good points: 좋은 점
- weak points
  - 기존의 conv와 attn을 사용하려는 것들은 여전히 attn과 conv를 개별적인 영역으로 취급하며, 이들 사이의 근본적인 관계를 충분히 활용하지 못함

- citation: 내 논문에 인용될 부분
- notes: 기타 메모

