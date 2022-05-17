# Table of Contents

- [코너 검출](https://github.com/Phw9/OpenCV/tree/master/LocalFeatureDetect/corner)

- [크기 불변 특징점 알고리즘](#크기-불변-특징점-알고리즘)
  - [SIFT](#SIFT)
  - [SURF](#SURF)
  - [KAZE](#KAZE)
  - [ORB](#ORB)

- [OpenCV 특징점 검출과 기술](#OpenCV-특징점-검출과-기술)

- [특징점 매칭](#특징점-매칭)
  - [OpenCV 특징점 매칭](#OpenCV-특징점-매칭)
  - [호모그래피와 영상 매칭](#호모그래피와-영상-매칭)
    - RANSAC(#RANSAC)

---

## 크기 불변 특징점 알고리즘

코너는 영상이 회전되어도 여전히 코너로 검출된다. 그러므로 코너는 회전 불변 특징점이라고 할 수 있다. 그러나 영상의 크기가 변경될 경우 코너는 더 이상 코너로 검출되지 않을 수 있다.

예를 들어 그림과 같이 크기가 확대되면 같은 크기의 사각형 안에서 코너보다는 에지에 가까운 형태로 관측 될 수 있다.

![캡처](https://user-images.githubusercontent.com/76188802/168242185-f3182fcd-5988-4dd7-9f4c-fde0fb852b0a.PNG)

크기가 다른 두 객체 영상에서 단순한 코너 점을 이용해 서로 같은 위치를 찾는 것에는 한계가 있어, 크기가 다른 영상에서도 지속적으로 검출될 수 있는 알고리즘 들이 있다.

---


### SIFT

SIFT는 크기 불변 특징 변환(Scale Invariant Feature Transform)의 약자이며, 2004년 캐나다의 브리티시 컬럼비아 대학교 로우(D. Lowe) 교수가 발표한 논문에 소개된 방법이다.

`SIFT 알고리즘은 영상의 크기 변화에 무관하게 특징점을 추출하기 위하여 입력 영상으로부터 스케일 스페이스(scale space)를 구성`한다. 스케일 스페이스는 `영상에 다양한 표준 편차를 이용한 가우시안 블러링을 적용하여 구성한 영상 집합`을 의미한다. 아래 레나 영상에 대해 스케일 스페이스를 구성한 예를 그림으로 보자.

![캡처](https://user-images.githubusercontent.com/76188802/168248926-61385428-293f-48e8-a177-bc6a65fd5855.PNG)

`여섯 개의 블러링된 영상이 스케일 스페이스를 구성한 결과이며, 이렇게 구성한 영상 집합을 옥타브(octave)`라고 한다. 이후 입력 영상의 크기를 가로, 세로 반으로 줄여 가면서 여러 옥타브를 구성한다. `SIFT 알고리즘에서 크기에 불변한 특징점을 검출할 때에는 인접한 가우시안 블러링 영상끼리의 차영상을 사용하며, 이를 DoG(Differece of Gaussian)영상` 이라고 한다. 그림 아래쪽에 나열한 영상이 레나 영상으로부터 구한 DoG 영상이다. 위 그림은 DoG 영상을 그레이스케일 영상 형식으로 보여주기 위해 각각의 차영상 픽셀 값에 128을 더해준 영상이다.

SIFT 알고리즘은 DoG 영상 집합에서 `인접한 DoG 영상을 고려한 지역 극값 위치를 특징점으로 사용하며, 이후 에지 성분이 강하거나 명암비가 낮은 지점은 특징점에서 제외`한다.

SIFT 알고리즘은 특징점을 검출하는 기능뿐만 아니라 `특징점 주변의 픽셀 값을 이용한 기술자(descriptor)계산 방법`도 포함한다.
`특징점 기술자는 특징점 주변 영상의 특성을 여러 개의 실수 값으로 표현한 것을 의미하며, 특징 벡터(feature vector)`라고도 한다. 서로 같은 특징점에서 추출된 기술자는 실수 값 구성이 서로 일치한다. SIFT는 기본적으로 특징점 부근의 부분 영상으로부터 `그래디언트 방향 히스토그램을 추출해 기술자로 사용`한다. 특징점 근방으로부터 특징점의 주된 방향 성분을 계산하고, 이 방향 만큼 회전한 부분 영상으로부터 128개의 빈(bin)으로 구성된 그래디언트 방향 히스토그램을 계산한다. 각각의 빈 값은 float 자료형을 사용하며, 하나의 SIFT 특징점은 512byte 크기의 기술자로 표현된다.

SIFT 알고리즘은 영상의 크기, 회전 등의 변환뿐만 아니라 촬영 시점 변화에도 충분히 강인하게 동착하며, 잡음의 영향과 조명 변화가 있어도 특징점을 반복적으로 잘 찾아낸다. SIFT 알고리즘은 다양한 컴퓨터 비전 분야에서 적용되었고 특히 객체 인식, 파노라마 영상 이어붙이기, 3차원 장면 인식 등의 분야에서 효과적으로 사용됐다.


---

### SURF

2008년에 발표된 SURF(Speed-Up Robust Features) 알고리즘은 SIFT에서 사용한 `DoG 영상을 단순한 이진 패턴으로 근사화하여 속도를 향상`시켰다⑴.


ef)

⑴ H. Bay, A. Ess, T. Tuytelaars, and L. V. Gool, “SURF: Speeded Up Robust Features,” Computer Vision and Image Understanding (CVIU), vol. 110, no. 3, pp. 346-359, 2008.

---

### KAZE

2012년에 발표된 KAZE 알고리즘은 `가우시안 함수 대신 비등방성 확산 필터(nonlinear diffusion filter)를 이용해 비선형 스케일 스페이스를 구축하여 특징점을 검출`한다. KAZE 알고리즘은 객체의 윤곽을 잘 보전함으로써 블러링, 크기 및 회전 변환, 잡음 등의 영향으로 변형된 영상에서 같은 특징점을 반복적으로 찾아내는 성능이 뛰어나다.




---

### ORB

SIFT, SURF, KAZE 방법은 스케일 스페이스를 구성하는 등 복잡한 연산을 수행해야 하기 때문에 실시간 응용에서 사용하기 어렵다는 단점이 있다. 또한, 이들 특징점 알고리즘에 의해 만들어지는 기술자는 128개 또는 64개의 실수 값으로 구성되어 있어서 메모리 사용량이 많고 특징점 사이의 거리 계산도 오래 걸릴 수 있다는 단점이 있다. 그래서 2010년 전후로는 특징점 검출이 매우 빠르고 이진수로 구성된 기술자를 사용하는 알고리즘이 발표되기 시작했다.

그중 2011년 발표된 ORB(Oriented FAST and Rotated BRIEF) 알고리즘은 당시 OpenCV를 관리하던 연구소에서 개발한 방법으로서, ⑴ SIFT와 SURF를 대체하기에 좋은 알고리즘이다. `ORB 알고리즘은 기본적으로 FAST 코너 검출 방법을 이용해 특징점을 추출`한다. 다만 `기본적인 FAST 알고리즘은 영상의 크기 변화에 취약하기 때문에 ORB 알고리즘은 입력 영상의 크기를 점진적으로 축소한 피라미드 영상을 구축하여 특징점을 추출`한다. 그리고 `각 특징점에서 주된 방향 성분을 계산하고, 방향을 고려한 BRIEF 알고리즘으로 이진 기술자를 계산`한다.

ORB에서 사용한 BRIEF(Binary Robust Independent Elementary Features)는 순수하게 특징점 기술자만을 생성하는 알고리즘이다⑵. BRIEF는 특징점 주변의 픽셀 쌍을 미리 정하고, 해당 픽셀 값 크기를 비교하여 0 또는 1로 특징을 기술한다. 두 점 x와 y에서의 픽셀 값 크기 비교 테스트는 τ는 다음과 같이 정의 한다.

![캡처](https://user-images.githubusercontent.com/76188802/168259980-d18754b2-5b3f-4a4e-a0d5-40396e818d9b.PNG)

예를 들어 아래 그림과 같이 특징점 p 주변에 a, b, c 점을 미리 정의하고, τ(a,b), τ(b,c), τ(c,a)를 구하면 이진수 0b110을 얻을 수 있다. 이진수 0b110은 b점이 a보다 밝고, c점이 b보다 밝고, a점은 c보다 어둠다는 정보를 표현한다. 이처럼 특징점 주변 정보를 이진수 형태로 표현하는 기술자를 이진 기술자(binary descriptor)라고 한다.

![캡처](https://user-images.githubusercontent.com/76188802/168260678-0d3c82f5-f170-4d9f-9aa4-a9c71b118866.PNG)


ORB 알고리즘은 

1. FAST 기반의 방법으로 특징점을 구한 후, 각 특징점에서 픽셀 밝기 값 분포를 고려한 코너 방향 성분을 계산한다.
2. 이 방향 성분을 이용하여 BRIEF 계산에 필요한 점들의 위치를 보정함으로써 회전에 불변한 BRIEF 기술자를 계산한다.

ORB 알고리즘에서는 기본적으로 `256개의 크기비교 픽셀 쌍을 사용하여 이진 기술자를 구성하며, 결과적으로 하나의 특징점은 256비트로 표현`할 수 있다. SIFT와 SURF 기술자가 각각 512바이트, 256바이트를 사용하는 것에 비해 ORB는 32바이트의 크기로 특징점을 기술할 수 있어서 효율적이다.

이진 기술자로 표현된 특징점 사이의 거리 계산은 주로 해밍 거리(Hamming distance)방법을 사용한다. 해밍 거리는 이진수로 표현된 두 기술자에서 서로 값이 다른 비트의 개수를 세는 방식으로 계산한다. 해밍 거리 계산은 두 기술자의 비트 단위 배타적 논리합(XOR) 연산 후, 비트 값이 1인 개수를 세는 방식으로 빠르게 계산한다.

ORB 외에도 BRISK, AKAZE, FREAK 등의 이진 기술자를 사용하는 특징점 알고리즘이 있다.


Ref)

⑴ E. Rublee et al., “Orb: an efficient alternative to sift or surf,” IEEE International Conference on Computer Vision (ICCV), pp. 2564-2571. 2011.

⑵ M. Calonder, V. Lepetit, C. Strecha and P. Fua, “ BRIEF: Binary Robust Independent Elementary Features,” European Conference on Computer Vision (ECCV), pp. 778-792, September, 2010.

---



## OpenCV 특징점 검출과 기술

OpenCV에서 제공하는 특징점 검출 알고리즘 구현 클래스 및 클래스를 이용해 영상에서 특징점을 검출하고 기술자를 구하는 방법에 대해 알아보자. 또한, OpenCV에서 제공하는 함수를 이용해 검출된 특징점을 화면에 출력하는 방법도 알아보자.

특징점 검출 방법을 설명하기에 앞서 OpenCV에서 `특징점 정보를 저장할 때 사용하는 keyPoint 클래스`에 대해 알아본다. KeyPoint 클래스는 `특징점 좌표뿐만 아니라 특징점 검출 시 고려한 주변 영역의 크기, 주된 방향(각도), 옥타브 정보 등을 멤버 변수`로 가지고 있다. 이러한 정보는 `특징점 주변 영역의 특징을 표현하는 기술자 계산시에도 사용`된다. 일반적으로 KeyPoint 객체는 사용자가 직접 생성하지 않으며, 특징점 검출 클래스 내부에서 생성하여 사용자에게 반환한다.


![캡처](https://user-images.githubusercontent.com/76188802/168267920-761d3561-b49b-4753-9cd3-8a89faadf4d5.PNG)

위 그림과 같이 OpenCV에서 특징점 관련 클래스는 모두 Feature2D 클래스를 상속받아 만들어진다. Feature2D 클래스는 detect(), compute(), detectAndCompute()라는 이름의 가상 멤버 함수를 가지고 있으며, Feature2D 클래스를 상속받은 각각의 특징점 알고리즘 구현 클래스는 이들 멤버 함수 기능을 실제로 구현하도록 설계되어 있다. `detect() 멤버 함수는 영상에서 KeyPoint를 검출하고, coumpute() 함수는 검출된 KeyPoint를 표현하는 기술자를 생성한다. detectAndCompute() 멤버 함수는 KeyPoint 검출과 descriptor 생성을 동시에 수행`한다.

위 그림에서 Feature2D 클래스를 상속받아 만들어진 SIFT, SURF, FastFeatureDetector, BriefDescripotrExtractor, KAZE, ORB 등의 클래스는 실제 특징점 검출 및 기술 알고리즘을 구현한 클래스다. 가장 유명한 특징점 검출 알고리즘인 SIFT와 SURF는 각각 알고리즘과 동일한 이름의 클래스로 구현되어 있다. `SIFT와 SURF는 소스 코드는 공개되어 있지만 알고리즘 자체에 특허가 걸려있어서 상업적인 사용시에는 제약`이 있을 수 있다. `BriefDescriptorExtractor 클래스는 BRIEF 기술자 계산 방법이 구현된 클래스`다. SIFT, SURF, BriefDescriptorExtractor 클래스는 xfeatures2d 추가 모듈에 포함되어 있으며 cv::xfeatures2d 네임스페이스를 사용한다. 그러므로 이들 클래스는 OpenCV 소스 코드를 직접 빌드해야 사용할 수 있다. 반면에 cv 네임스페이스를 사용하고 있는 FastFeatureDetector, KAZE, ORB 등의 클래스는 OpenCV 기본 소스에 포함되어 있어서 쉽게 사용할 수 있다.


위 그림에 나열된 `특징점 알고리즘 구현 클래스 중에는 특징점 검출만 지원하거나 기술자 생성만 지원하는 클래스도 있다.` 예를 들어 FastFeatureDetector 클래스는 FAST 코너 검출 방법을 클래스로 구현한 것이며, 이 클래스는 특징점을 검출하는 기능만 있다. 그러므로 FastFeatureDetector 객체에서 compute() 또는 detectAndCompute() 함수를 호출하면 에러가 발생한다. 반면에 BriefDescriptorExtractor 클래스는 다른 방법으로 구한 특징점 위치에서 BRIEF 이진 기술자를 구하는 기능만 제공한다. 그래서 BriefDescriptorExtractor 객체에서 detect() 또는 detectAndCompute() 함수를 호출하면 안된다. SIFT, KAZE, ORB처럼 특징점 검출과 기술을 함께 지원하는 알고리즘 클래스는 detect(), compute(), detecetAndCompute() 함수를 모두 사용할 수 있다.


특징점 구현 알고리즘 클래스를 이용하려면 먼저 각 특징점 클래스 객체를 생성해야한다. `Feature2D를 상속받아 만들어진 특징점 클래스들은 모두 create()라는 이름의 정적 멤버 함수를 가지고` 있으며, 각 특징점 클래스 객체는 해당 클래스의 `create() 멤버 함수를 이용하여 생성`해야 한다. `특징점 클래스마다 정의된 create() 정적 멤버 함수의 인자 구성은 각기 다르지만, 모든 인자에 기본값이 지정되어 있기 때문에 인자를 지정하지 않고도 사용`할 수 있다. (`각 특징점 클래스의 create() 멤버 함수에서 사용하는 인자 구성은 해당 알고리즘에 특화된 내용이 많다`. 그러므로 각각의 create() 함수에 대한 자세한 사항은 관련 논문과 OpenCV 사이트를 참고) 그리고 `각 특징점 클래스의 create() 멤버 함수는 해당 클래스 객체를 참조하는 스마트 포인터를 반환`함.

```cpp
/*
예를 들어 ORB::create() 멤버 함수 원형은 다음과 같다.
*/  

static Ptr<ORB> ORB::create(int nfeatures = 500, float scaleFactor = 1.2f, int nlevels = 8, int edgeThreshold =31, int firstLevel = 0, int WTA_K = 2, ORB::ScoreType scoreType = ORB::HARRIS_SCORE, int patchSize = 31, int fastThreshold = 20);

nfeatures     : 검출할 최대 특징 개수
scaleFactor   : 피라미드 생성 비율(영상 축소 비율)
nlevels       : 피라미드 단계 개수
edgeThreshold : 특징을 검출하지 않을 영상 가장자리 픽셀 크기
firstLevel    : 항상 0을 지정해야 한다.
WTA_K         : BRIEF 기술자 계산시 사용할 점의 개수. 2, 3, 4 중 하나를 지정해야함.
scoreType     : 특징점 점수 결정 방법. ORB::HARRIS_SCORE 또는 ORB::FAST_SCORE 둘 중 하나를 지정.
patchSize     : BRIEF 기술자 계산시 사용할 패치 크기
fastThreshold : FAST 코너 검출 방법에서 사용되는 임계값
return        : ORB 객체를 참조하는 Ptr 스마트 포인터 객체

Ptr<ORB> feature = ORB::create();       // ORB 클래스 객체 생성
Ptr<Feature2D> feature = ORB::create(); // ORB 클래스가 Feature2D 클래스를 상속받아 만들어진 클래스이기 때문에 이렇게도 가능
Ptr<Feature2D> feature = KAZE::create();// KAZE 특징점 검출 방법을 사용하기 위한 KAZE 클래스 객체 생성

```

- [키포인트 검출 예제](https://github.com/Phw9/OpenCV/tree/master/LocalFeatureDetect/detect)


---

## 특징점 매칭

#### OpenCV 특징점 매칭

특징점 매칭(matching)은 두 영상에서 추출한 특징점 기술자를 비교하여 서로 비슷한 특징점을 찾는 작업을 의미한다. 특히 크기 불변 특징점으로부터 구한 기술자를 매칭하면 그기와 회전에 강인한 영상 매칭을 수행할 수 있다.

특징점을 매칭하는 방법을 설명하기 앞서 OpenCV에서 특징점 매칭 정보를 저장할 때 사용하는 DMatch 클래스에 대해 알아보자.
```cpp
//  간략화한 DMatch 클래스 정의
class DMatch
{
public:
    DMatch();
    DMatch(int _queryIdx, int _trainIdx, float _distance);
    DMatch(int _queryIdx, int _trainIdx, int _imgIdx, float _distance);
    
    int queryIdx;     //  질의 기술자 번호
    int trainIdx;     //  훈련 기술자 번호
    int imgIdx;       //  훈련 영상 번호. 여러 장의 영상을 훈련 영상으로 설정한 경우 사용됨
    
    flaot distance;   //  두 기술자 사이의 거리
    
    bool operator<(const DMatch &m) const;  //  DMatch 클래스에 대한 크기 비교 연산자 재정의이며, DMatch::distance 멤버 변수 값을                                             //  이용해 크기를 비교한다.
};
```
distance 멤버 변수는 `두 키포인트 기술자가 얼마나 차이가 나는지를 나타내는 매칭 척도의 역할`을 한다. `두 특징점이 서로 유사하면 distance 값이 0에 가깝고, 서로 다른 특징점이면 distance 값이 크게` 나타난다. distance 계산 방식은 다차원 벡터의 유클리드 거리(Euclidean distance)로 주로 계산하며, 다만 이진 기술자끼리 비교하는 경우엔 해밍 거리를 사용한다. DMatch 클래스 객체는 보통 사용자가 직접 생성하지 않고, 특징점 매칭 알고리즘 내부에서 생성하여 사용자에게 반환한다.


![캡처](https://user-images.githubusercontent.com/76188802/168753268-6719d1ad-d7d4-40bb-a27c-9b105ceaefdc.PNG)


OpenCV에서 제공하는 특징점 매칭 클래스 상속 관계는 위와 같다. 특징점 매칭 클래스는 DescriptorMatcher 클래스를 상속받아 만들어진다. DescriptorMatcher 클래스는 match(), knnMatch(), radiusMatch() 등의 가상 멤버 함수를 가지고 있는 추상 클래스이며, DescriptorMatcher 클래스를 상속받은 BFMatcher 클래스와 FlannBasedMatcher 클래스는 이들 멤버 함수 기능을 실제로 구현하도록 설계되어 있다.
match() 함수는 가장 비슷한 기술자 쌍을 하나 찾고, knnMatch() 함수는 비슷한 기술자 쌍 k개를 찾는다. radiusMatch() 함수는 지정한 거리 반경 안에 있는 기술자 쌍을 모두 찾아 반환한다.

`BFMatcher 클래스는 전수 조사(Brute-Force) 매칭`을 수행한다. BFMatcher 클래스는 query 기술자 집합에 있는 모든 기술자와 train 기술자 집합에 있는 모든 기술자 사이의 거리를 계산하고, 이 중 `가장 거리가 작은 기술자를 찾아 매칭하는 방식`이다. BFMatcher 클래스의 `매칭 결정 방법은 매우 직관적이지만 특징점 개수가 늘어날수록 거리 계산 획수가 급격하게 늘어날 수 있다는 단점`이 있다. 예를 들어 첫 번째 영상에 1000개의 특징점이 있고, 두 번째 영상에 2000개의 특징점이 있다면 BFMatcher 방법은 총 2,000,000번의 비교 연산을 수행해야 한다. 그러므로 `특징점 개수가 늘어날수록 BFMatcher 방법에 의한 매칭 연산량은 크게 늘어나게 되며, 이러한 경우에는 BFMatcher 클래스 대신 FlannBasedMatcher 클래스를 사용하는 것이 효율적`이다.

Flann(Fast Library approximate nearest neighbors)은 근사화된 최근방 이웃(ANN, Approixmate Nearest Neighbors) 알고리즘을 빠르게 구현한 라이브러리다. 그리고 `FlannBasedMatcher 클래스는 Flann 라이브러리를 이용하여 빠르게 매칭을 수행하는 클래스`다. 즉, FlannBasedMatcher 클래스는 근사화된 거리 계산 방법을 사용하므로 가장 거리가 작은 특징점을 찾지 못할 수 있지만, 매우 빠르게 동작한다. 다만 FlannBasedMatcher 클래스는 기본적으로 `L2 노름 거리 측정 방식을 사용`하므로 해밍 거리를 사용하는 이진 기술자에 대해서는 사용할 수 없다. (이진 기술자에 대해서도 지역성 의존 해싱(LSH, Locality Sensitive Hashing) 기법을 이용하여 FlannBasedMatcher 클래스를 사용할 수는 있지만 사용법이 까다로운 편이다.)

BFMatcher::create() 함수의 첫 번째 인자 normType에는 두 기술자 사이의 거리를 측정하는 방식을 지정한다. SIFT, SURF, KAZE 알고리즘처럼 `실수 값으로 구성된 기술자를 사용하는 경우엔 보통 NORM_L2 또는 NORM_L1 상수를 지정`한다. ORB, BRIEF, AKAZE 알고리즘처럼 `이진 기술자를 사용하는 경우에는 normType에 NORM_HAMMING 플래그를 지정`해야 하며, 이 경우에는 두 이진 기술자 사이의 해밍 거리를 사용한다. 만약 ORB 기술자에서 WTA_K를 3 또는 4로 설정한 경우에는 normType을 NORM_HAMMING2로 지정해야 한다.

BFMatcher 또는 FlannBasedmatcher 객체를 생성한 후에는 DescriptorMatcher::match()함수로 두 입력 영상에서 추출한 기술자 행렬 사이의 매칭을 수행할 수 있다. 함수 원형은 다음과 같다.
```cpp
void DescriptorMatcher::match(InputArray queryDescriptors, InputArray trainDescriptors, std::vector<DMatch>& matches, InputArray mask = noArray()) const;

queryDescriptors  // 질의 기술자 집합
trainDescriptors  // 훈련 기술자 집합
matches           // 매칭 결과
mask              /* 서로 매칭 가능한 질의 기술자와 훈련 기술자를 지정할 떄 사용한다. 행 개수는 질의 기술자 개수와 같아야하고, 열 개수                      는 훈련 기술자 개수와 같아야 한다. 만약 mask.at<uchar>(i,j) 값이 0이면 queryDescriptors[i]는
                     trainDescriptors[j]로 매칭될 수 없다. noArray()를 지정하면 모든 가능한 매칭을 찾는다. */

```

1. DescriptorMatcher::`match() 함수는 queryDescriptors에 저장된 각각의 기술자에 대해 가장 유사한 기술자를 trainDescriptors에서 찾는다.`
2. 각각의 매칭 결과(matches)에 대해 DMatch::queryIdx에는 queryDescriptors의 번호가 저장되고, DMatch::trainIdx에는 trainDescriptors의 번호가 저장된다. mask 인자를 특별히 지정하지 않는 경우, 매칭 결과가 저장되는 matches에는 queryDescriptors 기술자 개수와 같은 수의 DMatch 객체가 저장된다.

DescriptorMatcher::knnMatch()    : 주어진 query 기술자에 대해 k개의 유사한 훈련 기술자를 찾아 반환
DescriptorMatcher::radiusMatch() : 지정한 거리보다 작은 거리를 갖는 훈련 기술자를 모두 찾아 반환


drawMatches() 함수는 두 매칭 입력 영상을 가로로 이어붙이고, 각 영상에서 추출한 특징점과 매칭 결과를 다양한 색상으로 표시한 결과 영상을 생성한다. drawMatches() 함수 원형은 다음과 같다.
```cpp
void drawMatches(InputArray img1, const std::vector<KeyPoint>& keypoints1,
                 InputArray img2, const std::vector<KeyPoint>& keypoints2,
                 const std::vector<DMatch>& matches1to2, InputOutputArray outImg, const Scalar& matchColor = Scalar::all(-1),
                 const Scalar& singlePointColor = Scalar::all(-1), const std::vector<char>& matchesMask = std::vector<char>(),
                 DrawMatchesFlags flags = DrawMatchesFlags::DEFAULT);
                 
img1              : 첫 번째 입력 영상
keypoints1        : 첫 번째 입력 영상에서 검출된 특징점
img2              : 두 번째 입력 영상
keypoints2        : 두 번째 입력 영상에서 검출된 특징점
matches1to2       : 첫 번째 입력 영상에서 두 번째 입력 영상으로의 매칭 정보
outImg            : 출력 영상
matchColor        : 매칭된 특징점과 직선 색상. 만약 Scalar::all(-1)을 지정하면 임의의 색상으로 그린다.
singlePointColor  : 매칭되지 않은 특징점 색상. 만약 Scalar::all(-1)을 지정하면 임의의 색상으로 그린다.
matchesMask       : 매칭 정보를 선택하여 그릴 때 사용할 마스크. 만약 std::vector<char>()를 지정하면 모든 매칭 결과를 그린다.
flags             : 매칭 정보 그리기 방법. DrawMatchesFlags 열거형 상수를 지정한다.

```

1. drawMatches() 함수는 두 개의 입력 영상 img1과 img2를 서로 가로로 이어 붙이고, 두 영상 사이의 특징점 매칭 결과를 직선으로 그린 결과 영상 outimg를 반환한다.
2. 두 입력 영상 사이의 매칭 정보는 matches1to2 인자로 전달한다.
3. 매칭 결과를 그리는 방식은 flags 인자로 지정한다.

- [키포인트 매칭 예제](https://github.com/Phw9/OpenCV/blob/master/LocalFeatureDetect/detect/keypoint_matching.cpp)

위의 키포인트 매칭 예제에서 지역 특징점 매칭의 최종 목적은 book-in-scene.jpg 영상에서 book.jpg 영상이 있는 위치와 모양을 정확하게 알아내는 것이다. dst는 영상을 가로로 이어 붙인 영상 위에 특징점 매칭 결과를 다양한 색상의 직선으로 표시한 결과다. 하지만 book.jpg 영상에서 추출한 모든 특징점 기술자에 대해 가장 유사한 book-in-scene.jpg 영상에서 추출된 일부 특징점은 매칭이 되지 않아 직선이 연결되어 있지 않은 것을 확인할 수 있다. 이는 `영상 일부가 가려져 있거나 가려져 있지 않더라도 기하학적 변형과 조명 변화로 인하여 완벽한 매칭은 거의 불가능하며, 매칭 결과 중 상당수는 완전히 다른 특징점으로 잘못 매칭된다. 그러므로 전체 매칭 결과에서 잘못 매칭된 결과는 제외하고, 제대로 매칭되었다고 판단되는 결과만 선별하여 사용`해야 한다.

DMatch 클래스는 기술자 사이의 거리를 표현하는 distance를 멤버 변수로 가지고 있다. 그러므로 distance 값이 너무 큰 매칭 결과는 무시하고 distance 값이 작은 결과만 사용하는 것이 좋다. `DMatch 클래스는 부등호 연산자에 대한 재정의가 되어 있고, 이 연산자 재정의에서는 distance 멤버 변수 크기를 비교하기 때문에 DMatch 객체를 std::sort() 함수로 정렬`하면 자동으로 distance 값을 기준으로 정렬된다.

- [좋은 매칭 선별 예제](https://github.com/Phw9/OpenCV/blob/master/LocalFeatureDetect/detect/good_matching.cpp)


---


#### 호모그래피와 영상 매칭

특징점 매칭 결과로부터 두 영상의 호모그래피(homography)를 계산하고, 이를 이용하여 크기가 다르고 회전이 되어 있는 객체를 정확하게 매칭하는 방법에 대해 알아보자. `호모그래피는 3차원 공간상의 평면을 서로 다른 시점에서 바라봤을 때 획득되는 영상 사이의 관계`를 나타내는 용어다. 호모그래피는 수학적으로 하나의 평면을 다른 평면으로 투시 변환(perspective transform)하는 것과 같은 관계에 있다.

![캡처](https://user-images.githubusercontent.com/76188802/168791605-aaa03ff9-7e47-4298-9a7c-3d252fcccf70.PNG)


위 그림은 3차원 공간에서 평면과 획든된 영상과의 호모그래피 관계를 보여준다. 바닥에 놓인 평면 P를 v1 시점에서 바라본 영상I1과 v2 시점에서 바라본 영상 I2 사이의 관계를 호모그래피 H12로 표현한다. 또한 영상 I1과 평면 P 사이의 관계, 또는 영상 I2와 평면 P 사이의 관계도 각각 호모그래피 H1과 H2 형태로 표현할 수 있다. `실제적인 연산 관점에서 호모그래피는 투시 변환과 같기 때문에 호모그래피 3x3 실수 행렬로 표현`할 수 있다. 또한 투시 변환을 구할 떄와 마찬가지로 `네 개의 대응되는 점의 좌표 이동 정보가 있으면 호모그래피 행렬을 구할 수 있다. 그러나 특징점 매칭 정보로부터 호모그래피를 구하는 경우에는 서로 대응되는 점 개수가 네 개보다 훨씬 많기 때문에 이러한 경우에는 투시 변환 시 에러가 최소가 되는 형태의 호모그래피 행렬을 구해야 한다.`


OpenCV는 두 영상 평면에서 추출된 특징점 매칭 정보로부터 호모그래피를 계산할 때 사용할 수 있는 findHomography() 함수를 제공한다. 함수 원형은 다음과 같다.
```cpp
cv::Mat findHomography(InputArray srcPoints, InputArray dstPoints, int method = 0, double ransacReprojThreshold =3,
                       OutputArray mask = noArray(), const int maxIters = 2000, const double confidence = 0.995);

srcPoints             : 원본 평면상의 점 좌표. CV_32FC2 타입의 Mat 객체 또는 vector<Point2f> 타입의 변수를 지정한다.
dstPoints             : 목표 평면상의 점 좌표. CV_32FC2 타입의 Mat 객체 또는 vector<Point2f> 타입의 변수를 지정한다.
method                : 호모그래피 행렬 계산 방법. 다음 방법중 하나를 지정한다.
                        0       - 모든 점을 사용하는 일반적인 방법. 최소자승법
                        LMEDS   - 최소 메디안 제곱(least-median of squares) 방법
                        RANSAC  - RANSAC 방법
                        RHO     - PROSAC 방법
ransacReprojThreshold : 최대 허용 재투영 에러. 이 값 이내로 특징점이 재투영되는 경우에만 정상치로 간주한다. RANSAC과 RHO 방법에서만                           사용된다.
mask                  : 호모그래피 계산에 사용된 점들을 알려 주는 출력 마스크 행렬. LMEDS와 RANSAC 방법에서만 사용된다.
maxIters              : RANSAC 최대 반복 횟수
confidence            : 신뢰도 레벨. 0에서 1 사이의 실수를 지정한다.
return                : CV_64FC1 타입의 3x3 호모그래피 행렬을 반환. 만약 호모그래피를 계산할 수 없는 상황이라면 비어 있는 Mat 객체가                         반환

```

원본 평면상의 점 좌표를 (xi,yi)로 표현하고 목표 평면상의 점 좌표를 (x'i,y'i)로 표현할 경우, 호모그래피 H는 다음 수식을 최소화하는 형태의 행렬이다.


![캡처](https://user-images.githubusercontent.com/76188802/168795097-00cd2ffe-3efc-4dab-93a5-4ed2b9b7d537.PNG)


앞 수식에서 h(ij){1<=i,j<=3)는 호모그래피 행렬 H의 원소를 나타내고, 다음과 같은 관계를 만족시킨다.


![캡처](https://user-images.githubusercontent.com/76188802/168795287-ef5119d3-2774-40de-90f7-70c0cc2e554c.PNG)


findHomography() 함수의 method 인자에 기본값인 0을 지정하면 입력 점과 출력 점을 모두 사용하는 최소자승법(leas squares)으로 행렬을 계산한다. 그러나 일반적으로 특징점 매칭 결과로부터 호모그래피를 계산할 때 최소자승법을 사용하면 호모그래피가 제대로 계산되지 않는다. 잘못 매칭된 점들처럼 오차가 큰 입력 정보를 이상치(outlier)라고 부르며, 이상치가 많이 존재하는 경우에는 호모그래피 계산 방법 method를 LMEDS, RANSAC, RHO 방법으로 설정하는 것이 좋다. LMEDS 메서드는 보통 이상치가 50% 이하인 경우에 올바르게 동작한다. RANSAC 또는 RHO 방법은 이상치가 50% 이상 존재하더라도 호모그래피 행렬을 잘 찾아 주는 편이다. RANSAC과 RHO 방법을 사용할 경우엔 srcPoints와 dstPoints에 저장된 점이 이상치가 아니라고 판단하기 위한 임계값을 설정해야 하며, 이 값은 ransacReprojThreshold 인자로 지정한다. 만약 *H x srcPoints(i)* 와 *dstPoints(i)* 사이의 거리가 ransacReprojThreshold보다 작으면 정상치(inlier)로 간주한다.

###### RANSAC








