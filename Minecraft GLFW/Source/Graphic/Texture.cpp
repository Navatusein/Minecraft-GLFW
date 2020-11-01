#include "Texture.h"



Texture* CreateTexture(std::string File) {
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height;
    unsigned char* image = SOIL_load_image(File.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if (image == NULL) {
        std::cout << "[Texture] Fail read " << File << std::endl;
        glDeleteTextures(1, &texture);
        return nullptr;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return new Texture(texture, width, height);
}

Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
