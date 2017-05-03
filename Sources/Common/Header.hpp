#pragma once

#pragma region Include

#include <memory>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>

#pragma endregion


namespace Nu
{
	// Usings
	using Size = std::size_t;
	using String = std::string;
	using WString = std::wstring;
	template<class First, class Second> using Pair = std::pair<First, Second>;

	template<class Type>				using Memory = Type*;
	template<class Type>				using Pointer = std::unique_ptr<Type>;
	template<class Type>				using Link = std::weak_ptr<Type>;
	template<class Type>				using Reference = std::shared_ptr<Type>;

	template<class Type, Size Size>		using Array = std::array<Type, Size>;
	template<class Type>				using Vector = std::vector<Type>;
	template<class Type>				using List = std::list<Type>;
	template<class Key, class Value>	using Map = std::map<Key, Value>;
	template<class Type>				using Set = std::set<Type>;
	template<class Type>				using Initializer = std::initializer_list<Type>;


	// Types
	template<class Type> class This;

	class Exception;


	// Functions
	template<class To, class From> inline Reference<To> Cast(const Reference<From>& from_);
	template<class To, class From> inline Reference<const To> Cast(const Reference<const From>& from_);
	template<class To, class From> inline Reference<To> UpCast(const Reference<From>& from_);
	template<class To, class From> inline Reference<const To> UpCast(const Reference<const From>& from_);

	template<class Type> inline typename std::remove_reference<Type>::type&& Move(Type&& type_);
	template<class Type> inline Type&& Forward(typename std::remove_reference<Type>::type& type_);

	template<class Type> inline Pointer<Type> WrapPointer(Type*const type_);
	template<class Type> inline Pointer<const Type> WrapPointer(const Type*const type_);
	template<class Type, class...Arguments> inline Pointer<Type> MakePointer(Arguments&&...arguments_);

	template<class Type> inline Link<Type> MakeLink(const Reference<Type>& reference_);

	template<class Type> inline Reference<Type> WrapReference(Type*const type_);
	template<class Type> inline Reference<const Type> WrapReference(const Type*const type_);
	template<class Type> inline Reference<Type> MakeReference(const Link<Type>& link_);
	template<class Type, class...Arguments> inline Reference<Type> MakeReference(Arguments&&...arguments_);

	template<class Type> inline Memory<Type> AllocateMemory();
	template<class Type> inline void ReleaseMemory(const Memory<Type>& memory_);

	template<class Type, class...Arguments> inline Reference<Type> Make(Arguments&&...arguments_);


	// Classes definition
	template<class Basic> class SmartDestructor:
		public Basic
	{
		template<class Type, class...Arguments> friend inline Reference<Type> Make(Arguments&&...arguments_);
	protected:
		bool isConstructed;
	};

	template<class Type> class This
	{
	protected:
		Link<Type> self;
	public:
		inline This(const Reference<Type>& this_);
	public:
		template<class Child> inline Reference<Child> GetThis() const;
		inline Reference<Type> GetThis() const;
	};

	class Exception
	{
	public:
		using Text = String;
	protected:
		const Text text = "Unknown exception";
	public:
		inline Exception() = default;
		inline Exception(const Text& errorText_);
		inline Exception(const Exception&) = default;
		inline ~Exception() = default;
	public:
		inline Exception& operator = (const Exception& source) = delete;
	public:
		inline Text GetText() const;
	};

}


#pragma region Nu

#pragma region This

template<class Type>
inline Nu::This<Type>::This(const Reference<Type>& this_):
	self(this_)
{
}

template<class Type> template<class Child>
inline Nu::Reference<Child> Nu::This<Type>::GetThis() const
{
	return Cast<Child>(MakeReference(self));
}
template<class Type>
inline Nu::Reference<Type> Nu::This<Type>::GetThis() const
{
	return MakeReference(self);
}

#pragma endregion

#pragma region Exception

inline Nu::Exception::Exception(const Text& errorText_):
	text(errorText_)
{
}

inline Nu::Exception::Text Nu::Exception::GetText() const
{
	return text;
}

#pragma endregion


template<class To, class From>
inline Nu::Reference<To> Nu::Cast(const Reference<From>& from_)
{
	return std::static_pointer_cast<To>(from_);
}
template<class To, class From>
inline Nu::Reference<const To> Nu::Cast(const Reference<const From>& from_)
{
	return std::static_pointer_cast<const To>(from_);
}
template<class To, class From>
inline Nu::Reference<To> Nu::UpCast(const Reference<From>& from_)
{
	return std::dynamic_pointer_cast<To>(from_);
}
template<class To, class From>
inline Nu::Reference<const To> Nu::UpCast(const Reference<const From>& from_)
{
	return std::dynamic_pointer_cast<const To>(from_);
}

template<class Type>
inline typename std::remove_reference<Type>::type&& Nu::Move(Type&& type_)
{
	return std::move(type_);
}
template<class Type>
inline Type&& Nu::Forward(typename std::remove_reference<Type>::type& type_)
{
	return std::forward<Type>(type_);
}


template<class Type>
inline Nu::Pointer<Type> Nu::WrapPointer(Type*const type_)
{
	return Move(Pointer<Type>(type_));
}
template<class Type>
inline Nu::Pointer<const Type> Nu::WrapPointer(const Type*const type_)
{
	return Move(Pointer<const Type>(type_));
}
template<class Type, class...Arguments>
inline Nu::Pointer<Type> Nu::MakePointer(Arguments&&...arguments_)
{
	return Move(std::make_unique<Type>(Forward<Arguments>(arguments_)...));
}

template<class Type>
inline Nu::Link<Type> Nu::MakeLink(const Reference<Type>& reference_)
{
	return Move(Link<Type>(reference_));
}

template<class Type>
inline Nu::Reference<Type> Nu::WrapReference(Type*const type_)
{
	return Move(Reference<Type>(type_));
}
template<class Type>
inline Nu::Reference<const Type> Nu::WrapReference(const Type*const type_)
{
	return Move(Reference<const Type>(type_));
}
template<class Type>
inline Nu::Reference<Type> Nu::MakeReference(const Link<Type>& link_)
{
	return Move(Reference<Type>(link_));
}
template<class Type, class...Arguments>
inline Nu::Reference<Type> Nu::MakeReference(Arguments&&...arguments_)
{
	return Move(std::make_shared<Type>(std::forward<Arguments>(arguments_)...));
}

template<class Type>
inline Nu::Memory<Type> Nu::AllocateMemory()
{
	auto rawMemory = std::malloc(sizeof(Type));
	auto memory = static_cast<Memory<Type>>(rawMemory);
	return memory;
}
template<class Type>
inline void Nu::ReleaseMemory(const Memory<Type>& memory_)
{
	std::free(memory_);
}

template<class Type, class...Arguments>
inline Nu::Reference<Type> Nu::Make(Arguments&&...arguments_)
{
	auto holder = AllocateMemory<SmartDestructor<Type>>();
	holder->isConstructed = false;

	auto shared = Move(Reference<Type>(static_cast<Type*>(holder), [](Type* memory_){
		auto holder = static_cast<SmartDestructor<Type>*>(memory_);

		if(holder->isConstructed)
		{
			holder->~SmartDestructor<Type>();
		}

		ReleaseMemory(holder);
	}));

	new(holder)Type(shared, Forward<Arguments>(arguments_)...);
	holder->isConstructed = true;

	return Move(shared);
}

#pragma endregion


#pragma region
#pragma endregion



















