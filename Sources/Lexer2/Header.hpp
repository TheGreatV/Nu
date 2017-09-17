#pragma once

#pragma region Include

#include <../Header/Header.hpp>

#pragma endregion


namespace Nu
{
	namespace Lexing2
	{
		class Entity;


		class Entity:
			public Nu::Entity
		{
		public:
			inline Entity(const Reference<Entity>& this_);
			virtual ~Entity() override = default;
		};
	}
}


#pragma region Nu

#pragma region Entity

inline Nu::Lexing2::Entity::Entity(const Reference<Entity>& this_):
	Nu::Entity(this_)
{
}

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion



















