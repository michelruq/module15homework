#include "chathash.h"

ChatHash::ChatHash()
{
	mSize = static_cast<std::uint32_t>(8);
	mContainer = new AuthentificationData[mSize];
	mCount = 0;
}

ChatHash::~ChatHash()
{
	delete [] mContainer;
}

void ChatHash::addItem(AuthentificationData::LoginName name, char* passWord, std::uint32_t passWordLength)
{
   std::int32_t index = static_cast<std::int32_t>(-1);
   std::uint32_t i = static_cast<std::int32_t>(0);
   for(; i < mSize; ++i)
   {
	  index = GetHash(name, i);
	  if(mContainer[index].mStatus == AssignmentStatus::Free)
      {
		  break;
	  }
   }
   
   if(i >= mSize)
   {
	   resize();
	   addItem(name, passWord, passWordLength);
   }
   else
   {	   
	   mContainer[index] = AuthentificationData(name, oSha1.GetHash(passWord, passWordLength));
	   ++mCount;
   }
}

bool ChatHash::find(AuthentificationData::LoginName name, char* passWord, std::uint32_t passWordLength)
{
   std::uint32_t i = static_cast<std::uint32_t>(0);
   std::uint32_t index = static_cast<std::uint32_t>(-1);
   for(; i < mSize; ++i)
   {
      index = GetHash(name,i);
	  if(mContainer[index].mStatus == AssignmentStatus::Engaged)
      {
		  if(!std::strcmp(mContainer[index].mLogin, name))
		  {
			  break;
		  }
	  }
   }
   
   if(i >= mSize) return false;  
	
   bool cmpHashes = !memcmp(mContainer[index].mHashedPassWord, oSha1.GetHash(passWord, passWordLength), AuthentificationData::HashNumberBytes);
   return cmpHashes;
}

void ChatHash::deletion(AuthentificationData::LoginName name)
{
	std::uint32_t i = static_cast<std::uint32_t>(0);
	for(; i < mSize; ++i)
	{
		std::uint32_t index = GetHash(name, i);
		if(mContainer[index].mStatus == AssignmentStatus::Engaged)
		{
		   if(!std::strcmp(mContainer[index].mLogin, name))
		   {
			  mContainer[index].mStatus = AssignmentStatus::Deleted;
			  --mCount;
			  return;
		   }
		}
	}
	
	if (i >= mSize) return;
}

void ChatHash::resize()
{
	AuthentificationData* intermediate = mContainer;
	
	std::uint32_t oldSize = mSize;
	
	mSize *= static_cast<std::uint32_t>(2);
	mCount = static_cast<std::uint32_t>(0);
	
	mContainer = new AuthentificationData[mSize];
	
	for(std::uint32_t i = static_cast<std::uint32_t>(0); i < oldSize; ++i)
	{
		if(intermediate[i].mStatus == AssignmentStatus::Engaged)
		{
			for(std::uint32_t j = static_cast<std::uint32_t>(0); j < mSize; ++j)
			{
				std::uint32_t index = GetHash(intermediate[i].mLogin, j);
				if(mContainer[index].mStatus == AssignmentStatus::Free)
				{
					mContainer[index] = AuthentificationData(intermediate[i].mLogin, intermediate[i].mHashedPassWord);
					++mCount;
					break;
				}
			}
		}
	}
	
	delete intermediate;
}

std::uint32_t ChatHash::GetHash(AuthentificationData::LoginName name, std::uint32_t offset)
{
	std::uint32_t sum = static_cast<std::uint32_t>(0);
	for(std::uint32_t i = static_cast<std::uint32_t>(0); i < std::strlen(name); ++i)
	{
		sum += name[i];
	}
	
	return (GetMultiplyMethod(sum) + offset*offset) % mSize;
}

std::uint32_t ChatHash::GetMultiplyMethod(std::uint32_t incomingValue)
{
	constexpr const float A = 0.7F;
	return static_cast<std::uint32_t>(mSize * A * incomingValue);
}
