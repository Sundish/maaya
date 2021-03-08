main:
	cc -o maya main.c `pkg-config --cflags --libs MagickWand`
