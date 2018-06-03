#include "svpng.inc"
#include <iostream>

#include "sphere.h"  
#include "hitable_list.h"
#include <float.h> 

#define W 2560
#define H 1440

/* shere equation at origin:	R^2 = x^2 + y^2 + z^2
with center C = (cx,cy,cz):		R^2 = (x-cx)^2 + (y-cy)^2 + (z-cz)^2
in vector form, p=(x,y,z):		R^2 = dot( p - C , p - C )
ray equation:					P = A + t * B
intersection:					R^2 = dot( (A + t B - C) , (A + t B - C) )
								dot(B,B) t ^ 2 + 2 dot( B , A-C ) * t + dot(A-C,A-C) - R^2 = 0
	this is a quadratic equation in T -> solutions (intersection, edge intersection, no intersection)

*/

Vec3 color(const Ray& r, hitable* world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);//white, light blue
	}
}

unsigned char img[W * H * 3];

int main(){

    unsigned char* p = img;

    Vec3 lower_left_corner(-2.0 , -1.0 , - 1.0 );
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0,2.0,0.0);
    Vec3 origin(0.0, 0.0, 0.0);

	hitable *list[2];
	list[0] = new sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new sphere(Vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

    for (int j = H-1; j >=0 ; j--){
        for (int i = 0; i < W; i++,p += 3)
        {
            float u = float(i) / float(W);
            float v = float(j) / float(H);
            Ray r(origin, lower_left_corner + u* horizontal + v * vertical);

            Vec3 col = color(r, world); // intersect the ray with the world
            
            p[0] = int(255.99*col[0]);
            p[1] = int(255.99*col[1]);
            p[2] = int(255.99*col[2]);
        }
    }
	
    svpng(fopen("out.png", "wb"), W, H, img, 0);
    std::cout << "finished" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
}
