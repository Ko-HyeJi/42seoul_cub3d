#include "cub3d.h"

double normalize_fisheye(double ang)
{
	if (ang >= 0)
	{
		while (ang >= TWO_PI)
			ang -= TWO_PI;
	}
	else
	{
		while (ang <= 0)
			ang += TWO_PI;
	}
	return ang;
}
