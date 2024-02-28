#pragma once

#include <cstdint>
#include "authentificationdata.h"
#include "sha1.h"

class ChatHash
{
	private:
		AuthentificationData* mContainer;	
	    std::uint32_t mCount;
		std::uint32_t mSize;
		Sha1 oSha1;
		
		void resize();
		std::uint32_t GetHash(AuthentificationData::LoginName name, std::uint32_t offset);
		std::uint32_t GetMultiplyMethod(std::uint32_t incomingValue);
	
	public: 
		ChatHash();
		~ChatHash();
		void addItem(AuthentificationData::LoginName name, char* passWord, std::uint32_t passWordLength);
		bool find(AuthentificationData::LoginName name, char* passWord, std::uint32_t passWordLength);
		void deletion(AuthentificationData::LoginName name);
	
};