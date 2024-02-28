#pragma once
#include <cstdint>
#include <cstring>

enum AssignmentStatus
{
	Free,
	Engaged,
	Deleted
};

class AuthentificationData
{
	public:
	   static constexpr const std::uint32_t HashNumberBytes = static_cast<std::uint32_t>(20);
	   static constexpr const std::uint32_t HashNumberPerUints = static_cast<std::uint32_t>(5);
	   static constexpr const std::uint32_t LoginLength = static_cast<std::uint32_t>(10);
	   using LoginName = char[LoginLength];
	
	   AuthentificationData();
	   AuthentificationData(LoginName login, std::uint32_t* hashedPassWord);
	   AuthentificationData& operator = (const AuthentificationData& other);
	   ~AuthentificationData();
	   
	   LoginName mLogin;
	   std::uint32_t* mHashedPassWord;
	   AssignmentStatus mStatus;
};