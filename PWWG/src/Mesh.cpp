#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> Vertices, std::vector<GLuint> Indices, std::vector<Texture> Textures, std::vector<Texture> GammaCorrectedTextures)
	:vertices(Vertices), indices(Indices), textures(Textures), gammaCorrectedTextures(GammaCorrectedTextures)
{
	GLuint VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
	glEnableVertexAttribArray(3);

	glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIds));
	glEnableVertexAttribArray(4);

	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
	glEnableVertexAttribArray(5);

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader, bool gammaCorrected)
{
	switch (gammaCorrected) 
	{
		case true:
			for (int i = 0; i < gammaCorrectedTextures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				shader.SetInt("material." + gammaCorrectedTextures[i].type, i);

				glBindTexture(GL_TEXTURE_2D, gammaCorrectedTextures[i].ID);
			}
			break;
		case false:
			for (int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				shader.SetInt("material." + textures[i].type, i);

				glBindTexture(GL_TEXTURE_2D, textures[i].ID);
			}
			break;
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

float Mesh::CalculateCursorOffsetY()
{
	float sumOfVerticesY = 0, max = -INFINITY;

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (max < vertices[i].position.y) max = vertices[i].position.y;
		sumOfVerticesY += vertices[i].position.y;
	}

	return max - sumOfVerticesY / 2;
}

float Mesh::GetMaxPositionX()
{
	float max = -INFINITY;

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (max < vertices[i].position.x) max = vertices[i].position.x;
	}

	return max;
}

float Mesh::GetMinPositionX()
{
	float min = INFINITY;

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (min > vertices[i].position.x) min = vertices[i].position.x;
	}

	return min;
}

float Mesh::GetMaxPositionY()
{
	float max = -INFINITY;

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (max < vertices[i].position.y) max = vertices[i].position.y;
	}

	return max;
}

float Mesh::GetMinPositionY()
{
	float min = INFINITY;

	for (int i = 0; i < vertices.size(); i++) 
	{
		if (min > vertices[i].position.y) min = vertices[i].position.y;
	}

	return min;
}