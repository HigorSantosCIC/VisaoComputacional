#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Scalar refColor;
Mat frame;

static void onClick( int event, int x, int y, int flags, void * data)
{
	if( event != EVENT_LBUTTONDOWN )
		return;

	refColor = frame.at<Vec3b>(x, y);
	cout << x << " " << y << " | " << refColor << endl;
}

int main(int argc, char** argv )
{
	if( argc < 2 )
		exit(-1);

	VideoCapture camera;
	camera.open(0);

	if( !camera.isOpened() )
		exit(-2);

	Mat background;
	background = imread( argv[1] );
	if( background.empty() )
		exit(-3);

	camera >> frame;
	resize(background, background, frame.size()); //trata casos das imagens serem diferentes

	namedWindow("Visao Computacional", 1);
	setMouseCallback("Visao Computacional", onClick, NULL);
	
	while(1)
	{
		camera >> frame;
		//Função Euclidiana que calcula a distancia
		for(int i = 0; i < frame.rows; i++)
			for(int j = 0; j < frame.cols; j++)
				if(norm(refColor, Scalar(frame.at<Vec3b>(i,j)), NORM_L2) < 70)
					frame.at<Vec3b>(i,j) = background.at<Vec3b>(i,j);

			
		imshow("Visao Computacional", frame);
		if( waitKey(10) == 27 ) break;
	}

	return 0;
}

