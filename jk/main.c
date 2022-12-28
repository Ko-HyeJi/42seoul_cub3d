#include "cub3d.h"

int ft_loop(t_all *p_all)//이름 수정할거임
{
	update_player(p_all);//later
	render_map(p_all);
	// render_player(p_all);
	draw_player(p_all);
	// draw_ray(p_all);여기에 없어도 될것같은딩..?
	mlx_put_image_to_window(p_all->mlx, p_all->win, p_all->img.img, 0, 0);
	return (0);
}

void	init_mlx(t_all *p_all)
{
	p_all->mlx = mlx_init();//디스플레이와 내 프로그램을 연결 시켜주고,
	p_all->win = mlx_new_window(p_all->mlx, WINDOW_WID, WINDOW_HEI, "title");//새로운 창 화면에 만들고
	p_all->img.img = mlx_new_image(p_all->mlx, WINDOW_WID, WINDOW_HEI);//지정한 가로 세로로 만들어진 직사각형을 보이지 않는 공간에 그려두고(메모리에 새 이미지 만들고), 
	p_all->img.data = (int *)mlx_get_data_addr(p_all->img.img, &(p_all->img.bpp), 
										&(p_all->img.size_line), &(p_all->img.endian));
	//생성된 이미지에 대한 정보 반환해서, 나중에 user가 이 정보 수정할수있음
}

void	init_key(t_all *p_all)
{
	p_all->key.up = false;
	p_all->key.down = false;
	p_all->key.left = false;
	p_all->key.right = false;
	p_all->key.left_rotation = false;
	p_all->key.right_rotation = false;
	p_all->key.updown_sight = false;
}

void	ft_init(t_all *p_all)
{
	init_player(p_all);//player 구조체 초기화시키고, 
	init_key(p_all);//key "
	init_mlx(p_all);//mlx 사용하기 위한 초기 세팅해주고 
}

void	loop_hook(t_all *p_all)
{
	mlx_hook(p_all->win, X_EVENT_KEY_PRESS, 0, &key_press, p_all);//키 누를때
		//mlx상 모든 이벤트가 발생할때 hook 한다.
		//키보드입력이나 마우스클릭을 프로그램에 도달하기전 가로채서 다른 역할하게끔한다.
	mlx_hook(p_all->win, X_EVENT_KEY_RELEASE, 0, &key_release, p_all);//키 떼고있을때
	mlx_loop_hook(p_all->mlx, &ft_loop, p_all);//ft_loop()를 계속 돌린다
		//등록된 이벤트가 발생하지 않을 경우, 두번째 함수 호출함
	// ft_loop(p_all);
	mlx_loop(p_all->mlx);//이벤트를 받고, 이벤트를 관리함. 
		//무한 루프를 돈다.
}

int main(int argc, char **argv)
{
	t_all	s_all;

	(void)argc;
	ft_init(&s_all);
	parse_map(argc, argv, &s_all);
	set_texture_img(&s_all);
	loop_hook(&s_all);

	return (0);
}
