#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include "key_macos.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

typedef struct	s_img
{
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
	int		*data;
}				t_img;

typedef struct	s_player
{
	double x;
	double y;
	double rotation_angle;
	double walk_speed;
	double turn_speed;
}				t_player;

typedef struct	s_key
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool right_rotation;
	bool left_rotation;
}				t_key;

typedef struct	s_temp_ray
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		found_wallHit;
	double	xhit_wall;
	double	yhit_wall;
	double	distance;
}				t_temp_ray;

typedef struct	s_ray
{
	double	ray_angle;
	double	xhit_wall;
	double	yhit_wall;
	double	distance;
	bool	vert_hit;
	bool	ray_faces_down;
	bool	ray_faces_up;
	bool	ray_faces_right;
	bool	ray_faces_left;
}				t_ray;

typedef struct	s_map
{
	unsigned long long	row;
	unsigned long long	col;
	char				**dp_map;
	double	row_tile_size;
	double	col_tile_size;
}				t_map;

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_map_info //map 구조체에 합칠지 고민중...(hyko)
{
	void	*v_texture[4];
	int		*i_texture[4];
	int		f;
	int		c;
	char**	tile;
	int		info_cnt;
	int		tile_cnt;
}				t_map_info;

typedef	enum	e_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	TILE,
}				t_type;

typedef struct	s_all
{
	t_img		img;
	t_player	player;
	t_key		key;
	t_ray		ray;
	t_map		map;
	void		*mlx;
	void		*win;
	t_map_info	map_info;
}				t_all;

#define MINI_SCALE 0.25

#define WINDOW_WID 640
#define WINDOW_HEI 480

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_WINDOW_DESTROY 17

#define PI     (3.14159265358979323846264338327950288)
#define TWO_PI (6.28318530717958647692528676655900576)
#define HALF_PI (1.57079632679489661923132169163975144)
#define RAY_COUNT WINDOW_WID

#define BUFFER_SIZE 333

#define FOV_ANGLE 60 * (PI / 180.0)
#define WALL_STRIP_WIDTH 1
#define	BLUE 0x0000FF
#define	WHITE 0xFFFFFF
#define	GREY 0xAAAAAA
#define	BLACK 0x000001 //초기화 값과 구분하기 위해 블루 한방울...(hyko)
#define	PINK 0xFF00FF
#define	RED 0xFF0000

#define COLOR_N RED
#define COLOR_S BLUE
#define COLOR_E	GREY
#define COLOR_W PINK

#define TEXTURE_HEIGHT 64
#define TEXTURE_WIDTH 64

int		key_press(int keycode, t_all *p_all);
void	init_player(t_all *p_all);
bool	hit_wall(double x, double y, t_all *p_all);
void	update_player(t_all *p_all);
void	fill_square(t_all *p_all, int x, int y, int color);
void	render_map(t_all *p_all);
void	draw_player(t_all *p_all);
int		ft_loop_hook(t_all *p_all);
int		key_release(int keycode, t_all *p_all);

void	ray_init(t_ray *p_ray, double ang);
void	calc_distance(t_all *p_all, t_temp_ray *hv);
double	distance_btw_points(double xa, double ya, double xb, double yb);
void	calc_ray(t_all *p_all, t_temp_ray *hv, int a, int b);
void	calc_horz_ray(t_all *p_all, t_temp_ray *p_horz);
void	calc_vert_ray(t_all *p_all, t_temp_ray *p_vert);
void	draw_line(t_all *p_all, double dx, double dy);
void	draw_one_ray(t_all *p_all, double ang, int i);
void	draw_ray(t_all *p_all);
double	normalize_fisheye(double ang);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(const char *s1, const char *s2);
char	*for_next(char *save);
char	*rtg(char *save);
char	*read_and_save(int fd, char *save);
char	*get_next_line(int fd);

void	locate_for_mini(int *xp, int *yp, t_point p);

void    render_3d_wall(t_all *p_all, int ray_num);
void	set_point(t_point *p_point, double x, double y);
void    render_3d(t_all *p_all);

void	draw_ceiling(t_all *p_all, int ray_num, int wall_top_pixel, int color);
void	draw_floor(t_all *p_all, int ray_num, int wall_bottom_pixel, int color);

void	init_mlx(t_all *p_all);
void	init_key(t_all *p_all);
void	ft_init(t_all *p_all);
void	loop_hook(t_all *p_all);
void	init_img_data(t_all* p_all);

void	parse_map(int argc, char** argv, t_all* all);
void	is_cub_file(const char* filename);
void	check_type(char* line, t_all *all);
void	display_err_msg_and_exit(const char* err_msg);

void	set_texture_img(t_all* all);

bool	check_edge(t_all *p_all, t_point p1, t_point p2);

int	mouse(void);

#endif
