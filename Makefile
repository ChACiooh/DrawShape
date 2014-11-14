all: matrix draw_shape
matrix: matrix.cc matrix_main.cc
	g++ -o matrix matrix.cc matrix_main.cc
draw_shape: draw_shape.cc draw_shape_main.cc
	g++ -o draw_shape draw_shape.cc draw_shape_main.cc

