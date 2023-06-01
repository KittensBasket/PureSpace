#ifndef SYSTEMS_GRAPHICS_HPP
#define SYSTEMS_GRAPHICS_HPP

#include <string>
#include <stdexcept>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"

#include "game_constants.hpp"

/*
    Draw call would look like this:
    graphic_data.use();
    glDrawArraysInstances(GL_TRIANGLES, 0, prim_vertex.size(),
   instances.size());
*/

struct GraphicsData {
  private:
	unsigned int makeVBO(const std::vector<vertex> &base_vertices, const std::vector<vertex> &base_texture,
	                     const size_t max_instance_cnt) {
		unsigned int id;

		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(GL_ARRAY_BUFFER,
		             (base_vertices.size() + base_texture.size()) * sizeof(vertex) +
		                 max_instance_cnt * sizeof(instance),
		             0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, base_vertices.size() * sizeof(vertex), base_vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, base_vertices.size() * sizeof(vertex), base_texture.size() * sizeof(vertex),
		                base_texture.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return id;
	}

	unsigned int makeTexture(const char *texture_path) {
		unsigned int texture_id;

		int width, height, col_channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *image_data = stbi_load(texture_path, &width, &height, &col_channels, 0);

		if (!image_data)
			throw std::domain_error("Unable to find image in \"" + std::string(texture_path) + "\"");

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image_data);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture_id;
	}

	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _IBO;

	unsigned int _texture_id;

	const size_t instance_offset;
	const unsigned int max_instance_cnt;

  public:
	GraphicsData(const std::vector<vertex> &base_vertices, const std::vector<vertex> &base_texture,
	             const std::vector<polygon> &base_indicies, const char *texture_path,  const unsigned int max_instance_cnt)
	    : instance_offset((base_vertices.size() + base_texture.size()) * sizeof(vertex)),
	      max_instance_cnt(max_instance_cnt) {

		if (base_vertices.empty() || base_texture.empty())
			throw "TODO: better exceptions!";

		if (base_vertices.size() != base_texture.size())
			throw "TODO: better exceptions!";

		_VBO = makeVBO(base_vertices, base_texture, max_instance_cnt);
		glGenBuffers(1, &_IBO);
		glGenVertexArrays(1, &_VAO);

		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, base_indicies.size() * sizeof(polygon), base_indicies.data(),
		             GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
		                      (void *)(base_vertices.size() * sizeof(vertex)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(instance),
		                      (void *)((base_vertices.size() + base_texture.size()) * sizeof(vertex)));
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		_texture_id = makeTexture(texture_path);
	}

	~GraphicsData() {
		glDeleteBuffers(1, &_VBO);
		glDeleteBuffers(1, &_IBO);
		glDeleteVertexArrays(1, &_VAO);
		glDeleteTextures(1, (const unsigned int*)_texture_id);
	}

	void writeInstances(const std::vector<instance> &instances) {
		if (instances.size() > max_instance_cnt)
			throw "TODO: better exceptions!";

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferSubData(GL_ARRAY_BUFFER, instance_offset, instances.size() * sizeof(instances), instances.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void use() {
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

		glBindTexture(GL_TEXTURE_2D, _texture_id);
	}
};

#endif // SYSTEMS_GRAPHICS_HPP