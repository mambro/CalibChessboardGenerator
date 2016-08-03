#CalibChessboardGenerator

This simple tool allows to generate a chessboard with the required characteristics (number of squares, resolution) for 
camera and projector calibration.


Options:
* **-w** *\<image_width\>*        # the width in pixels of the output pattern
* **-h** *\<image_width\>*        # the height in pixels of the output pattern
* **-x** *\<board_width\>*        # the number of inner corners on the horizontal dimension
* **-y** *\<board_width\>*         # the number of inner corners on the vertical dimension
* **-s** *\<square_size\>*        # the size in pixels of each square
* **-sx** *\<square_x_size>       # the size of x side in pixels \n"
* **-sy** *\<square_y_size>       # the size of x side in pixels \n"
* **-save**                   # enable saving of the pattern
* **-show**                   # enable display of the pattern

#Tips
Usually, the calibration requires the projector to show the fullscreen image of the chessboard. This can be obtained following these steps: 

1.  Check the resolution of your projector (e.g., 1024x768) and the aspect ratio (in this case 4:3)
2.  Set the width and the height of the output pattern equal to the projector's resolution
3.  Set the number of **inner** corners on x and y according to the aspect ratio (in this case x/y = 4/3)
4.  Remembering that x and y represent **inner** corners, compute the size value dividing the width by (x+1)
5.  Show the image (-show)
6.  Put the image on the correct monitor
7.  Switch to fullscreen mode

***

Command example:
<pre> ./chessboard_generator -w 1280 -h 800 -x 7 -y 4 -sx 160 -sy 160 -show </pre> 

*This command shows a grid of 8x6 squares for a device with resolution 1024x768.*
