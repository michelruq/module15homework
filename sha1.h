#pragma once
#include <cstdint>
#include <cstring>

class Sha1
{
	private:
	   static constexpr const std::uint32_t OneBlockSizeBytes = static_cast<std::uint32_t>(64);
	   static constexpr const std::uint32_t OneBlockSize4Bytes = static_cast<std::uint32_t>(16);
	   static constexpr const std::uint32_t BlockExpendSize4Bytes = static_cast<std::uint32_t>(80);
	   static constexpr const std::uint32_t Hash[5] =
	                                   {0x67452301,
										0xEFCDAB89,
										0x98BADCFE,
										0x10325476,
										0xC3D2E1F0}; //The constants are from standard
	   
	   using Block = std::uint32_t*;
	   using ExpandedBlock = std::uint32_t[BlockExpendSize4Bytes];
	
	   std::uint32_t CycleShiftLeft(std::uint32_t val, std::uint32_t bitCount);
	   std::uint32_t ConvertBigToLittleEndian(std::uint32_t val);
	
	public:
	   Sha1();
	   std::uint32_t* GetHash(char* message, std::uint32_t size);
	
};