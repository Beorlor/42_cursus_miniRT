/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:49:32 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/10 16:22:06 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include <float.h>
# include "minilibx-linux/mlx.h"
# include "42_cursus_libft/Includes/libft.h"

// Dimensions de la fenêtre
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define EPSILON 1e-6

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_MINUS 45
# define KEY_PLUS 61
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Identifiants des objets
typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
} t_object_type;

// Structures de base
typedef struct s_vector
{
	double x;
	double y;
	double z;
} t_vector;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

// Sous-structures pour les objets
typedef struct s_sphere
{
	double diameter;
} t_sphere;

typedef struct s_plane
{
	t_vector normal;
} t_plane;

typedef struct s_cylinder
{
	double	diameter;
	double	height;
	int		disk;
	int		is_base;
	t_vector axis;
} t_cylinder;

typedef struct s_cone
{
	double	diameter;
	double	height;
	t_vector axis;
} t_cone;

typedef struct s_noise
{
	int		octaves;
	double	frequency;
	double	persistence;
	double	intensity;
} t_noise;

typedef struct s_object
{
	t_object_type type;
	bool is_selected;
	bool checkerboard;
	t_noise noise;
	t_vector pos;
	t_color color;
	union
	{
		t_sphere sphere;
		t_plane plane;
		t_cylinder cylinder;
		t_cone cone;
	} specific;
	struct s_object *next;
} t_object;

// Structure de la scène
typedef struct s_ambient
{
	double ratio;
	t_color color;
} t_ambient;

typedef struct s_camera
{
	t_vector pos;
	t_vector orient;
	t_vector right;
	t_vector up;
	int fov;
	double fov_rad;
} t_camera;

typedef struct s_light
{
	t_vector pos;
	double brightness;
	t_color color;
	struct s_light *next;
} t_light;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int q;
	int e;
	int t;
	int y;
	int g;
	int h;
	int b;
	int n;
} t_keys;

typedef struct s_ray
{
	t_vector direction;
	t_vector origin;
} t_ray;

typedef struct s_inter
{
	double		coef_a;
	double		coef_b;
	double		coef_c;
	double		radius;
	double		delta;
	double		r1;
	double		r2;
	double		ray_dir_v;
	double		c_min;
	double		c_max;
	double		P1_proj;
	double		P2_proj;
	double		oc_v;
	double		closest;
	t_vector	cap_pos;
	t_vector	oc;
	t_vector	oc_perp;
	t_vector	dir_perp;
	t_vector	cylinder_center;
	t_vector	P1;
	t_vector	P2;
	t_vector	cone_apex;
} t_inter;

typedef struct s_perlin
{
	int		int_x;
	int		int_y;
	double	frac_x;
	double	frac_y;
	double	a;
	double	b;
	double	c;
	double	d;
	double	interpolate_x1;
	double	interpolate_x2;
} t_perlin;

typedef struct s_shadow
{
	t_vector	light_dir;
	t_vector	normal;
	t_color		ambient;
	t_color		color;
	t_color		diffuse;
	t_color		specular;
	t_vector	view_dir;
	double		shadow_factor;
	double		shininess;
	double		d_light;
} t_shadow;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}	t_img;

typedef struct s_checker
{
	t_color		black;
	t_color		white;
	t_vector	relative_pos;
	int			check_theta;
	int			check_height;
	double		theta;
	double		height;
	double		scale;
}	t_checker;

typedef struct s_data
{
	void *mlx;
	void *window;
	int object_count;
	int	flag;
	double farthest_object;
	double total_rays;
	double view_width;
	double view_height;
	double z_buffer[WINDOW_HEIGHT + 1][WINDOW_WIDTH + 1];
	t_ambient ambient;
	t_camera camera;
	t_light *light;
	t_object *objects;
	t_keys keys;
	t_ray	ray;
	t_img	*img;
} t_data;

// Prototypes de fonctions
int			validate_filename(const char *filename);
int			validate_color(t_color color);
int			validate_ambient(t_data *data);
int			validate_camera(t_data *data);
int			validate_light(t_data *data);
int			validate_scene_elements(t_data *data);
int			parse_ambient_color(char **color_split, t_data *data);
int			parse_ambient(char **split, t_data *data);
int			parse_camera_position(char **pos_split, t_data *data);
int			parse_camera_orientation(char **orient_split, t_data *data);
int			parse_camera(char **split, t_data *data);
int			parse_light_position(char **pos_split, t_light *new_light);
int			parse_light_color(char **color_split, t_light *new_light);
void		add_light_to_list(t_data *data, t_light *new_light);
int			parse_light(char **split, t_data *data);
double		ft_atof_sign(const char **str);
double		ft_atof_integer(const char **str);
double		ft_atof_fraction(const char **str);
double		ft_atof(const char *str);
void		free_split(char **split);
char		*construct_scene_path(const char *filename);
void		init_scene_data(t_data *data);
int			parse_scene_file(int fd, t_data *data);
int			check_mandatory_elements(t_data *data);
int			parse_scene(const char *filename, t_data *data);
int			parse_known_object(char **split, t_data *data);
int			parse_line(char *line, t_data *data);
int			parse_object_options(char **split, t_object *obj);
int			parse_perlin_noise(char **split, t_noise *noise);
int			parse_sphere_data(char **split, t_object *obj);
int			parse_sphere(char **split, t_data *data);
int			parse_plane_data(char **split, t_object *obj);
int			parse_plane(char **split, t_data *data);
int			parse_cylinder_data(char **split, t_object *obj);
int			parse_cylinder(char **split, t_data *data);
int			parse_cone_data(char **split, t_object *obj);
int			parse_cone(char **split, t_data *data);
int	is_split_valid(char **split1, char **split2, char **split3);

void		free_objects(t_object *objects);
void		free_split(char **split);
double		ft_atof(const char *str);
void 		free_data(t_data *data);
int			handle_close(t_data *data);

// Event handling functions
int			handle_keypress(int keycode, t_data *data);
int			handle_keyrelease(int keycode, t_data *data);
int			handle_mouse(int button, int x, int y, t_data *data);
void		update_object_position(t_object *obj, t_keys *keys);
int			loop_hook(t_data *data);
void		reset_keys(t_keys *keys);

// // Fonction de débogage
// void		debug_print_scene(t_data *data);
// void		debug_print_object(const t_object *obj);
// void		print_rays(t_data *data);

//render
void		render(t_data *data, t_ray *ray, int x, int y);
double		get_intersection_distance(t_object *object, t_ray *ray, int code);

//lightning
t_color		get_pixel_lighting(t_data *data, t_object *object, t_vector intersection);
t_vector	get_closest_cap_normal(t_cylinder *cylinder, t_object *object, t_vector intersection);
int			get_shadow_factor(t_data *data, t_vector intersection, t_light *light);
double		get_light_distance(t_vector a, t_vector b);
t_color		get_ambient_light(t_ambient ambient, t_color object_color);
void		init_lighting(t_shadow *parts, t_data *data, t_object *object, t_vector intersection);
void		add_color(t_shadow *parts);


//Raytracing
int			raytracing(t_data *data);

//Intersection calculation
double		sphere_intersection(t_sphere *sphere, t_ray *ray, t_object *current, int code);
double		cylinder_intersection(t_cylinder *cylinder, t_ray *ray, t_object *current, int code);
double		plane_intersection(t_plane *plane, t_ray *ray, t_vector *pos);
double		return_high_or_low(t_inter inter, int code);
double		cone_intersection(t_cone *cone, t_ray *ray, t_object *current, int code);
double		plane_disk_intersection(t_object *object, t_inter *inter, t_ray *ray, int code);
double		c_return_high_or_low(t_inter *inter, int code);

//Checkerboard
t_color		apply_checkerboard_pattern(t_object *object, t_vector intersection);
t_color		apply_smooth_checkerboard_to_plane(t_vector inter, t_checker *checker);
t_color		apply_checkerboard_to_vertical_plane(t_vector inter, t_checker *checker);
t_color		apply_checkerboard_to_sphere(t_object *object, t_vector inter, t_checker *checker);
t_color		apply_checkerboard_to_cylinder(t_object *object, t_vector inter, t_checker *checker);
t_color		apply_checkerboard_to_cone(t_object *object, t_vector inter, t_checker *checker);

//Minilibx
void		init_mlx_image(t_data *data);
int			rgb_to_int(t_color color);
void		ft_mlx_pixel_put(t_img *img, int x, int y, int color);

//events
void		apply_movement_to_camera(int key_code, t_data *data);
void		apply_rotation_to_camera(int key_code, t_data *data);
void		update_draw(t_data *data);

//vector_utils
t_vector	vector_cross(t_vector a, t_vector b);
t_vector	get_oc_vector(t_vector *ray_origin, t_vector *object_center);
t_vector	mul(t_vector a, double b);
t_vector	sub(t_vector a, t_vector b);
t_vector	add(t_vector a, t_vector b);
void		normalize_vector(t_vector *v);
double		square(double x);
double		get_scalar_product(const t_vector *a, const t_vector *b);
double		get_delta(t_inter *inter);

//perlin
void		perturb_normal(t_vector *normal, t_object *object, t_vector intersection);
double		perlin(double x, double y);

//noise
double		generate_smooth_noise(int x, int y);
double		generate_2d_noise(int x, int y);
double		generate_random_noise(int t);

#endif
