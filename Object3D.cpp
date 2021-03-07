#include "Object3D.h"


Mesh* Object3D::CreateCube(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
	float half_length = length / 2;

	std::vector<glm::vec3> normals = {
										glm::vec3(-1, -1, 1), // near bottom left
										glm::vec3(1, -1, 1), // near bottom right
										glm::vec3(-1, 1, 1), // near top left
										glm::vec3(1, 1, 1), // near top right
										glm::vec3(-1, -1, -1), // far bottom left
										glm::vec3(1, -1, -1), // far bottom right
										glm::vec3(-1, 1, -1), // far top left
										glm::vec3(1, 1, -1), // far top right

										glm::vec3(0, 0, 1), // fata
										glm::vec3(1, 0, 0), // dreapta
										glm::vec3(0, 0, -1), // spate
										glm::vec3(-1, 0, 0), // stanga
										glm::vec3(0, -1, 0), // jos
										glm::vec3(0, 1, 0), // sus
									};

	std::vector<glm::vec2> textureCoords = {
										glm::vec2(0.f, 0.f), // bottom left 0
										glm::vec2(0.5f, 0.f), // bottom middle 1
										glm::vec2(1.f, 0.f), // bottom right 2
										glm::vec2(0.f, 0.5f), // middle left 3
										glm::vec2(0.5f, 0.5f), // middle middle 4
										glm::vec2(1.f, 0.5f), // middle right 5
										glm::vec2(0.f, 1.f), // top left 6
										glm::vec2(0.5f, 1.f), // top middle 7
										glm::vec2(1.f, 1.f) // top right 8
	};
	
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[8], textureCoords[1]), // fata 1 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[8], textureCoords[2]), // fata 1 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[8], textureCoords[4]), // fata 1 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[8], textureCoords[5]), // fata 1 dreapta sus

		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[9], textureCoords[4]), // fata 2 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[9], textureCoords[5]), // fata 2 dreapta jos
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[9], textureCoords[7]), // fata 2 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[9], textureCoords[8]), // fata 2 dreapta sus

		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[10], textureCoords[1]), // fata 3 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[10], textureCoords[2]), // fata 3 dreapta jos
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[10], textureCoords[4]), // fata 3 stanga sus
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[10], textureCoords[5]), // fata 3 dreapta sus

		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[11], textureCoords[4]), // fata 4 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[11], textureCoords[5]), // fata 4 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[11], textureCoords[7]), // fata 4 stanga sus
		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[11], textureCoords[8]), // fata 4 dreapta sus
		 
		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[12], textureCoords[0]), // fata 5 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[12], textureCoords[1]), // fata 5 drapta jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[12], textureCoords[3]), // fata 5 stanga sus
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[12], textureCoords[4]), // fata 5 dreapta sus

		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[13], textureCoords[3]), // fata 6 stanga jos
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[13], textureCoords[4]), // fata 6 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[13], textureCoords[6]), // fata 6 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[13], textureCoords[7]) // fata 6 dreapta sus
	};

	/*
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[0], textureCoords[1]), // fata 1 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[1], textureCoords[2]), // fata 1 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[2], textureCoords[4]), // fata 1 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[3], textureCoords[5]), // fata 1 dreapta sus

		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[1], textureCoords[4]), // fata 2 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[5], textureCoords[5]), // fata 2 dreapta jos
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[3], textureCoords[7]), // fata 2 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[7], textureCoords[8]), // fata 2 dreapta sus

		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[5], textureCoords[1]), // fata 3 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[4], textureCoords[2]), // fata 3 dreapta jos
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[7], textureCoords[4]), // fata 3 stanga sus
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[6], textureCoords[5]), // fata 3 dreapta sus

		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[4], textureCoords[4]), // fata 4 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[0], textureCoords[5]), // fata 4 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[6], textureCoords[7]), // fata 4 stanga sus
		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[2], textureCoords[8]), // fata 4 dreapta sus
		 
		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[4], textureCoords[0]), // fata 5 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[5], textureCoords[1]), // fata 5 drapta jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[0], textureCoords[3]), // fata 5 stanga sus
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[1], textureCoords[4]), // fata 5 dreapta sus

		VertexFormat(center + glm::vec3(-half_length,  half_length, half_length), color, normals[2], textureCoords[3]), // fata 6 stanga jos
		VertexFormat(center + glm::vec3(half_length,  half_length, half_length), color, normals[3], textureCoords[4]), // fata 6 dreapta jos
		VertexFormat(center + glm::vec3(-half_length,  half_length, -half_length), color, normals[6], textureCoords[6]), // fata 6 stanga sus
		VertexFormat(center + glm::vec3(half_length,  half_length, -half_length), color, normals[7], textureCoords[7]) // fata 6 dreapta sus
	};
	*/

	std::vector<unsigned short> indices = { 0, 1, 2,
											3, 2, 1,
											4, 5, 6,
											7, 6, 5,
											8, 9, 10,
											11, 10, 9,
											12, 13, 14,
											15, 14, 13,
											16, 17, 18,
											19, 18, 17,
											20, 21, 22,
											23, 22, 21 };


	Mesh* cube = new Mesh(name);

	return CreateMesh(cube, vertices, indices);
}

Mesh* Object3D::CreateSphere(std::string name, glm::vec3 center, float length, glm::vec3 color)
{
	float radius = length / 2;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	int stacks = 100, sectors = 100;
	float theta, phi;
	float theta_step = M_PI / stacks;
	float phi_step = 2 * M_PI / sectors;
	float x, y, z, nx, ny, nz;
	int i = 0, j = 0;

	for (theta = 0; theta <= M_PI + theta_step; theta += theta_step) {
		j = 0;
		for (phi = 0; phi <= 2 * M_PI + phi_step; phi += phi_step) {
			x = radius * sin(theta) * cos(phi);
			y = radius * sin(theta) * sin(phi);
			z = radius * cos(theta);
			
			nx = x / radius;
			ny = y / radius;
			nz = z / radius;
			vertices.push_back(VertexFormat(center + glm::vec3(x, y, z), color, glm::vec3(nx, ny, nz), glm::vec2((float)j / sectors, (float)i / stacks)));
			
			j++;
		}
		i++;
	}

	int triangle1_base, triangle2_base;
	for (int i = 0; i < stacks; i++) {
		triangle1_base = i * (sectors + 1);
		triangle2_base = triangle1_base + sectors + 1;

		for (int j = 0; j < sectors; j++) {
			if (i != 0) {
				indices.push_back(triangle1_base);
				indices.push_back(triangle2_base);
				indices.push_back(triangle1_base + 1);
			}

			if (i != (stacks - 1)) {
				indices.push_back(triangle1_base + 1);
				indices.push_back(triangle2_base);
				indices.push_back(triangle2_base + 1);
			}

			triangle1_base++;
			triangle2_base++;
		}
	}

	Mesh* sphere = new Mesh(name);

	return CreateMesh(sphere, vertices, indices);
}

Mesh* Object3D::CreatePyramid(std::string name, glm::vec3 center, float length, glm::vec3 color)
{
	float half_length = length / 2;

	std::vector<glm::vec3> normals = {
										glm::vec3(0, 0.5f, 1), // fata
										glm::vec3(1, 0.5f, 0), // dreapta
										glm::vec3(0, 0.5f, -1), // spate
										glm::vec3(-1, 0.5f, 0), // stanga
										glm::vec3(0, -1, 0) // jos
	};

	std::vector<glm::vec2> textureCoords = {
										glm::vec2(0.f, 0.f), // bottom left 0
										glm::vec2(0.5f, 0.f), // bottom middle 1
										glm::vec2(1.f, 0.f), // bottom right 2
										glm::vec2(0.f, 1.f), // top left 3
										glm::vec2(0.5f, 1.f), // top middle 4
										glm::vec2(1.f, 1.f) // top right 5
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[0], textureCoords[1]), // fata 1 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[0], textureCoords[5]), // fata 1 dreapta jos
		VertexFormat(center + glm::vec3(0,  half_length, 0), color, normals[0], textureCoords[4]), // fata 1 sus

		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[1], textureCoords[5]), // fata 2 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[1], textureCoords[1]), // fata 2 dreapta jos
		VertexFormat(center + glm::vec3(0,  half_length, 0), color, normals[1], textureCoords[2]), // fata 2 sus

		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[2], textureCoords[1]), // fata 3 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[2], textureCoords[5]), // fata 3 dreapta jos
		VertexFormat(center + glm::vec3(0,  half_length, 0), color, normals[2], textureCoords[4]), // fata 3 sus

		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[3], textureCoords[5]), // fata 4 stanga jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[3], textureCoords[1]), // fata 4 dreapta jos
		VertexFormat(center + glm::vec3(0,  half_length, 0), color, normals[3], textureCoords[2]), // fata 4 sus

		VertexFormat(center + glm::vec3(-half_length, -half_length,  -half_length), color, normals[4], textureCoords[0]), // fata 5 stanga jos
		VertexFormat(center + glm::vec3(half_length, -half_length, -half_length), color, normals[4], textureCoords[1]), // fata 5 dreapta jos
		VertexFormat(center + glm::vec3(-half_length, -half_length, half_length), color, normals[4], textureCoords[3]), // fata 5 stanga sus
		VertexFormat(center + glm::vec3(half_length, -half_length, half_length), color, normals[4], textureCoords[4]) // fata 5 dreapta sus
	};

	std::vector<unsigned short> indices = { 0, 1, 2,
											3, 4, 5,
											6, 7, 8,
											9, 10, 11,
											12, 13, 14,
											15, 14, 13 };


	Mesh* cube = new Mesh(name);

	return CreateMesh(cube, vertices, indices);
}

Mesh* Object3D::CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color) {
	glm::vec3 corner = bottomLeftCorner;
	std::vector<glm::vec3> normals = {
										glm::vec3(0, 0, 0), // stanga jos
										glm::vec3(1, 0, 0), // dreapta jos
										glm::vec3(0, 1, 0), // stanga sus
										glm::vec3(1, 1, 0) // dreapta sus
	};
	std::vector<glm::vec2> textureCoords = {
										glm::vec2(0, 0), // stanga jos
										glm::vec2(1, 0), // dreapta jos
										glm::vec2(0, 1), // stanga sus
										glm::vec2(1, 1) // dreapta sus
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color, normals[0], textureCoords[0]), // stanga jos
		VertexFormat(corner + glm::vec3(length, 0, 0), color, normals[1], textureCoords[1]), // dreapta jos
		VertexFormat(corner + glm::vec3(0, length, 0), color, normals[2], textureCoords[2]), // stanga sus
		VertexFormat(corner + glm::vec3(length, length, 0), color, normals[3], textureCoords[3]) // dreapta sus
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 1, 2 };

	return CreateMesh(square, vertices, indices);
}


Mesh* Object3D::CreateShield(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color) {
	glm::vec3 corner = bottomLeftCorner;
	std::vector<glm::vec3> normals = {
										glm::vec3(0, 0, 0), // stanga jos
										glm::vec3(1, 0, 0), // dreapta jos
										glm::vec3(0, 1, 0), // stanga sus
										glm::vec3(1, 1, 0) // dreapta sus
	};
	std::vector<glm::vec2> textureCoords = {
										glm::vec2(0.f, 0.f), // stanga jos
										glm::vec2(0.5f, 0), // dreapta jos
										glm::vec2(0, 1), // stanga sus
										glm::vec2(0.5f, 1), // dreapta sus
										glm::vec2(1, 0.5f)
	};

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color, normals[0], textureCoords[1]), // stanga jos 
		VertexFormat(corner + glm::vec3(length / 2, -length / 2, 0), color, normals[0], textureCoords[4]), // mijloc jos 
		VertexFormat(corner + glm::vec3(length, 0, 0), color, normals[1], textureCoords[3]), // dreapta jos 
		VertexFormat(corner + glm::vec3(0, length, 0), color, normals[2], textureCoords[0]), // stanga sus 
		VertexFormat(corner + glm::vec3(length, length, 0), color, normals[3], textureCoords[2]) // dreapta sus 
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											0, 2, 3,
											2, 4, 3
	};

	return CreateMesh(square, vertices, indices);
}

Mesh* Object3D::CreateMesh(Mesh* mesh, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	// VAO
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// IBO
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}

/*
#include "Object3D.h"


Mesh* Object3D::CreateCube(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
	float half_length = length / 2;

	std::vector<glm::vec3> vertices =
	{
		center + glm::vec3(-half_length, -half_length,  half_length),
		center + glm::vec3(-half_length, -half_length,  half_length),
		center + glm::vec3(-half_length, -half_length,  half_length),
		center + glm::vec3(-half_length, -half_length, -half_length),
		center + glm::vec3(-half_length, -half_length, -half_length),
		center + glm::vec3(-half_length, -half_length, -half_length),
		center + glm::vec3(-half_length,  half_length,  half_length),
		center + glm::vec3(-half_length,  half_length,  half_length),
		center + glm::vec3(-half_length,  half_length,  half_length),
		center + glm::vec3(-half_length,  half_length, -half_length),
		center + glm::vec3(-half_length,  half_length, -half_length),
		center + glm::vec3(-half_length,  half_length, -half_length),
		center + glm::vec3(half_length, -half_length,  half_length),
		center + glm::vec3(half_length, -half_length,  half_length),
		center + glm::vec3(half_length, -half_length,  half_length),
		center + glm::vec3(half_length, -half_length, -half_length),
		center + glm::vec3(half_length, -half_length, -half_length),
		center + glm::vec3(half_length, -half_length, -half_length),
		center + glm::vec3(half_length,  half_length,  half_length),
		center + glm::vec3(half_length,  half_length,  half_length),
		center + glm::vec3(half_length,  half_length,  half_length),
		center + glm::vec3(half_length,  half_length, -half_length),
		center + glm::vec3(half_length,  half_length, -half_length),
		center + glm::vec3(half_length,  half_length, -half_length)
	};

	std::vector<unsigned short> indices = { 0, 6, 3,
											3, 6, 9,
											7, 22, 10,
											7, 19, 22,
											5, 11, 23,
											5, 23, 17,
											18, 12, 21,
											21, 12, 15,
											1, 4, 13,
											4, 16, 13,
											8, 14, 20,
											2, 14, 8 };

	std::vector<glm::vec3> normals = {
										glm::vec3(-1, -1, 1), // near bottom left
										glm::vec3(-1, -1, -1), // far bottom left
										glm::vec3(-1, 1, 1), // near top left
										glm::vec3(-1, 1, -1), // far top left
										glm::vec3(1, -1, 1), // near bottom right
										glm::vec3(1, -1, -1), // far bottom right
										glm::vec3(1, 1, 1), // near top right
										glm::vec3(1, 1, -1), // far top right
									};

	std::vector<glm::vec2> textureCoords;

	Mesh* cube = new Mesh(name);

	if (!fill) {
		cube->SetDrawMode(GL_LINE_LOOP);
	}

	return CreateMesh(cube, vertices, normals, textureCoords, indices);
}

Mesh* Object3D::CreateSphere(std::string name, glm::vec3 center, float length, glm::vec3 color)
{
	float radius = length / 2;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;

	int stacks = 100, sectors = 100;
	float theta, phi;
	float theta_step = M_PI / stacks;
	float phi_step = 2 * M_PI / sectors;
	float x, y, z, nx, ny, nz;
	int i = 0, j = 0;

	for (theta = 0; theta <= M_PI + theta_step; theta += theta_step) {
		j = 0;
		for (phi = 0; phi <= 2 * M_PI + phi_step; phi += phi_step) {
			x = radius * sin(theta) * cos(phi);
			y = radius * sin(theta) * sin(phi);
			z = radius * cos(theta);
			vertices.push_back(center + glm::vec3(x, y, z));

			nx = x / radius;
			ny = y / radius;
			nz = z / radius;
			normals.push_back(glm::vec3(nx, ny, nz));

			textureCoords.push_back(glm::vec2(j / sectors, i / stacks));

			j++;
		}
		i++;
	}

	int triangle1_base, triangle2_base;
	for (int i = 0; i < stacks; i++) {
		triangle1_base = i * (sectors + 1);
		triangle2_base = triangle1_base + sectors + 1;

		for (int j = 0; j < sectors; j++) {
			if (i != 0) {
				indices.push_back(triangle1_base);
				indices.push_back(triangle2_base);
				indices.push_back(triangle1_base + 1);
			}

			if (i != (stacks - 1)) {
				indices.push_back(triangle1_base + 1);
				indices.push_back(triangle2_base);
				indices.push_back(triangle2_base + 1);
			}

			triangle1_base++;
			triangle2_base++;
		}
	}

	Mesh* sphere = new Mesh(name);

	return CreateMesh(sphere, vertices, normals, textureCoords, indices);
}

Mesh* Object3D::CreateSquare(std::string name, glm::vec3 bottomLeftCorner, float length, glm::vec3 color) {
	glm::vec3 corner = bottomLeftCorner;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;

	std::vector<glm::vec3> vertices =
	{
		corner, // stanga jos
		corner + glm::vec3(length, 0, 0), // dreapta jos
		corner + glm::vec3(length, length, 0),// dreapta sus
		corner + glm::vec3(0, length, 0), // stanga sus
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2 };

	return CreateMesh(square, vertices, normals, textureCoords, indices);
}

Mesh* Object3D::CreateMesh(Mesh* mesh, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<unsigned short>& indices)
{
	// VAO
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// IBO
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	mesh->InitFromData(vertices, normals, indices);

	return mesh;
}

*/