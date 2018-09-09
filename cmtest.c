#include "cmerrors.h"
#include <stdio.h>

void main(void)
{
  char errorString[256];

//  printf("## %s\n", CMGetErrorString(errorString, 256, CMERR_NoSession));
  printf("## %s\n", CMGetErrorString(errorString, 256, CMERR_GenericMessage, "test"));
}
