#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <iostream>
#include <vector>
#include <cstdio>

using namespace cv;
using namespace std;

// specify board width and height
// specify output image size
// specify (optional) pixel size of squares

static void help(){
    printf("This is a chessboard pattern generator.\n"
           "Usage: chessboard_test\n"
           "    -w <image_width>        # the width in pixels of the output pattern\n"
           "    -h <image_height>        # the height in pixels of the output pattern\n"
           "    -x <board_width>        # the number of inner corners on the horizontal dimension\n"
           "    -y <board_height>        # the number of inner corners on the vertical dimension\n"
           "    -sx <square_x_size>       # the size of x side in pixels \n"
           "    -sy <square_y_size>       # the size of y side in pixels \n"
           "    -save                   # enable saving of the pattern\n"
           "    -show                   # enable display of the pattern\n"
           "\n" );
}

int main(int argc, char** argv){
    
    Size2f boardSize,imageSize;
    float sqr_x_Size = -1;
    float sqr_y_Size = -1;
    bool save_image = false;
    bool show_image = false;

   
   imageSize = Size(1024,768);
    // parse arguments
    if( argc < 2 )
    {
        help();
        return 0;
    }
    
    for(int i=1;i<argc;i++)
    {
        const char* s = argv[i];
        
        if( strcmp( s, "-w" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &imageSize.width ) != 1 || imageSize.width <= 0 )
                return fprintf( stderr, "Invalid image width\n" ), -1;
        }
        else if( strcmp( s, "-h" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &imageSize.height ) != 1 || imageSize.height <= 0 )
                return fprintf( stderr, "Invalid image height\n" ), -1;
        }
        else if( strcmp( s, "-x" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &boardSize.width ) != 1 || boardSize.width <= 0 )
                return fprintf( stderr, "Invalid board height\n" ), -1;
        }
        else if( strcmp( s, "-y" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &boardSize.height ) != 1 || boardSize.height <= 0 )
                return fprintf( stderr, "Invalid board height\n" ), -1;
        }
        else if( strcmp( s, "-sx" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &sqr_x_Size ) != 1 || sqr_x_Size <= 0 )
                return fprintf( stderr, "Invalid square size\n" ), -1;
        }
        else if( strcmp( s, "-sy" ) == 0 )
        {
            if( sscanf( argv[++i], "%f", &sqr_y_Size ) != 1 || sqr_y_Size <= 0 )
                return fprintf( stderr, "Invalid square size\n" ), -1;
        }
        else if(strcmp("-save",s)==0)
        {
            save_image = true;
        }
        else if(strcmp("-show",s)==0)
        {
            show_image = true;
        }
        else
            return fprintf( stderr, "unknown option %s", s), -1;
    }

    boardSize.width++;
    boardSize.height++;
    
    float scl = 0.75;
    
    if( sqr_x_Size <= 0 || sqr_y_Size <= 0 ){
        
        // auto calculate square size
        float x_sz = imageSize.width / (float)boardSize.width;
        float y_sz = imageSize.height / (float)boardSize.height;
        x_sz *= scl;
        y_sz *= scl;
        
        sqr_x_Size = min(x_sz, y_sz);
        sqr_y_Size = sqr_x_Size;
        cout << "square size = " << sqr_x_Size << endl;
    }
    
    Size2f chess_img_x_size = boardSize * sqr_x_Size;
    Size2f chess_img_y_size = boardSize * sqr_y_Size;

    
    Point2f roi_vertex( (imageSize.width - chess_img_x_size.width)/2,
                       (imageSize.height - chess_img_y_size.height)/2 );
    
    Mat chessboard(imageSize,CV_8UC3,Scalar::all(255));
    Mat chessboard_roi( chessboard,Rect(roi_vertex.x,roi_vertex.y,chess_img_x_size.width,chess_img_y_size.height ) );
    
    cout << "Initializing chessboard..";
    for (int r=0; r<boardSize.height; r++)
    {
        for (int c=0; c<boardSize.width; c++)
        {
            Mat sub_roi(chessboard_roi,Rect(sqr_x_Size*c,sqr_y_Size*r,sqr_x_Size,sqr_y_Size));
            
            if( (r+c)%2 == 1 )
                sub_roi.setTo(Scalar::all(255));
            else
                sub_roi.setTo(Scalar::all(0));
        }
    }
    cout << "done" << endl;
    
    // generate filename
    char buf[50];
    sprintf(buf,"chessboard_%dx%d.png",boardSize.width-1,boardSize.height-1);
    string fname(buf);
    
    if( save_image ){
        imwrite(fname, chessboard);
    }
    
    if( show_image ){
        imshow(fname, chessboard);
        waitKey(0);
    }
    
    return 0;
}