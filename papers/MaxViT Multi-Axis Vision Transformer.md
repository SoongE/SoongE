### Objective summary in general
- intro: blocked local과 dilated global attention에 대해 효율적이고 확장 가능한 attention 모델을 소개. 이 모델은 다양한 input resolution에서 global-local spatial interaction을 가능하게함. 이것을 이용해 convolution과 attention을 이용한 `MaxViT` backbone을 제안함. MaxViT는 전체 네트워크에서 globally하게 볼 수 있음.

- literature review (or theoretical background): Conv와 ViT는 각자의 영역에서 문제를 해결하기 위해 많은 노력들을 해옴. Conv에서는 deeper,wider,dense connection, micro-design 등등. ViT에서는 self-attention 그 중에서도 local-attention에 집중함. 하지만 ViT는 large-scale dataset으로 학습해야만 conv 성능을 뛰어넘을 수 있고, full attention에서 global interaction을 하기 위해서는 early or high-resolution에서 compuationally complexity가 quadratic에서 매우 힘들다. model capacity and generalizability의 균형을 맞추고 computation budget을 유지하는건 global and local interaction을 효과적으로 하기 위한 도전과제로 여전히 남아있다.
- method: Block and Grid attention으로 구성된 Max-SA module을 개발. 계산 효율성을 위해 MBConv와 합쳐서 <MBConv, Block Attn, Grid Attn> 조합의 MaxViT block을 개발. RenNet의 architecture를 따르지만 block을 MaxViT block으로 대체. pre-normalized self-attention을 key operator로 사용.
  - Block attention: local interaction --> underfito n huge-scale dataset
  - Grid Attention: global mixing
  - MBConv의 depthwise convolution은 conditional postion encoding(CPE)로 취급할 수 있다.
- results: Parameter와 FLOPs 대비 accuracy가 ConvNeXt, ViT, Swin, CoAtNet에 비해 더 좋은 성능을 낼 수 있었다.
- conclusion: 최근 Conv와 ViT는 cv에서 비슷한 성능을 내고 있다. MaxViT는 efficient convolution and sparse attention의 장점만 결합한 모델이라고 할 수 있다. 또한, 이 모듈을 MLP-Mixer나 gMLP에 적용하는 후속연구도 생각해볼 수 있다.


### Subjective comments in general
- good points: Conv와 Attention의 장점들을 가져와 결합할 수 있었다.
- weak points: 그러한 노력에도 불구하고 성능차이는 미묘하며, 파라미터수를 최대로 했을때는 SOTA라고 보기 힘들다.
- notes: MLP-Mixer에 어떻게 사용될 수 있는지 확인해보면 좋을 것 같다.