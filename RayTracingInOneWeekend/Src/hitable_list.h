#ifndef HITABLE_LIST_H  
#define HITABLE_LIST_H  
  
#include "hitable.h" 

class hitable_list:public hitable
{
public:
    hitable **list; // array of pointers to hitables
    int list_size;
public: 
    hitable_list(){}
    hitable_list(hitable ** l, int n) 
    {
        list = l;
        list_size = n;
    }

	// return whether the Ray hit the hitable for  tmin < t < tmax, store hit data (eg color) in hit record 'rec'
    virtual bool hit(const Ray & r, float tmin, float tmax, hit_record & rec ) const;
};

#endif // HITABLE_LIST_H  