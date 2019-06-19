#include <iostream>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

constexpr int WIDTH = 960;
constexpr int HEIGHT = 380;
constexpr double FPS = 29.97;

int main(int argc, char *argv[])
{
    std::string filename = argv[1];
    std::string outputDir = argv[2];
    std::cout << filename << std::endl;
    std::cout << outputDir << std::endl;

    cv::VideoCapture video(filename);

    std::ofstream times(outputDir + "times.txt");
    auto current = 0.0;

    for (int i = 0; i < 330; i++)
    {
        cv::Mat frame;
        video.read(frame);
    }

    auto i = 0;
    while (true)
    {
        cv::Mat frame, gray, flipped;
        auto success = video.read(frame);
        if (!success)
        {
            break;
        }

        cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);
        cv::Mat distImg(gray, cv::Rect((gray.cols - WIDTH) / 2, (gray.rows - HEIGHT) / 2, WIDTH, HEIGHT));
        cv::flip(distImg, flipped, 0);

        std::stringstream ss;
        ss << std::setfill('0') << std::setw(6) << i;
        auto outputFilename = outputDir + "/" + ss.str() + ".png";
        std::cout << "writing: " << outputFilename << std::endl;
        cv::imwrite(outputFilename, flipped, {9});

        i++;

        times << current << std::endl;
        current += 1.0 / FPS;

        if (i % 100 == 0)
        {
            std::cout << i << std::endl;
        }
    }

    std::cout << i << std::endl;

    times.close();
    video.release();

    return 0;
}
