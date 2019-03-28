#include <math.h>
float B_SIZE;

void setBlocSize(float size) {
	B_SIZE = floorf(size * 10) / 10;
}

float getBlocSize() {
	return B_SIZE;
}

int getBlocFullSize() {
	return (int)(B_SIZE * 2);
}