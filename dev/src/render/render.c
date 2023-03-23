

//TODO: make this file

// FOV is in degrees
ray get_ray(int width, int height, int x_pix, int y_pix, float FOV, float orientation[2]){
    float yaw = orientation[0];
    //float pitch = orientation[1];
    float FOV = FOV*M_PI/180;
    float hFOV = FOV/2;
    float pitch_ratio = (float)y_pix/(height-1);
    float yaw_ratio = (float)x_pix/(width-1);
    float deg1 = yaw+hFOV;
    float deg2 = yaw-hFOV;
    float p1[3] = npoint(cos(deg1), 0, sin(deg1));
    float p2[3] = npoint(cos(deg2), 0, sin(deg2));
    float flat = minus(p2, p1);
    float xz[3] = add(p1, scale(flat, yaw_ratio));

    deg1 = hFOV;
    p1 = npoint(0, cos(deg1), 0);
    p2 = scale(p1, -1);
    flat = minus(p2, p1);
    point y = add(p1, scale(flat, pitch_ratio));
    point dir = add(xz, y);
    ray ry;
    ry.pos = cam->pos;
    ry.dir = dir;
    ry.hit = 0;
    ry.mint = -1;
    ry.computed = 1;
    return ry;
}