### Objective summary in general

- intro: 파라미터와 연산량을 강화시키는 새로운 모델 Global Context Vision Transformer(GCViT)를 제안.

- literature review (or theoretical background):
  - ViT는 long-short range information을 잘 탐지할 수 있는 모델로서 나오게 되었다. 다만, computational cost와 필요한 데이터의 사이즈가 매우 많아진다는것이 baffle스러웠다. 

- method
  - Stage개념을 이용해 Hierarchical framework to obtain feature representations at several resolutions
  - Every GCViT stage is composed of alternating `local and global self-attention` modules
  - **Global Token Generator**는 CNN과 비슷한 feature extractor 모듈이다.
    - 스테이지마다 전체 이미지에서 오직 한 번만 작동한다.

  - EveryStage의 마지막에 resolution과 channel을 조절한다. –> Downsampling block 이용
  - Attention은 GCViT의 core idea로 semantic information을 추출
  - 

- Modules
  - Downsampling
    - FusedMBConv - Conv3x3(s=2), LayerNorm
      - FusedMBConv –> DWConv,GELU,SE,Conv1x1+shortcut

  - Attention
    - Be composed of local and global self-attention modules
      - Global Query Token –> Interacted with local key and valu toekns, 

    - Local Self Attention –> Extract local,shor-range information
    - Global Self Attention –> Long range dependencies
    - all cross-patch communication
    - 그 외에는 기존의 Attention과 비슷함


- conclusion
  - Global Self Attention은 classification, detection, segmentation에서 모두 훌륭하게 작동한다.
  - Global Context Query Features를 share하는 것은 performance를 많이 올려줬다.


### Subjective comments in general

- good points:
  - Enhance parameter and compute utilization
  - Attention Mask, Shifting local windows와  같은 기법 없이도 long-shot spatial interaction(global info, local info)를 효율적으로 계산할 수 있다.
  - ViT의 lack of the inductive bias 문제도 조금은 해결한다. 
- weak points: 안 좋은 점
- citation: 내 논문에 인용될 부분
- notes:
  - Swin Transformer
    - long-short range shortcoming을 해결하고자함 –> local windows and cross-window connection of self-attention
      - Local-window는 global하게 보려는 시도를 막아버리는 architecture다

