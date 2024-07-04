#ifndef RTW_STB_IMAGE_H
#define RTW_STB_IMAGE_H


typedef struct		s_rtw_image 
{
	// private:
    int				bytes_per_pixel;
    float			*fdata; // Linear floating point pixel data
	unsigned char	*bdata; // Linear 8-bit pixel data
    int				image_width; // Loaded image width
    int				image_height; // Loaded image height
    int				bytes_per_scanline;
} 					rtw_image;

// Function prototypes
void			init_rtw_image(rtw_image *img, char *filename);
unsigned char	float_to_byte(float value);
void			convert_to_bytes(rtw_image *img);
unsigned char	*pixel_data(const rtw_image *img, int x, int y);
int				width(const rtw_image *img);
int				height(const rtw_image *img);
int				load(rtw_image *img, const char* filename);
int				clamp_rtw(int x, int low, int high);
void			free_rtw_image(rtw_image *img);




#endif
