#include "PNGLogger.h"
#include <iostream>

PNGLogger::PNGLogger()
{
  filepath = getFilePath();
}


void PNGLogger::update(PNGImageDummy& dummy)
{
  if (enabled && (imageCounter % everyXFrame == 0))
  {
    theDate = getDate();
    logImage(true);
    logImage(false);
    dummy.successful = true;
  }
  imageCounter++;


}

std::string PNGLogger::getFilePath()
{
#ifdef TARGET_ROBOT
  return "/home/nao/pnglogs/";
#else
  return File::getBHDir() + std::string("/Config/Logs/PNGs/");
#endif
}

void PNGLogger::logImage(bool upper)
{
  unsigned char* imagedata = upper ? (unsigned char*)theImageUpper.image : (unsigned char*)theImage.image;
  unsigned width = upper ? 640 : 320;
  unsigned height = upper ?  480 : 240;

  unsigned char* target_ptr = upper ? targetUpper : targetLower;

  for (unsigned y = 0; y < height; y++)
  {
    for (unsigned x = 0; x < width; ++x)
    {
      if (streamAsRGB) {
      unsigned char r;
      unsigned char g;
      unsigned char b;

      ColorModelConversions::fromYCbCrToRGB(imagedata[0], imagedata[1], imagedata[3], r, g, b);

      target_ptr[0] = r;
      target_ptr[1] = g;
      target_ptr[2] = b;
      } else {
        target_ptr[0] = imagedata[0];
        target_ptr[1] = imagedata[1];
        target_ptr[2] = imagedata[3];
      }


      target_ptr += 3;
      imagedata+=4;
    }
    imagedata+=width*4;


  }

  std::string filename = filepath + theDate + "_" + std::to_string(imageCounter/everyXFrame) + "_" + (upper ? "upper" : "lower") + ".png";
  const char * filename_cstr = filename.c_str();
  stbi_write_png(filename_cstr, width, height, 3, upper ? targetUpper : targetLower, upper ? 640*3 : 320*3);



}


std::string PNGLogger::getDate()
{
  time_t now;
  char the_date[12];

  the_date[0] = '\0';

  now = time(NULL);

  if (now != -1)
  {
     strftime(the_date, 25, "%d_%m_%Y__%H_%M_%S", gmtime(&now));
  }

  return std::string(the_date);
}

MAKE_MODULE(PNGLogger, cognitionInfrastructure)
