// This converts avc1 nal units (h264 formatted in an mp4 file) to annex B nal units.
// avc1 nal length field is 4 bytes in this exercise.
//
// AVC1 layout is the following:
// [4 bytes nal data length in big-endian][annex B nal data]
//
// Annex B layout is the following:
// [0x00000001 start code][annex B nal data]
//
// annex B nal data looks like this:
// [1 byte nal header][rbsp][stop bit]
//
// You don't need to understand the annex B layout, all that is required
// is to convert the 4 byte nal length header to the annex B start code (0x00000001)
// and move to the next nal.
//
// If anyone has done actual h264 decoding/demuxing they have parsed nal units
// and converted between formats.  Bonus points if the candidate knows all of this
// without being told and can just write the code.  If they don't, just explain 
// the two layouts and have them write the code.
//
// The only difficult part here is knowing how to deal with big-endian numbers.

#include "avc1_to_annexb.h"

const int NAL_LEN_FIELD = 4;

// Convert as many full length nal units in place and return the number of bytes processed.
int Avc1ToAnnexB(uint8_t* data, int bytes)
{
    int initial_bytes = bytes;
    int nal_len = 0;

    while (bytes > NAL_LEN_FIELD)
    {
        // Get the nal data length from the big-endian header
        nal_len = ((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]) + NAL_LEN_FIELD;

        if (bytes >= nal_len)
        {
            // Convert header to a nal start code (0x000001)
            data[0] = data[1] = data[2] = 0;
            data[3] = 1;

            // Move to the next nal unit
            data += nal_len;
            bytes -= nal_len;
        }
        else
        {
            break;
        }
    }

    return initial_bytes - bytes;
}