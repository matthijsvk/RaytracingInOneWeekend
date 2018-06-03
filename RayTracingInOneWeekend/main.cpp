#include "stdafx.h"
#include "svpng.inc"
#include "ray.h"
#include <iostream>

#define W 600
#define H 300

/* shere equation at origin:	R^2 = x^2 + y^2 + z^2
with center C = (cx,cy,cz):		R^2 = (x-cx)^2 + (y-cy)^2 + (z-cz)^2
in vector form, p=(x,y,z):		R^2 = dot( p - C , p - C )
ray equation:					P = A + t * B
intersection:					R^2 = dot( (A + t B - C) , (A + t B - C) )
								dot(B,B) t ^ 2 + 2 dot( B , A-C ) * t + dot(A-C,A-C) - R^2 = 0
	this is a quadratic equation in T -> solutions (intersection, edge intersection, no intersection)

*/

float hit_sphere(const Vec3& center, float radius, const Ray& r)
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0 * dot(oc, r.Direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b*b - 4*a*c;
	if (discriminant < 0.0) {
		return -1.0;
	}
	else {
		return (-b + sqrt(discriminant)) / (2.0 * a);
	}
 }

Vec3 color(const Ray& r)
{
	Vec3 sphere_center = Vec3(0, 0, -1);
	float t = hit_sphere(sphere_center, 0.5, r);
	Vec3 hit_point = r.point_at_parameter(t);
	// color red if top of shere hit, else normal background color (blue to white from top to bottom)
    if (t > 0.0)
    {
		// we have a hit
		// get normal = hit_point to sphere_center
		//convert normal direction to color for visualization
		Vec3 N = unit_vector(hit_point - sphere_center);
		return 0.5 * Vec3(N.x() + 1, N.y() + 1, N.z() + 1); 
    }
        
	// convert ray direction to [-1,1]
    Vec3 unit_direction = unit_vector(r.Direction());
	// scale to [0,1]
    t = 0.5 * (unit_direction.y() + 1.0) ;

	// fill in with background colors
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

unsigned char img[W * H * 3];

int main(){

    unsigned char* p = img;

    Vec3 lower_left_corner(-2.0 , -1.0 , - 1.0 );
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0,2.0,0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    for (int j = H-1; j >=0 ; j--){
        for (int i = 0; i < W; i++,p += 3)
        {
            float u = float(i) / float(W);
            float v = float(j) / float(H);
            Ray r(origin, lower_left_corner + u* horizontal + v * vertical);

            Vec3 col = color(r);
            
            p[0] = int(255.99*col[0]);
            p[1] = int(255.99*col[1]);
            p[2] = int(255.99*col[2]);

        }
    }
	
    svpng(fopen("bg.png", "wb"), W, H, img, 0);
    std::cout << "finished" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
}
