#include <stdint.h>

const int NAL_LEN_FIELD = 4;

// Convert as many full length nal units in place and return the number of bytes processed.
int Avc1ToAnnexB(uint8_t* data, int bytes);
