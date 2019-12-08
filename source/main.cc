#include <iostream>
#include <fstream>
#include "hittable_list.h"
#include "sphere.h"
#include "random.h"
#include "camera.h"

using namespace std;

// -- to study --

/*

    polimosfirmo degli oggetti simile a quello in java, hittable è superclasse di sphere

*/

vec3 color(const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 500;
    int ny = 250;
    int ns = 100;


    /*
        ---- PPM HEADER ----

        the p3 meand color are in ascii, then nx columns and ny rows, then
        255 for max color. 
    */

    string ppm_header = "P3\n" + to_string(nx) + " " + to_string(ny) + "\n255\n";

    // ---- OUTPUT FILE ----
    fstream output_file;

    // open file
    output_file.open ("test.ppm", fstream::in | fstream::out | fstream::trunc);

    cout << ppm_header; 
    output_file << ppm_header;

    // ---- DATA ----
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hittable *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0-8, 0.8, 0.8), 0.4));
    hittable *world = new hittable_list(list,4);
    
    camera cam;

    for (int j=ny-1; j >=0; j--) {
        for (int i=0; i<nx; i++) {
            vec3 col(0, 0, 0);
            // antialiasing
            for (int s = 0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            // ------- end antialiasing -------

            // gamma correction, gamma = 2
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));


            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            string ppm_px = to_string(ir) + " " + to_string(ig) + " " + to_string(ib) + "\n";

            cout << ppm_px;
            output_file << ppm_px;
        }
    }

    // close file
    output_file.close();

}