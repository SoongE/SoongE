### Types of Convolution

- Deeper: LeNet
- Wider: Inception
- Adding Dense Connection: DenseNets
- Efficient Separable Convolution: MobileNets
- Atrous Convolutions: DeepLab
- using Encoder-Decoder framworks:  U-Net
- non-local interaction: non-local networks
- feature pyramids: feature pyramid networks
- spatial and channel-wise attention: Cbam, SENet
- modern micro-design: ConvNeXt



### Types of Transformer

Image patches are simply regarded as sequences of words and a transformer encoder is applied on these visual tokens. However, it has been observed that without extensive pre-training ViT underperforms on image recognition.

- Pure: ViT
- Aggregate Attention: Swin
- Sparse Attention: Axial-deeplab, Focal, Dynamicvit, Cswin, Vivit
- Local Attention: TNT, T2T-ViT, 
- Pyramidal design: MViT, PVT
- training strategies: teacher-student strategy, LayerScale and CaiT, Deepvit



### Types of Hybrid Model

Pure Transformer-based vision models have been observed to generalize poorly due to relatively less inductive bias.

- Hybrid: CoAt, Early Convolutions Help Transformers See Better, Cvt, MViT, Convit, Coatnet
- implicit fashion: Twins-PCPVT, Swin