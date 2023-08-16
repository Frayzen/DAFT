#include "../../include/preprocessing/obj_parser.h"

int countVerticesInFaceLine(char* line){
    int count = 2;
    int lastSpace = 1;
    int nbvertices = 0;
    while(line[count] != '\n' && line[count] != '\0'){
        if(line[count] == ' '){
            lastSpace = 1;
        }else{
            if(lastSpace == 1){
                nbvertices++;
            }
            lastSpace = 0;
        }
        count++;
    }
    return nbvertices;
}
void countObjLine(char* line, void* data){
    Mesh* m = (Mesh*)data;
    if(line[0] == 'v'){
        if(line[1] == ' '){
            m->vertexCount++;
        }else if(line[1] == 'n'){
            m->normalCount++;
        }else if(line[1] == 't'){
            m->uvCount++;
        }
    }else if(line[0] == 'f'){
        m->triangleCount+= countVerticesInFaceLine(line) - 2;
    }
}
void parseFaceLine(char* line, Mesh* m) {
    int nbvertices = countVerticesInFaceLine(line);
    int count = 1;
    int vs[nbvertices];
    int ns[nbvertices];
    int us[nbvertices];
    int res, sum;
    for (int i = 0; i < nbvertices; i++){
        us[i] = 0;
        ns[i] = 0;
        res = sscanf(line + count, " %d%n", &vs[i], &sum);
        assert(res == 1);
        count+=sum;
        if(line[count] == '/'){
            res = sscanf(line + count, "/ %d%n", &us[i], &sum);
            count+=sum;
        }
        if(line[count] == '/'){
            res = sscanf(line + count, "/ %d%n", &ns[i], &sum);
            assert(res == 1);
            count+=sum;
        }
        if(i > 1){
            Triangle tri = m->triangles[m->triangleCount];
            tri.vs = (int3){vs[0] - 1, vs[i - 1] - 1, vs[i] - 1}; 
            tri.ts = (int3){us[0] - 1, us[i - 1] - 1, us[i] - 1};
            tri.ns = (int3){ns[0] - 1, ns[i - 1] - 1, ns[i] - 1};
            m->triangles[m->triangleCount] = tri;
            m->triangleCount++;
        }
        count++;
    }
}

void postParseObjLine(char* line, void* data){
    Mesh* m = (Mesh*)data;
    if (line[0] == 'v')
    {
        if (line[1] == ' ')
        {
            sscanf(line, "v %f %f %f", &m->vertices[m->vertexCount].x, &m->vertices[m->vertexCount].y, &m->vertices[m->vertexCount].z);
            m->vertexCount++;
        }
        else if (line[1] == 'n')
        {
            sscanf(line, "vn %f %f %f", &m->normals[m->normalCount].x, &m->normals[m->normalCount].y, &m->normals[m->normalCount].z);
            m->normalCount++;
        }
        else if (line[1] == 't')
        {
            sscanf(line, "vt %f %f", &m->uvs[m->uvCount].x, &m->uvs[m->uvCount].y);
            m->uvCount++;
        }
    }
    else if (line[0] == 'f')
    {
        parseFaceLine(line, m);
    }
}

void clearCounts(Mesh* m){
    m->vertexCount = 0;
    m->normalCount = 0;
    m->uvCount = 0;
    m->triangleCount = 0;
}

void checkMesh(Mesh* m){
    assert(m->vertexCount > 0);
    assert(m->triangleCount > 0);
    for (int i = 0; i < m->triangleCount; i++)
    {
        assert(m->triangles->vs.x < m->vertexCount && m->triangles->vs.y < m->vertexCount && m->triangles->vs.z < m->vertexCount);
        assert(m->triangles->ns.x < m->normalCount && m->triangles->ns.y < m->normalCount && m->triangles->ns.z < m->normalCount);
        assert(m->triangles->ts.x < m->uvCount && m->triangles->ts.y < m->uvCount && m->triangles->ts.z < m->uvCount);
    }
}

void parseObjFile(char* path, Mesh* m, Transform* transform){
    clearMesh(m);
    clearCounts(m);
    parseFile(path, &countObjLine, m);
    m->vertices = malloc(sizeof(Vector3) * m->vertexCount);
    m->normals = malloc(sizeof(Vector3) * m->normalCount);
    m->uvs = malloc(sizeof(Vector3) * m->uvCount);
    m->triangles = malloc(sizeof(Triangle) * m->triangleCount);
    clearCounts(m);
    parseFile(path, &postParseObjLine, m);
    for (int i = 0; i < m->vertexCount; i++)
    {
        m->vertices[i] = transformVector3(m->vertices[i], transform);
    }
    checkMesh(m);
}