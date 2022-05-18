# ImageStitching


---

영상 이어 붙이기(image stitching)는 여러 장의 영상을 서로 이어 붙여서 하나의 큰 영상을 만드는 기법이다. `영상 이어 붙이기로 만들어진 영상을 파노라마 영상(panorama image)`이라고 부르며, 많은 디지털 카메라 또는 스마트폰 카메라 앱에서도 파노라마 영상을 만들어 주는 기능을 제공한다. 영상 이어 붙이기에서 입력으로 사용할 영상은 `서로 일정 비율 이상으로 겹치는 영역이 존재`해야 하며, `서로 같은 위치를 분간할 수 있도록 유효한 특징점`이 많이 있어야 한다.


영상 이어 붙이기를 수행하려면 입력 영상에서 특징점을 검출하고, 서로 매칭을 수행하여 호모그래피를 구해야 한다. 그리고 구해진 호모그래피 행렬을 기반으로 입력 영상을 변형하여 서로 이어 붙이는 작업을 수행한다. 이때 영상을 이어 붙인 결과가 자연스럽게 보이도록 이어 붙인 영상의 밝기를 적절하게 보정하는 블렌딩 처리도 해야한다. OpenCV는 이러한 일련의 영상 이어 붙이기 작업을 수행하는 Stitcher 클래스를 제공한다.


Stitcher 클래스를 이용해 여러 장의 영상을 이어 붙이려면 먼저 Stitcher 객체를 생성한다. Stitcher 클래스 객체를 생성하려면 Stitcher 클래스에서 제공하는 Stitcher::create() 정적 멤버 함수를 사용한다. Stitcher::create() 함수 원형은 다음과 같다.

```cpp

static Ptr<Stitcher> Stitcher::create(Mode mode = Stitcher::PANORAMA);

mode	: 이어 붙이기 방식. Stitcher::PANORAMA 또는 Stitcher::SCANS를 지정한다.
return	: Stitcher 객체를 참조하는 Ptr 스마트 포인터 객체
```

만약 스캐너 등으로 스캔한 여러 장의 영상을 이어 붙이려면 Stitcher::SCANS를 mode 값으로 지정한다. Stitcher::PANORAMA ㅗ드는 입력 영상들이 서로 투시 변환(또는 호모그래피) 관계에 있다고 가정하고, Stitcher::SCANS 모드는 입력 영상들이 서로 어파인 변환 관계라고 간주한다.


Stitcher 객체 생성 후 영상을 실제로 이어 붙이는 작업은 Stitcher::stitch() 함수다. 다수의 영상을 입력으로 받고, 이어 붙인 결과 영상을 반환한다. 함수 원형은 다음과 같다

```cpp
Stitcher::Status Stitcher::stitch(InputArrayOfArrays images, OutputArray pano);

images	: 입력 영상의 벡터. std::vector<cv::Mat> 타입을 사용한다.
pano	: 출력 파노라마 영상
return	: 함수 동작 결과 코드. 이 값이 Stitcher:Status::OK면 정상 동작을 의미.(상수)
```

Stitcher::stitch() 함수는 images에 포함된 입력 영상에서 ORB 특징점을 찾아 서로 매칭하고 호모그래피 행렬을 계산한다. 그리고 호모그래피 행렬을 이용해 인접한 영상을 적절하게 투시 변환하고, 서로 이어 붙인 부분의 밝기를 적절하게 보정한 결과 영상 pano를 반환한다.







