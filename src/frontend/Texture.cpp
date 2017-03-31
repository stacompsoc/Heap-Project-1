#include "Texture.hpp"
#include "Log.hpp"
#include "Font.hpp"

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
  gl_log("TGA loading: %s\n", filename);
  if(!tgafile.is_open()) {
    gl_log("TGA loading: Wasn't able to find image %s\n", filename);
    return;
  }

  tgafile.read(reinterpret_cast <char *> (header), sizeof(char) * 18);

  if(header[2] != 2) {
    tgafile.close();
    gl_log("TGA loading: wrong file header %s\n", filename);
    return;
  }

  if(header[0])
    tgafile.seekg(header[0], std::ios_base::cur);

  width = header[13] * 256 + header[12];
  height = header[15] * 256 + header[14];
  int bpp = header[16] / 8;

  if(bpp != 4) {
    tgafile.close();
    gl_log("TGA loading: wrong bit depth: %s\n", filename);
    return;
  }

  long imgsize = width * height * bpp;
  data = new unsigned char[imgsize];

  tgafile.read(reinterpret_cast <char *> (data), sizeof(char) * imgsize);

  for(GLuint cswap = 0; cswap < (unsigned int)imgsize; cswap += bpp) {
    std::swap(data[cswap], data[cswap + 2]);
  }
  tgafile.close();
  gl_log("TGA loading finished\n");
}

void Texture::LoadDummy() {
  data = new unsigned char[60*60*4];
  width = 60, height = 60;
  memset(data, 0xff, sizeof(unsigned char) * width * height * 4);
}

void Texture::Init(std::string filename) {
  ASSERT(data == NULL);
  ASSERT(filename.substr(filename.length() - 4, 4) == ".tga");
  /* LoadDummy(); */
  LoadTGA(filename.c_str());
  glGenTextures(1, &tex); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GLERROR
  glGenerateMipmap(GL_TEXTURE_2D); GLERROR
  Unbind();
  delete [] data;
  data = NULL;
}

void Texture::Init(FT_GlyphSlot *glyph) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); GLERROR
  glGenTextures(1, &tex); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (*glyph)->bitmap.width, (*glyph)->bitmap.rows,
               0, GL_RED, GL_UNSIGNED_BYTE, (*glyph)->bitmap.buffer); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GLERROR
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GLERROR
  Unbind();
}

void Texture::AttachToShader(ShaderProgram &program) {
  u_samp = glGetUniformLocation(program.id(), "tex"); GLERROR
}

void Texture::Bind(size_t index) const {
  glActiveTexture(GL_TEXTURE0 + index); GLERROR
  glBindTexture(GL_TEXTURE_2D, tex); GLERROR
  glUniform1i(u_samp, texcounter); GLERROR
}

void Texture::Unbind() {
  glBindTexture(GL_TEXTURE_2D, 0); GLERROR
}

void Texture::Clear() {
  glDeleteTextures(1, &tex);
}
