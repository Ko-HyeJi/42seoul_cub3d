#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

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
	double rotation_angle;//바라보는각도. 시야각도
	double walk_speed;//움직이는 속도
	double turn_speed;//바라보는 각도의 조정속도
}				t_player;

typedef struct	s_key
{
	bool up;
	bool down;
	bool left;
	bool right;
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
}				t_temp_ray;//변수명 다시

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
}				t_ray;//변수명 다시
//광선이 벽과 만나는 좌표와
//광선의 방향적인 요소를 가지고있다

typedef struct	s_map
{
	unsigned long long	row;//ull..?
	unsigned long long	col;
	char				**dp_map;
	unsigned long long	row_tile_size;
	unsigned long long	col_tile_size;
}				t_map;//필요시 minimap으로

typedef struct	s_map_info
{
	void*	no;
	void*	so;
	void*	we;
	void*	ea;
	int		f;
	int		c;
	char**	tile;
	int		info_cnt;
	int		tile_cnt;
}				t_map_info;

typedef struct	s_all
{
	t_mlx		mlx;
	t_img		img;
	t_player	player;
	t_key		key;
	t_ray		ray;
	t_map		map;
	t_map_info		map_info; //구조체 이름 수정 필요
}				t_all;

#define MINI_SCALE 0.5
#define TILE_SIZE 80

#define WINDOW_WID 640
#define WINDOW_HEI 480

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
// # define X_EVENT_WINDOW_DESTROY 17

#define PI     (3.14159265358979323846264338327950288)
#define TWO_PI (6.28318530717958647692528676655900576)

#define RAY_RANGE (PI / 3.0) // player 시야범위. 무난하게 60도
#define RAY_COUNT 121 // 광선의 갯수. 2보다 커야하고 홀수 추천

// #define BUFFER_SIZE 333

int		key_press(int keycode, t_all *p_all);
void	init_player(t_all *p_all);
bool	hit_wall(double x, double y, t_all *p_all);
void	update_player(t_all *p_all);
void	fill_square(t_all *p_all, int x, int y, int color);
void	render_map(t_all *p_all);
void	draw_player(t_all *p_all);
int		ft_loop(t_all *p_all);//이름 수정할거임
void	render_player(t_all *p_all);
int		key_release(int keycode, t_all *p_all);

void	ray_init(t_ray *p_ray, double ang);
void	calc_distance(t_all *p_all, t_temp_ray *hv);
double	distance_btw_points(double xa, double ya, double xb, double yb);
void	calc_ray(t_all *p_all, t_temp_ray *hv);
void	calc_horz_ray(t_all *p_all, t_temp_ray *p_horz);
void	calc_vert_ray(t_all *p_all, t_temp_ray *p_vert);
void	draw_line(t_all *p_all, double xa, double ya, double xb, double yb);
void	draw_one_ray(t_all *p_all, double ang);
void	draw_ray(t_all *p_all);
double	normalize_angle(double ang);

void	get_row_col(char *argv, t_all *p_all);
void	get_map(char *argv, t_all *p_all);

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(const char *s1, const char *s2);
char	*for_next(char *save);
char	*rtg(char *save);
char	*read_and_save(int fd, char *save);
char	*get_next_line(int fd);

void	locate_for_mini(int *xp, int *yp, int x, int y, t_all *p_all);
void	init_map(char *argv, t_all *p_all);

#endif
