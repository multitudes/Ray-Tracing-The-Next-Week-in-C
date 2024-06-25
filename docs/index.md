I am following the tutorials in [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) but writing the code in C for good practice.  

These are my notes from the book and what I learned in the process.


## Raytracing
At its core, a ray tracer sends rays through pixels and computes the color seen in the direction of those rays. The involved steps are

- Calculate the ray from the “eye” through the pixel,
- Determine which objects the ray intersects, and
- Compute a color for the closest intersection point.

## aspect ratio
A 16∶9 aspect ratio means that the ratio of image width to image height is 16∶9.  
For a practical example, an image 800 pixels wide by 400 pixels high has a 2∶1 aspect ratio. 

## the output image
The book writes the image to a file in the PPM format. The PPM format is a text-based format that starts with a header that describes the image size and color depth. The header is followed by the pixel data, which is written as a series of RGB triplets. 
ex:
```
P3
800 450
255
220 234 255
220 234 255

```
In the above example P3 is just a magic number and has no connection with the display color depth. The next line is the image size, 800 pixels wide by 450 pixels high. The last line is the color depth, 8 bits in this case but can be seen as the is the maximum value for each color. Everything after that is the image data: RGB triplets.  
https://en.wikipedia.org/wiki/Netpbm 


## The Viewport
The viewport is a virtual rectangle in the 3D world that contains the grid of image pixel locations. If pixels are spaced the same distance horizontally as they are vertically, the viewport that bounds them will have the same aspect ratio as the rendered image. The distance between two adjacent pixels is called the pixel spacing, and square pixels is the standard. 
We'll initially set the distance between the viewport and the camera center point to be one unit. This distance is often referred to as the focal length.  
While our 3D space has the conventions above, this conflicts with our image coordinates, where we want to have the zeroth pixel in the top-left and work our way down to the last pixel at the bottom right. This means that our image coordinate Y-axis is inverted: Y increases going down the image. 
 We'll also have the y-axis go up, the x-axis to the right, and the negative z-axis pointing in the viewing direction. (This is commonly referred to as right-handed coordinates.)

## Ray-Sphere Intersection

The equation for a sphere of radius r that is centered at the origin is an important mathematical equation: 

$$
x^2 + y^2 + z^2 = r^2
$$

If a given point (x,y,z) is inside the sphere, then $x^2 + y^2 + z^2 < r^2$ , and if a given point (x,y,z) is outside the sphere, then $x^2 + y^2 + z^2 > r^2$.

If we want to allow the sphere center to be at an arbitrary point (Cx,Cy,Cz) in 3D, then the equation becomes:  
$$
(Cx−x)^2 + (Cy−y)^2 + (Cz−z)^2 = r^2
$$

This formula looks very similar to the definition of a dot product of a vector from point P = (x,y,z) to a center C = (Cx,Cy,Cz) which is (C-P).

The dot product of this vector with itself is:  

$$
(C−P)⋅(C−P)=(Cx−x)^2+(Cy−y)^2+(Cz−z)^2 = r ^ 2
$$ 

We can read this as “any point P that satisfies this equation is on the sphere”.  

Remember that on our ray P is a function of t, so we can substitute P = Q + td into the equation and solve for t. (Q is the origin of the ray, and d is the direction of the ray.)

The only unknown is t, and we have a $t^2$, which means that this equation is quadratic. 
You can solve for a quadratic equation $ax^2+bx+c=0$ by using the quadratic formula:

$$
x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

So solving for t in the ray-sphere intersection equation gives us these values for a, b, and c:
$$
a=d⋅d
b=−2d⋅(C−Q)
c=(C−Q)⋅(C−Q)−r2
$$

where Q is the origin of the ray, d is the direction of the ray, C is the center of the sphere, and r is the radius of the sphere.

Really we just need to know if the square root also called the discriminant is real and positive. If it is, then the ray intersects the sphere at two points. If it is zero, then the ray is tangent to the sphere. If it is negative, then the ray misses the sphere entirely.

$$
\sqrt{b^2 - 4ac}
$$

In code:
```c
bool hit_sphere(const t_sphere *s, const t_ray *r) 
{
    t_vec3 cq = vec3substr(s->center, r->orig);
    double a = dot(&(r->dir), &(r->dir));
    double b = -2.0 * dot(&(r->dir), &cq);
    double c = dot(&cq, &cq) - s->radius * s->radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
```

# Which side of the sphere are we on?
We need to choose to determine the side of the surface at the time of geometry intersection or at the time of coloring.
This is a boolean determined with the dot product
```
bool front_face;
if (dot(ray_direction, outward_normal) > 0.0) {
    // ray is inside the sphere
    normal = -outward_normal;
    front_face = false;
} else {
    // ray is outside the sphere
    normal = outward_normal;
    front_face = true;
}
```

## an array of shapes in C? How!?
Thanks to this course I discovered that you can have polymorphic behavior in C. 
It is a bit weird at first but totally doable.  

I have a struct, t_hittable that has a function pointer to a hit function.  

To create an array of different shapes (like spheres and cubes) that all implement the [`hittable`]interface or behaviour, I define a struct `t_hittable` that contains a function pointer for the `hit` function:

```c
typedef struct s_hittable {
    bool (*hit)(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec);
} t_hittable;
```

Then, for each shape (like a sphere or a cube), you create a struct that includes the `t_hittable` struct as its first member:

```c
typedef struct {
    t_hittable base;
    t_point3 center;
    double radius;
} sphere;

typedef struct {
    t_hittable base;
    t_point3 min;
    t_point3 max;
} cube;
```
This is very important: the `hittable` struct must be the first member of the shape structs. This is because the C standard guarantees that the address of the first member of a struct is the same as the address of the struct itself. This allows you to cast a pointer to a `sphere` or `cube` to a `hittable` pointer and back without any issues.

You can then define the `hit` functions for each shape:

```c
bool hit_sphere(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec) {
    // implementation...
}

bool hit_cube(const void* self, const t_ray* r, double t_min, double t_max, t_hit_record* rec) {
    // implementation...
}
```

The functions all take a `const void* self` parameter, which is a pointer to the shape struct. This allows you to cast the pointer to the appropriate shape struct inside the function.

When you create a new shape, you set the `hit` function pointer in the `hittable` struct to the appropriate function:

```c
sphere* new_sphere(t_point3 center, double radius) {
    sphere* s = malloc(sizeof(sphere));
    s->base.hit = hit_sphere;
    s->center = center;
    s->radius = radius;
    return s;
}

cube* new_cube(t_point3 min, t_point3 max) {
    cube* c = malloc(sizeof(cube));
    c->base.hit = hit_cube;
    c->min = min;
    c->max = max;
    return c;
}
```

Finally, you can create an array of `t_hittable` pointers and add your shapes to it:

```c
hittable* shapes[10];
shapes[0] = (hittable*)new_sphere(center1, radius1);
shapes[1] = (hittable*)new_cube(min1, max1);
// etc...
```

To check if a ray hits any of the shapes, you can loop over the array and call the `hit` function through the function pointer:

```c
for (int i = 0; i < 10; i++) {
    if (shapes[i]->hit(shapes[i], r, t_min, t_max, &rec)) {
        // hit
    }
}
```

## The Camera

## Extras - the compile_commands.json file
If using nvim the LSP will ask for a compile_commands.json file. This file is can be generated by the compiledb tool. 
```
make clean && make > build.log
compiledb -n < build.log      
```

## links
- [Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
- [Raytracing the next week](https://raytracing.github.io/books/RayTracingTheNextWeek.html)  
- [Raytracing the rest of your life](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)  

- [MLX42](https://github.com/codam-coding-college/MLX42)  
- stb_image.h, a header-only image library available on GitHub at https://github.com/nothings/stb.
- [https://gabrielgambetta.com/computer-graphics-from-scratch/](https://gabrielgambetta.com/computer-graphics-from-scratch/)  
- A raytracer on the back of a business card. [https://fabiensanglard.net/rayTracing_back_of_business_card/](https://fabiensanglard.net/rayTracing_back_of_business_card/)

here are a few really good resources by [Fabien Sanglard](https://fabiensanglard.net/about/index.html):

scratchapixel.com : Great raytracer lessons written by professionals that have worked on Toy Story, Avatar, Lord of the Rings, Harry Potter, Pirates of the Caribbean and many other movies.
An Introduction to Ray Tracing : An old book but a Classic.
Physically Based Rendering : Heavy on maths but really good and well explained.
