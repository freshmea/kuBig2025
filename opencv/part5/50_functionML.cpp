#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/plot.hpp>

using namespace std;
using namespace cv;

// 선형 회귀 학습 함수 (동일)
Mat trainLinearRegression(const Mat &samples, const Mat &response)
{
    Mat X(samples.rows, 2, CV_32F);
    for (int i = 0; i < samples.rows; ++i)
    {
        X.at<float>(i, 0) = samples.at<float>(i, 0); // x
        X.at<float>(i, 1) = 1.0f;                    // bias(상수항)
    }
    Mat XtX = X.t() * X;
    Mat XtX_inv;
    invert(XtX, XtX_inv, DECOMP_SVD);
    Mat weights = XtX_inv * X.t() * response;
    return weights; // [기울기; 절편]
}

// 예측 함수 (동일)
float predictLinearRegression(const Mat &weights, float x)
{
    return weights.at<float>(0, 0) * x + weights.at<float>(1, 0);
}

int main()
{
    // 데이터를 Mat으로 생성
    Mat x_data = (Mat_<float>(10, 1) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    Mat y_data(10, 1, CV_32F);

    RNG rng(12345);
    for (int i = 0; i < x_data.rows; ++i)
    {
        float noise = rng.gaussian(0.5f);
        y_data.at<float>(i, 0) = 2.f * x_data.at<float>(i, 0) + 1.f + noise;
    }

    // 회귀 학습
    Mat weights = trainLinearRegression(x_data, y_data);

    cout << "학습된 기울기 weight: " << weights.at<float>(0, 0) << endl;
    cout << "학습된 절편 bias: " << weights.at<float>(1, 0) << endl;

    // 요청에 따라 플롯에 사용될 기울기를 2.0으로, 절편을 1.0으로 강제 설정
    weights.at<float>(0, 0) = 2.0f;
    weights.at<float>(1, 0) = 1.0f; // 데이터 생성 시 y = 2x + 1 형태에 맞춤

    cout << "플롯에 사용될 강제 기울기: " << weights.at<float>(0, 0) << endl;
    cout << "플롯에 사용될 강제 절편: " << weights.at<float>(1, 0) << endl;

    // 회귀선 생성 (예측) - 강제 설정된 weights 사용
    Mat x_line = (Mat_<float>(2, 1) << 1, 10); // 구간 [min, max]
    Mat y_line(2, 1, CV_32F);
    for (int i = 0; i < 2; ++i)
    {
        y_line.at<float>(i, 0) = predictLinearRegression(weights, x_line.at<float>(i, 0));
    }

    // 데이터 타입을 double로 변환 (plot 모듈 요구사항)
    Mat x_data_d, y_data_d, x_line_d, y_line_d;
    x_data.convertTo(x_data_d, CV_64F);
    y_data.convertTo(y_data_d, CV_64F);
    x_line.convertTo(x_line_d, CV_64F);
    y_line.convertTo(y_line_d, CV_64F);

    // 산점도 플롯, 그리드 없이 데이터만
    Ptr<plot::Plot2d> scatterPlot = plot::Plot2d::create(x_data_d, y_data_d);
    scatterPlot->setShowGrid(false);                  // 그리드 표시 안 함
    scatterPlot->setShowText(false);                  // 텍스트 표시 안 함
    scatterPlot->setNeedPlotLine(false);              // 선 연결 안 함
    scatterPlot->setPlotLineColor(Scalar(0, 0, 255)); // 검은색 점
    scatterPlot->setPlotLineWidth(10);                // 점 크기 조정

    // 회귀선 플롯
    Ptr<plot::Plot2d> linePlot = plot::Plot2d::create(x_line_d, y_line_d);
    linePlot->setShowGrid(false); // 그리드 표시 안 함
    linePlot->setShowText(false); // 텍스트 표시 안 함
    // x, y 축에  대한 설정 숫자 표시

    // 플롯 렌더
    Mat scatterResult, lineResult;
    scatterPlot->render(scatterResult);
    linePlot->render(lineResult);

    // 산점도 위에 회귀선 합성
    addWeighted(scatterResult, 1.0, lineResult, 1.0, 0.0, scatterResult);

    // x 축 반전
    flip(scatterResult, scatterResult, 0); // x축 반전

    imshow("OpenCV Plot 모듈 예제", scatterResult);
    waitKey(0);

    return 0;
}
