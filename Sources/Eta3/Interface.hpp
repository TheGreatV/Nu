#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Eta3
	{
		class Entity
		{
		public:
			virtual ~Entity() = default;
		};
		
		class Unit:
			public Entity
		{
		public:
			virtual ~Unit() override = default;
		};

		class Type:
			public Unit
		{
		public:
			virtual ~Type() override = default;
		};
		class Instance:
			public Unit
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Type> GetType() const = 0;
		};

		class Executable:
			public Entity
		{
		public:
			class Result;
			class Body;
		public:
			virtual ~Executable() override = default;
		public:
			virtual Reference<Result> GetResult() const = 0;
		};
#pragma region Executable::Result
		class Executable::Result:
			public Entity
		{
		public:
			class None;
			class Instance;
		public:
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Executable::Result::None
		class Executable::Result::None:
			public Executable::Result
		{
		public:
			virtual ~None() override = default;
		};
#pragma endregion
#pragma region Executable::Result::Instance
		class Executable::Result::Instance:
			public Executable::Result
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Type> GetType() const = 0;
		};
#pragma endregion
#pragma region Executable::Body
		class Executable::Body:
			public Entity
		{
		public:
			class Internal;
			class CommandList;
		public:
			virtual ~Body() override = default;
		};
#pragma endregion
#pragma region Executable::Body::Internal
		class Executable::Body::Internal:
			public Executable::Body
		{
		public:
			virtual ~Internal() override = default;
		};
#pragma endregion
#pragma region Executable::Body::CommandList
		class Executable::Body::CommandList:
			public Executable::Body
		{
		public:
			using Commands = Vector<Reference<Command>>;
		public:
			virtual ~CommandList() override = default;
		public:
			virtual Commands GetCommands() const = 0;
		};
#pragma endregion
		class Instruction:
			public Unit,
			public Executable
		{
		public:
			virtual ~Instruction() override = default;
		};
		class Algorithm:
			public Unit,
			public Executable
		{
		public:
			class Argument;
		public:
			using Arguments = Vector<Reference<Argument>>;
			using Commands = Vector<Reference<Command>>;
		public:
			virtual ~Algorithm() override = default;
		public:
			virtual Arguments GetArguments() const = 0;
		};
#pragma region Algorithm::Argument
		class Algorithm::Argument:
			public Entity
		{
		public:
			class Instance;
			class Instruction;
		public:
			virtual ~Argument() override = default;
		};
#pragma endregion
#pragma region Algorithm::Argument::Instance
		class Algorithm::Argument::Instance:
			public Algorithm::Argument
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta3::Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Argument::Instruction
		class Algorithm::Argument::Instruction:
			public Algorithm::Argument
		{
		public:
			virtual ~Instruction() override = default;
		public:
			virtual Reference<Eta3::Instruction> GetInstruction() const = 0;
		};
#pragma endregion

		class Command:
			public Entity
		{
		public:
			class CreateInstance;
			class DeleteInstance;
			class Return;
			class Call;
		public:
			virtual ~Command() override = default;
		};
#pragma region Command::CreateInstance
		class Command::CreateInstance:
			public Command
		{
		public:
			virtual ~CreateInstance() override = default;
		public:
			virtual Reference<Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Command::DeleteInstance
		class Command::DeleteInstance:
			public Command
		{
		public:
			virtual ~DeleteInstance() override = default;
		public:
			virtual Reference<Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Command::Return
		class Command::Return:
			public Command
		{
		public:
			class None;
			class Instance;
		public:
			virtual ~Return() override = default;
		public:
			virtual Reference<Executable> GetExecutable() const = 0;
		};
#pragma endregion
#pragma region Command::Return::None
		class Command::Return::None:
			public Return
		{
		public:
			virtual ~None() override = default;
		};
#pragma endregion
#pragma region Command::Return::Instance
		class Command::Return::Instance:
			public Return
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta3::Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Command::Call
		class Command::Call:
			public Command
		{
		public:
			class Executable;
			class Instruction;
			class Algorithm;
		public:
			virtual ~Call() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable
		class Command::Call::Executable:
			public Call
		{
		public:
			class Result;
		public:
			virtual ~Executable() override = default;
		public:
			virtual Reference<Result> GetResult() const = 0;
		};
#pragma endregion
#pragma region Command::Call::Executable::Result
		class Command::Call::Executable::Result:
			public Entity
		{
		public:
			class None;
			class Instance;
		public:
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable::Result::None
		class Command::Call::Executable::Result::None:
			public Result
		{
		public:
			virtual ~None() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable::Result::Instance
		class Command::Call::Executable::Result::Instance:
			public Result
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta3::Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Command::Call::Instruction
		class Command::Call::Instruction:
			public Executable
		{
		public:
			virtual ~Instruction() override = default;
		public:
			virtual Reference<Eta3::Instruction> GetInstruction() const = 0;
		};
#pragma endregion
#pragma region Command::Call::Algorithm
		class Command::Call::Algorithm:
			public Executable
		{
		public:
			class Argument;
		public:
			using Arguments = Vector<Reference<Argument>>;
		public:
			virtual ~Algorithm() override = default;
		public:
			virtual Reference<Eta3::Algorithm> GetAlgorithm() const = 0;
			virtual Arguments GetArguments() const = 0;
		};
#pragma endregion
#pragma region Command::Call::Algorithm::Argument
		class Command::Call::Algorithm::Argument:
			public Entity
		{
		public:
			class Instance;
			class Instruction;
		public:
			virtual ~Argument() override = default;
		};
#pragma endregion
#pragma region Command::Call::Algorithm::Argument::Instance
		class Command::Call::Algorithm::Argument::Instance:
			public Entity
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta3::Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Command::Call::Algorithm::Argument::Instruction
		class Command::Call::Algorithm::Argument::Instruction:
			public Entity
		{
		public:
			virtual ~Instruction() override = default;
		public:
			virtual Reference<Eta3::Instruction> GetInstruction() const = 0;
		};
#pragma endregion


		class Assembly:
			public Entity
		{
		public:
			using Types = Map<String, Reference<Type>>;
			using Instructions = Map<String, Reference<Instruction>>;
			using Algorithms = Map<String, Reference<Algorithm>>;
			using Instances = Map<String, Reference<Instance>>;
		public:
			virtual ~Assembly() override = default;
		public:
			virtual Types GetTypes() const = 0;
			virtual Instructions GetInstructions() const = 0;
			virtual Algorithms GetAlgorithms() const = 0;
			virtual Instances GetInstances() const = 0;
		};
	}
}


#pragma region Nu

#pragma region Eta3

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















