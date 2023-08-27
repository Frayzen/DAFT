#include "../../include/acceleration/lod.h"

void printMat4(Matrix4 m){
    printf("%f %f %f %f\n", m.r1[0], m.r1[1], m.r1[2], m.r1[3]);
    printf("%f %f %f %f\n", m.r2[0], m.r2[1], m.r2[2], m.r2[3]);
    printf("%f %f %f %f\n", m.r3[0], m.r3[1], m.r3[2], m.r3[3]);
    printf("%f %f %f %f\n", m.r4[0], m.r4[1], m.r4[2], m.r4[3]);
}

Vector4 getPlaneEquation(Mesh* m, int triId){
    Triangle tri = m->triangles[triId];
    Vector3 p1 = m->vertices[tri.vs.x];
    Vector3 p2 = m->vertices[tri.vs.y];
    Vector3 p3 = m->vertices[tri.vs.z];
    Vector3 e1 = sub(p2, p1);
    Vector3 e2 = sub(p3, p1);
    Vector3 normal = normalize(cross(e1, e2));
    float d = -dot(normal, p1);
    Vector4 result = {normal.x, normal.y, normal.z, d};
    return result;
}

SymmetricMatrix4 computeKp(Mesh* m, int tri){
    Vector4 plane = getPlaneEquation(m, tri);
    float a = plane.x;
    float b = plane.y;
    float c = plane.z;
    float d = plane.w;
    SymmetricMatrix4 result = {
        a * a, a * b, a * c, a * d,
        b * b, b * c, b * d,
        c * c, c * d,
        d * d
    };
    return result;
}

void addSymToMat(Matrix4* m, SymmetricMatrix4* s){
    //r1
    m->r1[0] += s->r1[0];
    m->r1[1] += s->r1[1];
    m->r1[2] += s->r1[2];
    m->r1[3] += s->r1[3];
    //r2
    m->r2[0] += s->r1[1];
    m->r2[1] += s->r2[0];
    m->r2[2] += s->r2[1];
    m->r2[3] += s->r2[2];
    //r3
    m->r3[0] += s->r1[2];
    m->r3[1] += s->r2[1];
    m->r3[2] += s->r3[0];
    m->r3[3] += s->r3[1];
    //r4
    m->r4[0] += s->r1[3];
    m->r4[1] += s->r2[2];
    m->r4[2] += s->r3[1];
    m->r4[3] += s->r4[0];
}

Matrix4 addMatToMat(Matrix4 m1, Matrix4 m2){
    Matrix4 result = {
        m1.r1[0] + m2.r1[0], m1.r1[1] + m2.r1[1], m1.r1[2] + m2.r1[2], m1.r1[3] + m2.r1[3],
        m1.r2[0] + m2.r2[0], m1.r2[1] + m2.r2[1], m1.r2[2] + m2.r2[2], m1.r2[3] + m2.r2[3],
        m1.r3[0] + m2.r3[0], m1.r3[1] + m2.r3[1], m1.r3[2] + m2.r3[2], m1.r3[3] + m2.r3[3],
        m1.r4[0] + m2.r4[0], m1.r4[1] + m2.r4[1], m1.r4[2] + m2.r4[2], m1.r4[3] + m2.r4[3]
    };
    return result;
}

Edge* addEdgeIfNotExist(int i, int j, Edge* e){
    Edge* current = e;
    while(current != NULL){
        if((current->v1 == i && current->v2 == j) || (current->v1 == j && current->v2 == i)){
            return e;
        }
        current = current->next;
    }
    Edge* newEdge = calloc(sizeof(Edge), 1);
    newEdge->v1 = i;
    newEdge->v2 = j;
    newEdge->cost = 0;
    newEdge->next = NULL;
    if(e == NULL)
        newEdge->next = NULL;
    else
        newEdge->next = e;
    return newEdge;
}

Edge* appendToEdgeList(Edge* e, Edge* newEdge){
    newEdge->next = NULL;
    if(e == NULL){
        return newEdge;
    }
    if(e->cost > newEdge->cost){
        newEdge->next = e;
        return newEdge;
    }
    Edge* current = e;
    while(current->next != NULL){
        if(current->next->cost > newEdge->cost){
            newEdge->next = current->next;
            current->next = newEdge;
            return e;
        }
        current = current->next;
    }
    current->next = newEdge;
    return e;
}

Edge* computeEdgesCost(Mesh* mesh, Edge* e, Matrix4* Qs){
    Edge* r = NULL;
    Edge* current = e;
    while(current != NULL){
        Edge* next = current->next;
        Vector3 v1 = mesh->vertices[current->v1];
        Vector3 v2 = mesh->vertices[current->v2];
        Matrix4 Q = addMatToMat(Qs[current->v1], Qs[current->v2]);
        Matrix4 savedQ = Q;
        Q.r4[0] = 0;
        Q.r4[1] = 0;
        Q.r4[2] = 0;
        Q.r4[3] = 1;
        Matrix4 Qinv;
        Vector4 newPoint;
        if(inverseMat4(&Q, &Qinv)){
            newPoint = multiplyMatrixVector4(Qinv, (Vector4){0,0,0,1});
            current->newPoint = (Vector3){newPoint.x, newPoint.y, newPoint.z};
        }else{
            current->newPoint = midPoint(v1, v2);
            newPoint = (Vector4){current->newPoint.x, current->newPoint.y, current->newPoint.z, 1};
        }
        //hesitate between these two lines
        current->cost = dot4(newPoint, multiplyMatrixVectTranspose4(savedQ, newPoint));
        //current->cost = dot4(newPoint, multiplyMatrixVector4(savedQ, newPoint));
        r = appendToEdgeList(r, current);
        current = next;  
    }
    return r;
}

Edge* removeUnmergeable(Mesh* mesh, Edge* edges){
    Edge* current = edges;
    Edge* prev = NULL;
    Edge* ret = edges;
    while(current != NULL){
        Edge* next = current->next;
        Vector3 v1 = mesh->vertices[current->v1];
        Vector3 v2 = mesh->vertices[current->v2];
        int found = 0;
        int joint[mesh->vertexCount];
        for (int i = 0; i < mesh->triangleCount; i++)
        {
            Triangle tri = mesh->triangles[i];
            if(tri.vs.x == current->v1 || tri.vs.y == current->v1 || tri.vs.z == current->v1){
                joint[tri.vs.x] = 1;
                joint[tri.vs.y] = 1;
                joint[tri.vs.z] = 1;
            }
        }
        joint[current->v1] = 0;
        joint[current->v2] = 0;
        for (int i = 0; i < mesh->triangleCount; i++)
        {
            Triangle tri = mesh->triangles[i];
            if(tri.vs.x == current->v2 || tri.vs.y == current->v2 || tri.vs.z == current->v2){
                if(joint[tri.vs.x] == 1 || joint[tri.vs.y] == 1 || joint[tri.vs.z] == 1){
                    found++;
                    if(found == 2)
                        break;
                }
            }
        }
        if(found == 2){
            if(prev == NULL)
                ret = current;
            else{
                prev->next = current->next;
                free(current);
                current = NULL;
            }
        }
        //TODO geometry check (for normals)     
        prev = current;
        current = next;
    }
    return ret;
}

int isInside(Vector3 max, Vector3 min, Vector3 point){
    return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
}
int replaceInTri(Triangle* t, int from, int to){
    if(t->vs.x == from){
        t->vs.x = to;
        return 1;
    }
    if(t->vs.y == from){
        t->vs.y = to;
        return 1;
    }
    if(t->vs.z == from){
        t->vs.z = to;
        return 1;
    }
    return 0;
}

void removeTrianglesWithEdge(Mesh* mesh, int cur, int v1, int v2){
    int2 children = mesh->children[cur];
    if(children.x < 0){
        int triId = -(children.x+1);
        Triangle tri = mesh->triangles[triId];
        if(tri.vs.x == v1 || tri.vs.y == v1 || tri.vs.z == v1){
            if(tri.vs.x == v2 || tri.vs.y == v2 || tri.vs.z == v2)
                mesh->children[cur].x = 0;
            else
                replaceInTri(&tri, v1, v2);
        }
    }else if(children.x > 0 && isInside(mesh->maxBbox[children.x], mesh->minBbox[children.x], mesh->vertices[v1])){
        removeTrianglesWithEdge(mesh, children.x, v1, v2);
    }
    if(children.y < 0){
        int triId = -(children.y+1);
        Triangle tri = mesh->triangles[triId];
        if(tri.vs.x == v1 || tri.vs.y == v1 || tri.vs.z == v1){
            if(tri.vs.x == v2 || tri.vs.y == v2 || tri.vs.z == v2)
                mesh->children[cur].y = 0;
        }
    }else if(children.y > 0 && isInside(mesh->maxBbox[children.y], mesh->minBbox[children.y], mesh->vertices[v1])){
        removeTrianglesWithEdge(mesh, children.y, v1, v2);
    }
}

void mergeEdges(Mesh* mesh, Edge* edges){
    Edge e = *edges;
    Vector3 newPoint = e.newPoint;
    int v1 = e.v1;
    int v2 = e.v2;
    removeTrianglesWithEdge(mesh, v1, v2, 0);
    mesh->vertices[v1] = newPoint;
    mesh->vertices[v2] = newPoint;
    rebuildBbox(mesh);
}

int _countBBox(Mesh* m, int cur){
    if(cur <= 0)
        return 1;
    return 1 + _countBBox(m, m->children[cur].x) + _countBBox(m, m->children[cur].y);
}
int countBBox(Mesh* m){
    return 1+_countBBox(m, m->children[0].x)+_countBBox(m, m->children[0].y);
}

void simplifyMesh(Mesh* mesh){
    SymmetricMatrix4* Kps = malloc(mesh->triangleCount * sizeof(SymmetricMatrix4));
    for(int i = 0; i < mesh->triangleCount; i++){
        Kps[i] = computeKp(mesh, i);
    }
    Matrix4 Qs[mesh->vertexCount];
    memset(Qs, 0, sizeof(Matrix4) * mesh->vertexCount);
    Edge* tempEdges = NULL;
    for (int i = 0; i < mesh->triangleCount; i++)
    {
        addSymToMat(&Qs[mesh->triangles[i].vs.x], &Kps[i]);
        addSymToMat(&Qs[mesh->triangles[i].vs.y], &Kps[i]);
        addSymToMat(&Qs[mesh->triangles[i].vs.z], &Kps[i]); 
        tempEdges = addEdgeIfNotExist(mesh->triangles[i].vs.x, mesh->triangles[i].vs.y, tempEdges);
        tempEdges = addEdgeIfNotExist(mesh->triangles[i].vs.y, mesh->triangles[i].vs.z, tempEdges);
        tempEdges = addEdgeIfNotExist(mesh->triangles[i].vs.z, mesh->triangles[i].vs.x, tempEdges);
    }
    free(Kps);
    if(LOD_THRESHOLD > 0)
        for (int i = 0; i < mesh->vertexCount; i++)
        {
            Vector3 v = mesh->vertices[i];
            for (int j = i+1; j < mesh->vertexCount; j++)
            {
                Vector3 v2 = mesh->vertices[j];
                if(dist(v,v2) < LOD_THRESHOLD)
                    addEdgeIfNotExist(i, j, tempEdges);
            }     
        }
    Edge* edges = computeEdgesCost(mesh, tempEdges, Qs);

    removeUnmergeable(mesh, edges);
    int count = 0;
    Edge* current = edges;
    while(current != NULL){
        count++;
        //printf("%f | ", current->cost);
        current = current->next;
    }
    printf("First edge points: %f %f %f | %f %f %f\n", mesh->vertices[edges->v1].x, mesh->vertices[edges->v1].y, mesh->vertices[edges->v1].z, mesh->vertices[edges->v2].x, mesh->vertices[edges->v2].y, mesh->vertices[edges->v2].z);
    printf("Merges to point: %f %f %f\n", edges->newPoint.x, edges->newPoint.y, edges->newPoint.z);
    printf("\n %d edges mergeable\n", count);
    printf("\n %d bbox before\n", countBBox(mesh));
    current = edges;
    for (int i = 0; i < 400; i++)
    {
        mergeEdges(mesh, current);
        current = current->next;
    }
    printf("\n %d bbox after\n", countBBox(mesh));
    

}