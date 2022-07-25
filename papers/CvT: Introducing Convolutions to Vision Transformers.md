### Objective summary in general

- intro: Convolution을 ViT에 introducing함으로써 ViT의 성능과 효율을 높임. 2개의 contribution. **Convolutional Toekn Embedding, Convolutional Transformer block Leveraging a convolutional projection**.

- literature review (or theoretical background):

  - ViT: ViT는 NLP에서 만들어진 Transformer를 cv에 적용시킨 첫 모델이다. 16x16 patch를 가지고 token으로 취급하여 모델을 만들었다. Large scale 에서 비록 ViT는 성공적이었으나, 비슷한 사이즈의 cnn과 비교하면 성능이 뛰어나다고 볼 순 없었다.
  - CNN: CNN이 성공적이라 볼 수 있는 이유는 2D local structure를 가지고 있기 때문이다. spatially neighboring pixels are usually highly correlated. CNN은 이 local feature를 강제로 잘 잡아낼 수 있다. local receptive fields, shared weights, spatial subsampling을 통해. 

- method: stage 시작마다 convolutional positional encoding과 self-attention block 직전에 있는 linear projection(Not MLP, qkv projection)을 depth-wise convolution으로 replace.

  - > Positional Encoding is replaced with Convolutional Token Embedding 

  - Remove Positional embedding, linear projection

  - Add Convolutional Token Embedding, Convolutional proejcton(squeeze –> key,value만) 


- results: Imagenet에서 1k, 21k 모두 transformer, cnn 모델보다 정확도가 올랐으며, flops, parameter는 더 효율적으로 낮출 수 있었다.
- conclusion: ViT에 convolution을 녹여내기 위해 많은 실험들을 했고, positional encoding 대신 convolutional toekn embedding을 사용하고 convolutional projection으로 성공적인 성능 향상을 이뤘다.

### Subjective comments in general

- good points: 좋은 점
- weak points: 안 좋은 점
- citation: 내 논문에 인용될 부분
- notes:
  - Desire properties of CNN: shift, scale, distortion invariance
  - Desire properties of ViT: dynamic attention, global context, better generalization