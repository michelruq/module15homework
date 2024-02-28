#include "sha1.h"

Sha1::Sha1()
{
	
}

std::uint32_t Sha1::CycleShiftLeft(std::uint32_t val, std::uint32_t bitCount)
{
	return ((val << bitCount) | (val >> (32 - bitCount)));
}

std::uint32_t Sha1::ConvertBigToLittleEndian(std::uint32_t val)
{
	return  ((val & 0x000000FF) << 24) | 
            ((val & 0x0000FF00) << 8) | 
            ((val & 0x00FF0000) >> 8) | 
            ((val & 0xFF000000) >> 24);
}

std::uint32_t* Sha1::GetHash(char* message, std::uint32_t size)
{
	std::uint32_t A = Hash[0];
	std::uint32_t B = Hash[1];
	std::uint32_t C = Hash[2];
	std::uint32_t D = Hash[3];
	std::uint32_t E = Hash[4];
	
	std::uint32_t CompleteBlockCount = size / OneBlockSizeBytes;
	
	std::uint32_t RequiredNumberBytesForLastBlock = OneBlockSizeBytes - (size - CompleteBlockCount * OneBlockSizeBytes);
	
	if(RequiredNumberBytesForLastBlock < static_cast<std::uint32_t>(8))
	{
		CompleteBlockCount += static_cast<std::uint32_t>(2);
		RequiredNumberBytesForLastBlock += OneBlockSizeBytes;
	}
	else
	{
		CompleteBlockCount += static_cast<std::uint32_t>(1);
	}
	
	std::uint32_t extendedMessageSize = size + RequiredNumberBytesForLastBlock;
	
	char* newMessage = new char [extendedMessageSize];
	
	memcpy(newMessage, message, size);
	newMessage[size] = 0x80;
	memset(newMessage + size + 1, 0, RequiredNumberBytesForLastBlock - 1);
	
	std::uint32_t* ptrToSize = (std::uint32_t*) (newMessage + extendedMessageSize - 4);
	*ptrToSize = ConvertBigToLittleEndian(size * static_cast<std::uint32_t>(8));
	
	ExpandedBlock expBlock;
	
	for(std::uint32_t i = static_cast<std::uint32_t>(0); i < CompleteBlockCount; ++i )
	{
		char* currentPtr = newMessage + OneBlockSizeBytes*i;
		Block block = reinterpret_cast<Block>(currentPtr);
		
		for(std::uint32_t j = static_cast<std::uint32_t>(0); j < OneBlockSize4Bytes; ++j)
		{
			expBlock[j] = ConvertBigToLittleEndian(block[j]);
		}
		
		for(std::uint32_t j = OneBlockSize4Bytes; j < BlockExpendSize4Bytes; ++j)
		{
			expBlock[j] = 
			    expBlock[j - 3] ^ 
				    expBlock[j - 8] ^
					    expBlock[j - 14] ^
						    expBlock[j - 16];
							
				expBlock[j] = CycleShiftLeft(expBlock[j], 1);			
		}
		
		std::uint32_t a = Hash[0];
		std::uint32_t b = Hash[1];
		std::uint32_t c = Hash[2];
		std::uint32_t d = Hash[3];
		std::uint32_t e = Hash[4];
		
		for(std::uint32_t j = 0; j < BlockExpendSize4Bytes; j++) 
		{
            std::uint32_t f;
            std::uint32_t k;
            // в зависимости от раунда считаем по-разному
            if (j < static_cast<std::uint32_t>(20)) 
			{
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } 
			else if (j < static_cast<std::uint32_t>(40)) 
			{
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } 
			else if (j < static_cast<std::uint32_t>(60)) 
			{
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } 
			else 
			{
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
        
            // перемешивание
            std::uint32_t temp = CycleShiftLeft(a,5) + f + e + k + expBlock[j];
            e = d;
            d = c;
            c = CycleShiftLeft(b,30);
            b = a;
            a = temp;   
        }
		
		A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
	}
	std::uint32_t* digest = new std::uint32_t[5];
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
	
	delete[] newMessage;
	
	return digest; 
}