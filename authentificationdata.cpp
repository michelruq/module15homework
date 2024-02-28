#include "authentificationdata.h"

AuthentificationData::AuthentificationData() : mLogin(""), mHashedPassWord(nullptr), mStatus(AssignmentStatus::Free)
{
	
}

AuthentificationData::AuthentificationData(LoginName login, std::uint32_t* hashedPassWord) : mStatus(AssignmentStatus::Engaged)
{
	std::strcpy(mLogin, login);
	mHashedPassWord = hashedPassWord;
}

AuthentificationData& AuthentificationData::operator = (const AuthentificationData& other)
{
	if(&other == this)
	{
		return *this;
	}
	
	if(mHashedPassWord != nullptr)
	{
		delete [] mHashedPassWord;
	}
	
	mHashedPassWord = new std::uint32_t[HashNumberPerUints];
	
	std::memcpy(mHashedPassWord, other.mHashedPassWord, HashNumberBytes);
	
	std::strcpy(mLogin, other.mLogin);
	
	mStatus = other.mStatus;
	
	return *this;
}

AuthentificationData::~AuthentificationData()
{
	if(mHashedPassWord != nullptr)
	{
		delete [] mHashedPassWord;
	}
}