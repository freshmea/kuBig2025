# Alpine Linux 최신 버전을 기반으로 사용
FROM alpine:latest

# 필요한 패키지 설치 (OpenCV 및 CMake 빌드에 필요한 의존성, py3-numpy-dev 추가)
RUN apk update && apk add --no-cache \
    build-base \
    git \
    pkgconf \
    libpng-dev \
    libjpeg-turbo-dev \
    tiff-dev \
    libwebp-dev \
    openexr-dev \
    ffmpeg-dev \
    gstreamer-dev \
    gst-plugins-base-dev \
    libgomp \
    openblas-dev \
    python3 \
    python3-dev \
    py3-numpy \
    py3-numpy-dev \
    linux-headers \
    wget \
    bash \
    curl \
    libstdc++ \
    musl-dev \
    openssl-dev

# Python 경고 억제
ENV PYTHONWARNINGS=ignore

# CMake 3.24.0 소스에서 빌드
RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.0/cmake-3.24.0.tar.gz \
    && tar -zxvf cmake-3.24.0.tar.gz \
    && cd cmake-3.24.0 \
    && ./bootstrap --prefix=/usr/local \
    && make -j$(nproc) \
    && make install \
    && cd .. \
    && rm -rf cmake-3.24.0 cmake-3.24.0.tar.gz

# OpenCV 4.9.0 및 opencv_contrib 소스 다운로드
RUN git clone --branch 4.9.0 https://github.com/opencv/opencv.git /opencv \
    && git clone --branch 4.9.0 https://github.com/opencv/opencv_contrib.git /opencv_contrib

# OpenCV 빌드 및 설치 (Python 및 NumPy 경로 명시, 컴파일러 플래그 추가)
RUN mkdir -p /opencv/build && cd /opencv/build \
    && cmake -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/usr/local/opencv-4.9 \
    -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
    -D BUILD_EXAMPLES=OFF \
    -D BUILD_opencv_python3=ON \
    -D WITH_TBB=OFF \
    -D WITH_V4L=OFF \
    -D WITH_OPENGL=OFF \
    -D WITH_FFMPEG=ON \
    -D WITH_GSTREAMER=ON \
    -D WITH_OPENEXR=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D CMAKE_CXX_FLAGS="-Wno-undef -Wno-cast-user-defined" \
    -D PYTHON3_EXECUTABLE=/usr/bin/python3 \
    -D PYTHON3_INCLUDE_DIR=/usr/include/python3.12 \
    -D PYTHON3_NUMPY_INCLUDE_DIRS=/usr/lib/python3.12/site-packages/numpy/_core/include .. \
    && make -j$(nproc) \
    && make install \
    && cd / && rm -rf /opencv /opencv_contrib

# 환경 변수 설정
ENV LD_LIBRARY_PATH=/usr/local/opencv-4.9/lib:$LD_LIBRARY_PATH
ENV PKG_CONFIG_PATH=/usr/local/opencv-4.9/lib/pkgconfig:$PKG_CONFIG_PATH
ENV PATH=/usr/local/bin:$PATH

# 작업 디렉토리 설정
WORKDIR /app

# 기본 명령어
CMD ["bash"]