#pragma once

#pragma region Include

#include <../Common/Header.hpp>

#pragma endregion


namespace Nu
{
	class Entity;


	class Entity:
		public This<Entity>
	{
	public:
		inline Entity(const Reference<Entity>& this_);
		virtual ~Entity() = default;
	};
}


#pragma region Nu

#pragma region Entity

inline Nu::Entity::Entity(const Reference<Entity>& this_):
	This(this_)
{
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















