# Python 3.11 slim 버전을 기반으로 사용
FROM python:3.11-slim-bullseye

# 시스템 업데이트 및 필요한 의존성 설치
RUN apt-get update && apt-get install -y --no-install-recommends \
    # 기본 빌드 도구 및 유틸리티
    build-essential \
    git \
    pkg-config \
    wget \
    curl \
    bash \
    # Kitware APT 저장소 추가에 필요
    apt-transport-https \
    ca-certificates \
    gnupg \
    software-properties-common \
    # Python 관련
    python3-pip \
    python3-dev \
    # Protobuf (ONNX 등에서 사용 가능)
    protobuf-compiler \
    libprotobuf-dev \
    # OpenCV 빌드 의존성
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libwebp-dev \
    libopenexr-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libv4l-dev \
    libgtk-3-dev \
    libtbb-dev \
    libopenblas-dev \
    libeigen3-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# CMake 3.24.0 소스에서 빌드
RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.0/cmake-3.24.0.tar.gz \
    && tar -zxvf cmake-3.24.0.tar.gz \
    && cd cmake-3.24.0 \
    && ./bootstrap --prefix=/usr/local \
    && make -j$(nproc) \
    && make install \
    && cd .. \
    && rm -rf cmake-3.24.0 cmake-3.24.0.tar.gz

# NumPy 및 ONNX 관련 패키지 설치
RUN pip3 install numpy onnx onnxruntime

# OpenCV 4.11.0 및 opencv_contrib 소스 다운로드
RUN git clone --branch 4.11.0 https://github.com/opencv/opencv.git /opencv \
    && git clone --branch 4.11.0 https://github.com/opencv/opencv_contrib.git /opencv_contrib

# OpenCV 빌드 및 설치
RUN mkdir -p /opencv/build && cd /opencv/build \
    && PYTHON3_EXECUTABLE=$(which python3) \
    && PYTHON3_INCLUDE_DIR=$(python3 -c "from sysconfig import get_paths; print(get_paths()['include'])") \
    && PYTHON3_LIBRARY=$(python3 -c "import sysconfig; libdir = sysconfig.get_config_var('LIBDIR'); ldlibrary = sysconfig.get_config_var('LDLIBRARY'); print(f'{libdir}/{ldlibrary}')") \
    && PYTHON3_NUMPY_INCLUDE_DIRS=$(python3 -c "import numpy; print(numpy.get_include())") \
    && PYTHON3_PACKAGES_PATH=$(python3 -c "from sysconfig import get_paths; print(get_paths()['purelib'])") \
    && cmake -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/usr/local/opencv-4.11 \
    -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON \
    -D BUILD_TESTS=OFF \
    -D BUILD_PERF_TESTS=OFF \
    -D BUILD_DOCS=OFF \
    -D BUILD_opencv_python3=ON \
    -D BUILD_opencv_java=OFF \
    -D BUILD_opencv_js=OFF \
    -D BUILD_opencv_ts=OFF \
    -D BUILD_opencv_world=OFF \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_OPENGL=ON \
    -D WITH_FFMPEG=ON \
    -D WITH_GSTREAMER=ON \
    -D WITH_OPENEXR=ON \
    -D WITH_CUDA=OFF \
    -D WITH_CUDNN=OFF \
    -D WITH_CUBLAS=OFF \
    -D WITH_OPENCL=ON \
    -D WITH_IPP=ON \
    -D WITH_EIGEN=ON \
    -D WITH_QT=OFF \
    -D WITH_GTK=ON \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D OPENCV_DNN_CUDA=OFF \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_PYTHON3_INSTALL_PATH=${PYTHON3_PACKAGES_PATH} \
    -D PYTHON3_EXECUTABLE=${PYTHON3_EXECUTABLE} \
    -D PYTHON3_INCLUDE_DIR=${PYTHON3_INCLUDE_DIR} \
    -D PYTHON3_LIBRARY=${PYTHON3_LIBRARY} \
    -D PYTHON3_NUMPY_INCLUDE_DIRS=${PYTHON3_NUMPY_INCLUDE_DIRS} \
    -D PYTHON3_PACKAGES_PATH=${PYTHON3_PACKAGES_PATH} \
    -D BUILD_opencv_dnn=ON \
    -D OPENCV_DNN_OPENCL=ON \
    -D WITH_ONNX=ON \
    -D CMAKE_CXX_FLAGS="-Wno-undef -Wno-cast-user-defined" .. \
    && make -j$(nproc) \
    && make install \
    && cd / && rm -rf /opencv /opencv_contrib

# 환경 변수 설정
ENV LD_LIBRARY_PATH=/usr/local/opencv-4.11/lib:$LD_LIBRARY_PATH
ENV PKG_CONFIG_PATH=/usr/local/opencv-4.11/lib/pkgconfig:$PKG_CONFIG_PATH

# 작업 디렉토리 설정
WORKDIR /app

# 기본 명령어
CMD ["bash"]