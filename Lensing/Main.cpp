#include <vector>
#include <string>
#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"

#include <stb/stb_image_write.h>

int main()
{
	unsigned int n_layers = 10;

	Window win = Window("Depth of Field", 2.5 * 512, 2.5 * 512, glm::vec4(0, 1, 1, 0));

	Shader shader = Shader();
	shader.addVertexShader("res/Lensing.vert");
	shader.addFragmentShader("res/Lensing.frag");
	shader.compileShader();

	std::vector<GLfloat> data =
	{
		//Positions		UVs
		1, 1, 0,		1, 1, //top right
		1, -1, 0,		1, 0, // bottom right
		-1, -1, 0,		0, 0, // bottom left
		-1,  1, 0,		0, 1  // top left
	};

	std::vector<GLuint> indices =
	{
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	Texture texture = Texture("res/horizontally_flipped_grid.jpg", false);
	win.clear();
	
	for(unsigned int i = 1; i <= 1; i++)
	{
		shader.bind();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		texture.bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		texture.unbind();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		shader.unbind();
	
		unsigned char* result_img = new unsigned char[win.getWidth() * win.getHeight() * 3]; //1 byte per color
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, win.getWidth(), win.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, result_img);

		stbi_flip_vertically_on_write(1); //non-zero value
		stbi_write_bmp(std::string("output/result" + std::to_string(i) + ".bmp").c_str(), win.getWidth(), win.getHeight(), 3, result_img);

		texture.deleteTexture();
		if(i != n_layers)
			texture = Texture(result_img, win.getWidth(), win.getHeight(), 3);

		delete result_img;
	}

	win.update();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;

}