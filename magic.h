`/* This structure found in https://github.com/jcorrius/go-oo-mingw32-soc/blob/master/test/Lwp/bento.c 

Seems Lotus Word Pro uses Bento (WOW!)

*/


typedef struct {
  unsigned char  magic[8];
  guint16 flags;
  guint16 blockSize;
  guint16 majorVersion;
  guint16 minorVersion;
  guint32  tocOffset;
  guint32  tocSize;
} ContainerLabel; /* 24 bytes */