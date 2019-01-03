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

void Pause()
{
    printf("Press Enter key to continue...");
    fgetc(stdin);
}
int main()
{
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
        imshow("Lena_original", src);

        Mat gray_src,dst;

        cvtColor(src, gray_src, CV_BGR2GRAY);
        imshow("Lena_gray", gray_src);

        /*
        �ϥήɾ�:�ڭ̥i�z�L�Ԧ�����ϡA�Ϫ�����л\�Ҧ��j�׽d��A�o�ؤ�k���T�ണ���v�����סA���O�b�h�Ʊ��p�A�v���ҽk���O�]���L�����j�׽d��A�ӬO�Y�϶��������j�פ�ҹL���A�o�ɥi�H�s�@�@�ӬM�g��A�ϱo�վ㤧�᪺�v���A�७���ϥΩҦ����j�סA�i�ӼW�[�v����������סC

        OpenCV����ϵ���
        void equalizeHist(InputArray src, OutputArray dst)

        src�G��J�ϡA8�줸��q�D�ϡC
        dst�G��X�ϡA�M��J�Ϥؤo�B���A�ۦP�C
        equalizeHist()�禡�i�o�쪽��ϵ��ƫ᪺�v���A�H�U���y�{�AOpenCV�w�N�y�{�ʸ˦n�A�ϥήɥu�n�����I�sequalizeHist()�禡�Y�i�G

        �p���J�Ϫ�����ϡC
        �N������k�@��Ҧ�bin���`�X��255�C
        �p�⪽��ϲ֭p��C
        �Ϊ���ϲ֭p�����U�j�ת��M�g�A�ҥH���]�j��30�Ҳֿn����Ҭ�20%�A�M�g���j�קY��255*0.2�A�ѩ�ڭ̪�����k�@�ƨ�255�A�ҥH���]�j��30�Ҳֿn���Ȭ�20�A�M�g���j�קY��20�C
        */
        equalizeHist(gray_src, dst);
        imshow("equalizeHist", dst);
    }

    waitKey(0);
    Pause();
    return 0;
}
