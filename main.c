#include "minilibx/mlx.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/get_next_line.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct s_square {
	int	startX;
	int endX;
	int startY;
	int	endY;
	int	color;
}				t_square;


int windowWidth = 1920;
int	windowHeight = 1080;
int squareWidth = 1000;
int squareHeight = 500;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	makesquare(t_data *data, t_square square)
{
	for (int i = square.startX; i <= square.endX; i++)
	{
		for (int j = square.startY; j <= square.endY; j++)
		{
			my_mlx_pixel_put(data, i, j, square.color);
		}
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_square	square;

	square.startX = (windowWidth / 2) - (squareWidth / 2);
	square.endX = (windowWidth / 2) + (squareWidth / 2);
	square.startY = (windowHeight / 2) - (squareHeight / 2);
	square.endY = (windowHeight / 2) + (squareHeight / 2);
	square.color = 0x262626;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, windowWidth, windowHeight, "Hello world!");
	img.img = mlx_new_image(mlx, windowWidth, windowHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	makesquare(&img, square);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
