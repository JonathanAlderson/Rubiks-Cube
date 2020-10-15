#ifndef _IMAGE_
#define _IMAGE_

#include<string>
#include <QImage>
#include <GL/glu.h>


class Image {
 public:
  Image(const std::string& fn);

  ~Image();

  Image(const Image&);


  const GLubyte* imageField() const;

  unsigned int Width()  const { return _width;}
  unsigned int Height() const {return _height;}
 private:

  unsigned int _width;
  unsigned int _height;

  QImage* p_qimage;


  GLubyte* _image;
};

#endif
