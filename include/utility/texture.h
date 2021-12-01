#ifndef TEXTURE_H
#define TEXTURE_H

class Texture 
{
private:
  unsigned int ID;
  int enumType;

public:
  Texture();
  void bind(int enumType);
  void generateTexture(const char* file, int rgbType, bool flip = false);
};

#endif