/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtw_stb_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:17:08 by lbrusa            #+#    #+#             */
/*   Updated: 2024/07/04 18:50:55 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// need to include only oncd and not in the header file
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"
#include "rtw_stb_image.h"

/*
 * Initialize the image structure with default values.
 */
void init_rtw_image(t_rtw_image *img, char *filename) 
{
    img->bytes_per_pixel = 3;
    img->fdata = NULL;
    img->bdata = NULL;
    img->image_width = 0;
    img->image_height = 0;
    img->bytes_per_scanline = 0;
	// rtw_image/earthmap.jpg
	printf("filename = %s\n", filename);
	if (load(img, filename) == 0) {
		fprintf(stderr, "Failed to load image %s\n", filename);
		exit(1);
	}
	printf("Image loaded\n");
}

/*
 * Loads the linear (gamma=1) image data from the given file name. 
 * Returns true if the load succeeded. 
 * The resulting data buffer contains the three [0.0, 1.0]
 * floating-point values for the first pixel (red, then green, then blue). 
 * Pixels are contiguous, going left to right for the width of the image, 
 * followed by the next row below, for the full height of the image.
 * Load an image from a file, storing the linear floating point pixel data in the 
 * `fdata` member.
 */
int load(t_rtw_image *img, const char* filename) 
{
    int n; 
	
	if (!filename)
		return (0);
	n = img->bytes_per_pixel; // Dummy out parameter: original components per pixel
	
	// The stbi_loadf function from the stb_image.h library is used to load an image 
	// file and return the image data as floating-point values. It takes several parameters, 
	// including the filename of the image, pointers to variables that will store the image width 
	// and height, a pointer to an integer that will store the number of channels in the image, and 
	// the number of bytes per pixel.
	// The function returns a pointer to the loaded image data as an array of floating-point values. 
	// Each pixel in the image is represented by multiple floating-point values, depending on the 
	// number of channels in the image. The exact format of the returned data depends on the image 
	// file being loaded. 
	// It's important to note that the returned pointer points to dynamically allocated memory, 
	// so it's necessary to free this memory when it's no longer needed to avoid memory leaks.
    img->fdata = stbi_loadf(filename, &img->image_width, &img->image_height, &n, img->bytes_per_pixel);
    if (img->fdata == NULL) 
		return (0);
	printf("Image loaded - got fdata as array of float\n");
    img->bytes_per_scanline = img->image_width * img->bytes_per_pixel;
    convert_to_bytes(img);
    return (1);
}

/*
 * Clamp a value to a range and returns it. This is the int version
 */
int clamp_rtw(int x, int low, int high) 
{
    if (x < low) return low;
    if (x < high) return x;
    return high - 1;
}

/*
 * Convert a floating point value in the range [0.0, 1.0] 
 * to an unsigned byte value in the range [0, 255].
 */
unsigned char float_to_byte(float value) 
{
    if (value <= 0.0)
        return 0;
    if (1.0 <= value)
        return 255;
    return (unsigned char)(255.0 * value);
}

/*
 * Convert the linear floating point pixel data to bytes, 
 * storing the resulting byte data in the `bdata` member.
 */
void convert_to_bytes(t_rtw_image *img) 
{
    int total_bytes = img->image_width * img->image_height * img->bytes_per_pixel;
	printf("img width height and bytes per pixel = %d %d %d\n", img->image_width, img->image_height, img->bytes_per_pixel);
	printf("total_bytes = %d\n", total_bytes);
    img->bdata = malloc(total_bytes * sizeof(unsigned char));
	if (img->bdata == NULL) {
		fprintf(stderr, "Failed to allocate memory for image data\n");
		exit(1);
	}
	// Iterate through all pixel components, converting from [0.0, 1.0] float values to
	// unsigned [0, 255] byte values.
    unsigned char *bptr = img->bdata;
    float *fptr = img->fdata;
    for (int i = 0; i < total_bytes; i++, fptr++, bptr++)
        *bptr = float_to_byte(*fptr);
}

// Return the address of the three RGB bytes of the pixel at x,y. If there is no image
// data, returns magenta.
unsigned char *pixel_data(const t_rtw_image *img, int x, int y) 
{
    static unsigned char magenta[] = { 255, 0, 255 };
    if (img->bdata == NULL) return magenta;
	// printf(" looking up x = %d, y = %d\n", x, y);
	
	//int clamp(int x, int low, int high) 
    x = clamp_rtw(x, 0, img->image_width);
    y = clamp_rtw(y, 0, img->image_height);
	// values should be mostly the same
	// printf("x = %d, y = %d ===============\n", x, y);
    return img->bdata + y * img->bytes_per_scanline + x * img->bytes_per_pixel;
}

int width(const t_rtw_image *img) 
{
    return (img->fdata == NULL) ? 0 : img->image_width;
}

int height(const t_rtw_image *img) 
{
    return (img->fdata == NULL) ? 0 : img->image_height;
}

void free_rtw_image(t_rtw_image *img) {
    if (img->fdata) {
        stbi_image_free(img->fdata);
        img->fdata = NULL;
    }
    if (img->bdata) {
        free(img->bdata);
        img->bdata = NULL;
    }
}