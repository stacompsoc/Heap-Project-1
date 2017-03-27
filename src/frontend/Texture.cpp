#include "Texture.hpp"
#include "Log.hpp"

#include <fstream>

int Texture::g_texcounter = 0;
Texture::Texture():
  texcounter(g_texcounter)
{
  ++g_texcounter;
}

Texture::~Texture()
{}

void Texture::LoadTGA(const char *filename) {
  std::ifstream tgafile(filename, std::ios::in | std::ios::binary);
  unsigned char header[20];
  std::cerr << "TGA loading: " << filename << std::endl;
  if(!tgafile.is_open()) {
    std::cerr << "TGA loading: Wasn't able to find image " << filename << std::endl;
    return;
  }

  tgafile.read(reinterpret_cast <char *> (header), sizeof(char) * 18);

  if(header[2] != 2) {
    tgafile.close();
    std::cerr << "TGA loading: wrong file header " << filename << std::endl;
    return;
  }

  if(header[0])
    tgafile.seekg(header[0], std::ios_base::cur);

  width = header[13] * 256 + header[12];
  height = header[15] * 256 + header[14];
  int bpp = header[16] / 8;

  if(bpp != 4) {
    tgafile.close();
    std::cerr << "TGA loading: wrong bit depth: " << filename << std::endl;
    return;
  }

  long imgsize = width * height * bpp;
  unsigned char *data = new unsigned char[imgsize];

  tgafile.read(reinterpret_cast <char *> (data), sizeof(char) * imgsize);

  for(GLuint cswap = 0; cswap < (unsigned int)imgsize; cswap += bpp)
    std::swap(data[cswap], data[cswap + 2]);
  tgafile.close();

}

// tga
void Texture::Init(std::string filename) {
  ASSERT(filename.substr(filename.length() - 4, 4) == ".tga");
  LoadTGA(filename.c_str());
  const GLenum color_mode = GL_RGBA;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);
  delete [] data;
}

void Texture::AttachToShader(ShaderProgram &program) const {
  ASSERT(program.id() != 0);
  glGetUniformLocation(program.id(), "tex"); GLERROR
}

void Texture::Bind() const {
  glActiveTexture(GL_TEXTURE0 + texcounter);
  glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::Unbind() const {
  glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::Clear() {
  glDeleteTextures(1, &tex);
}
