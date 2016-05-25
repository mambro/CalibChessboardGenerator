This simple tool allows to generate a chessboard with the required characteristics (number of squares, resolution) for 
camera and projector calibration.


Options: 
    -w <image_width>        # the width in pixels of the output pattern
    -h <image_width>        # the height in pixels of the output pattern
    -x <board_width>        # the number of inner corners on the horizontal dimension
    -y <board_width>        # the number of inner corners on the vertical dimension
    -s <square_size>        # the size in pixels to make each square
    -save                   # enable saving of the pattern
    -show                   # enable display of the pattern


Command example:

./chessboard_generator -w 1280 -h 800 -x 8 -y 5 -s 159 -show