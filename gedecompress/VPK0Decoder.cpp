// BY ZOINKITY

#include "StdAfx.h"
#include "VPK0Decoder.h"

CVPK0Decoder::CVPK0Decoder(void)
{
}

CVPK0Decoder::~CVPK0Decoder(void)
{
}

int  CVPK0Decoder::_flags(unsigned char* inputBuffer, int& inputPosition, unsigned char& flags, int& flagsLeft, int compressedSize)
{
	if (flagsLeft == 0)
	{
		if (inputPosition >= compressedSize)
			return 0;
		flagsLeft = 8;
		flags = inputBuffer[inputPosition++];
	}

    int value = ((flags&0x80)>0);
    flags<<=1;
	flagsLeft--;
	return value;
}

unsigned long CVPK0Decoder::_nbits(unsigned char* inputBuffer, int& inputPosition, unsigned char& flags, int& flagsLeft, int num, int compressedSize)
{
    //"""Returns a value equal to the next num bits in stream.
    //itr should point to the self._flags() method above."""
    unsigned long v=0;
    for (int i = 0; i < num; i++)
	{
        v <<=1;
		bool flagRet = _flags(inputBuffer, inputPosition, flags, flagsLeft, compressedSize);;
        v|=flagRet;
	}
    return v;
}

int CVPK0Decoder::header(unsigned char* data, int& mode, unsigned long& dec_s)
{
    //"""Returns tuple: mode and compressed size""" 
    unsigned long name = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
    mode = data[3] - 48; 
    dec_s= (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | (data[7]);
    if ((name & 0xFFFFFF00) != 0x76706B00)
        return -1;
    else 
        return mode;
}

void CVPK0Decoder::_tblbuild(unsigned char* inputBuffer, int& inputPosition, unsigned char& flags, int& flagsLeft, Triplet*& tbl, int& tripletCount, int compressedSize)
{
    //"""Builds a table of ints and references from a bitsequence. 
    //itr should be a pointer to _flags(itr) or something similiar.""" 
	tripletCount = 0;
    tbl = new Triplet[0x100000];
    unsigned char* buf = new unsigned char[0x100000];
	int bufSize = 0;
    //# Current index and final index, respectively. 
    int idx = 0;
    //## convenience, instead of looking it up all the time 
    int fin = 0;


    while (true)
	{
		if (_flags(inputBuffer, inputPosition, flags, flagsLeft, compressedSize))
		{
            //# If idx == 0, the table is finished 
            if (idx<2)
                break;
            //## reference 
            tbl[tripletCount++] = Triplet(buf[idx-2], buf[idx-1], 0);
            buf[idx-2] = fin ;
            fin+=1;
            idx-=1;
		}
        else
		{
            //## integer entry 
            unsigned char v = _nbits(inputBuffer, inputPosition, flags, flagsLeft, 8, compressedSize);
            tbl[tripletCount++] = Triplet(0,0,v);
            if (bufSize<=idx)
                buf[bufSize++] = fin;
            else 
                buf[idx] = fin;
            fin+=1;
            idx+=1;
		}
	}

	delete [] buf;
}

int CVPK0Decoder::_tblsel(unsigned char* inputBuffer, int& inputPosition, unsigned char& flags, int& flagsLeft, Triplet*& tbl, int& tripletCount, int compressedSize, int idx)
{
        //"""Uses bitflags to iterate the table until non-reference entry found. 
        //Returns an int with the width given by the table entry. 
        //itr should be a pointer to _flags(itr) or something similiar.""" 
        //# idx is set to final entry by default; override only if you're doing something special. 
        if (idx<0)
            idx = (tripletCount-1);
        if (idx<0)
            return 0; 

        //# Iterates from end fo the list to the beginning; final entry always a reference. 
		while (!tbl[idx].two)
		{
            if (_flags(inputBuffer, inputPosition, flags, flagsLeft, compressedSize))
				idx = tbl[idx].one;
            else
				idx = tbl[idx].zero;
		}
		return _nbits(inputBuffer, inputPosition, flags, flagsLeft, tbl[idx].two, compressedSize);
}

int CVPK0Decoder::dec(unsigned char* inputBuffer, int compressedSize, int dec_s, unsigned char* output)
{

	int inputPosition = 0;
	int outputPosition = 0;

	unsigned char flags = 0;
	int flagsLeft = 0;

    //"""Decompresses vpk0 data to output. 
    //If header not present, reads it from the file. 
    //In the case of an error or incompatible format, 
    //    returns an empty bytearray.""" 
    //# initialize the data stream 
	unsigned long f = 0;

    //# Retrieve sample length 
    int sl = _nbits(inputBuffer, inputPosition, flags, flagsLeft, 8, compressedSize);

	Triplet* tbl1 = NULL;
	Triplet* tbl2 = NULL;
	int tbl1Size;
	int tbl2Size;

    //# Build table 1 
	_tblbuild(inputBuffer, inputPosition, flags, flagsLeft, tbl1, tbl1Size, compressedSize);

    //# Build table 2 
    _tblbuild(inputBuffer, inputPosition, flags, flagsLeft, tbl2, tbl2Size, compressedSize);

    while (outputPosition < dec_s)
	{
        if (_flags(inputBuffer, inputPosition, flags, flagsLeft, compressedSize))
		{
			int p = 0;
            //# Copy bytes from output 
            if (sl)
			{
                //## two-sample backtrack lengths 
                int l = 0;
                int u = _tblsel(inputBuffer, inputPosition, flags, flagsLeft, tbl1, tbl1Size, compressedSize);
                if (u<3)
				{
                    l = u+1;
                    u = _tblsel(inputBuffer, inputPosition, flags, flagsLeft, tbl1, tbl1Size, compressedSize);
				}
                p = outputPosition - (u<<2) - l + 8;
			}
            else
			{
                //## one-sample backtrack lengths 
                p = outputPosition - _tblsel(inputBuffer, inputPosition, flags, flagsLeft, tbl1, tbl1Size, compressedSize);
			}
            //# Grab #bytes to copy 
            int n = _tblsel(inputBuffer, inputPosition, flags, flagsLeft, tbl2, tbl2Size, compressedSize);
            //# Append n bytes from p to output. 
            //# Do it byte-by-byte to allow replication. 
            for (int i = p; i < p+n; i++)
                output[outputPosition++] = output[i];
		}
        else
		{
            //# Push next byte to output 
            output[outputPosition++] = _nbits(inputBuffer, inputPosition, flags, flagsLeft, 8, compressedSize);
		}
	}

	delete [] tbl1;
	delete [] tbl2;
    return outputPosition;
}