#include "cub3d.h"

double normalize_fisheye(double ang)
{
	if (ang >= 0)
	{
		while (ang >= M_PI * 2)
			ang -= M_PI * 2;
	}
	else
	{
		while (ang <= 0)
			ang += M_PI * 2;
	}
	return ang;
}
