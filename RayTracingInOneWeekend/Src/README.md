Overview of the RayTracer
-------

1. `main`   
    creates objects in the world, creates camera, computes intersections of rays from camera towards a Field of View (FOV) fplane.  
    intersections with objects return which color this pixel is.  
2. `vec3`  
    3-dimensional vector, plus lots of operations  
3. `ray`  
    a ray has an origin and a direction. A parameter `t` specifies at what point along the ray we're looking  
4. `hitable`  
    an object in the world which which rays can intersect  
5. `hitable_list`  
    a list of hitables in the world. Loop through this to find all intersections rays/objects.  
    1. Sphere:  a simple sphere  
                
                - sphere equation at origin:	R^2 = x^2 + y^2 + z^2  
                - with center  C = (cx,cy,cz):	R^2 = (x-cx)^2 + (y-cy)^2 + (z-cz)^2  
                - in vector form, p=(x,y,z):	R^2 = dot( p - C , p - C )  
                - intersection:			R^2 = dot( (A + t B - C) , (A + t B - C) )  
                - expanded version:		dot(B,B) t ^ 2 + 2 dot( B , A-C ) * t + dot(A-C,A-C) - R^2 = 0  
                - this is a quadratic equation in t
				you can miss a sphere, hit it once (just at the border), or twice (pass through it)  
