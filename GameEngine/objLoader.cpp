#include "objLoader.h"




bool objLoader::getSimilarVertexIndex(PackedVertex & packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short & result)
{
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void objLoader::indexVBO(std::vector<glm::vec3>& in_vertices, std::vector<glm::vec2>& in_uvs, std::vector<glm::vec3>& in_normals, std::vector<unsigned short>& out_indices, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	for (unsigned int i = 0; i<in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

		unsigned short index;
		bool found = getSimilarVertexIndex(packed, VertexToOutIndex, index);

		if (found) { out_indices.push_back(index);}
		else { 

			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}

}

RawModel objLoader::LoadObj(char * path, Loader& loader)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<glm::vec3>  out_vertices;
	std::vector<glm::vec2>  out_uvs;
	std::vector<glm::vec3>  out_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		
	}

	while (1) {

		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; 

				 

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

	
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}

	std::vector<glm::vec3>  Final_vertices;
	std::vector<glm::vec2>  Final_uvs;
	std::vector<glm::vec3>  Final_normals;
	std::vector<unsigned short> Final_indices;
	indexVBO(out_vertices, out_uvs, out_normals, Final_indices, Final_vertices, Final_uvs, Final_normals);


	ARRAY<glm::vec3> ARvertices;
	ARvertices.arrayPointer = &Final_vertices[0];
	ARvertices.numberOfElements = Final_vertices.size();
	ARvertices.size = Final_vertices.size()*sizeof(glm::vec3);

	ARRAY<glm::vec2> ARuv;
	ARuv.arrayPointer = &Final_uvs[0];
	ARuv.numberOfElements = Final_uvs.size();
	ARuv.size = Final_uvs.size()*sizeof(glm::vec2);

	ARRAY<unsigned short> ARindex;
	ARindex.arrayPointer = &Final_indices[0];
	ARindex.numberOfElements = Final_indices.size();
	ARindex.size = Final_indices.size()*sizeof(unsigned short);

	ARRAY<glm::vec3> ARnormal;
	ARnormal.arrayPointer = &Final_normals[0];
	ARnormal.numberOfElements = Final_normals.size();
	ARnormal.size = Final_normals.size() * sizeof(glm::vec3);

	RawModel Model = loader.loadToVAO(ARvertices, ARuv, ARnormal,ARindex);


	fclose(file);
	return Model;
	
	
}



objLoader::objLoader()
{
}


objLoader::~objLoader()
{
}
