#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <cstdio>

#include <sys/timeb.h>
#if defined(WIN32)
    #define  TIMEB    _timeb
    #define  ftime    _ftime
    typedef __int64 TIME_T;
#else
    #define TIMEB timeb
    typedef long long TIME_T;
#endif

using namespace cv;
using namespace std;
Mat src;//input image

Mat dst, map_x, map_y;
int index = 0;
void update_map(void);

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
    const char* OUTPUT_TITLE = "remap demo";

    Mat input;
	input = imread("Lena_original.jpg");
	if (!input.data)
    {
		printf("could not load image...\n");
	}
    else
    {
        //��j
        pyrUp(input, src, Size(input.cols*2, input.rows*2));

        namedWindow("Lena_original", CV_WINDOW_AUTOSIZE);
        imshow("Lena_original", src);

        namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);

        map_x.create(src.size(), CV_32FC1);
        map_y.create(src.size(), CV_32FC1);
        dst=Mat::zeros(src.size(),src.type());

        int c = 0;
        while (true) {
            c = waitKey(500);
            if ((char)c == 27) {//ESC
                break;
            }
            index = c % 4;
            printf("%d -> %d\n",c,index);
            update_map();
            /*
            �X���ܴ�(remap)
            OpenCV���M�g
            void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interpolation, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())

            src�G��J�ϡC
            dst�G��X�ϡA���A�M��J�ϬۦP�C
            map1�G�Ĥ@�ӿ�J���M�g��A���A�i��CV_16SC2�BCV_32FC1��CV_32FC2�A�ؤo�M��J�ϬۦP�A�M�g���ȥN���O��J�Ϧ�������m�n�ಾ�h���sx�y�СC
            map2�G�ĤG�ӿ�J���M�g��A���A�i��CV_16UC1�� CV_32FC1�A�ؤo�M��J�ϬۦP�A�M�g���ȥN���O��J�Ϧ�������m�n�ಾ�h���sy�y�СC�C
            interpolation�G�������A�C
            borderMode�G��ɼҦ��A�w�]��BORDER_CONSTANT�C
            borderValue�G��ɥ~���ȡA�w�]�j�׬�0�C
            */
            remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 255, 255));
            imshow(OUTPUT_TITLE, dst);
        }
    }

    waitKey(0);
    Pause();
    return 0;
}

void update_map(void) {
	for (int row = 0; row < src.rows; row++) {//���� X
		for (int col = 0; col < src.cols; col++) {//�e�� Y
			switch (index) {
			case 0://�Y�p�@�b
				if (col > (src.cols * 0.25) && col <= (src.cols*0.75) && row > (src.rows*0.25) && row <= (src.rows*0.75)) {
					map_x.at<float>(row, col) = 2 * (col - (src.cols*0.25));
					map_y.at<float>(row, col) = 2 * (row - (src.rows*0.25));
				}
				else {
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			case 1://X����
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
			case 2://Y����
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			case 3://XY����
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			}

		}
	}
}
