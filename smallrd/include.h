#pragma once
#include<iostream>
#include<stdlib.h>

#define MAXXRES 1024
#define MAXYRES 1024
#define CLAMP(x, min, max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : (x))) //clamp x into [min, max]
#define INBOUND(x, min, max) ((x) >= (max) ? false : ((x) < (min) ? false : true)) //if x is in [min, max)
#define	ARRAY(x, y, col) ((x) + (y) * (col))

