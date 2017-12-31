#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Translator2
	{
		class Executable;
		class Result;
		namespace Results
		{
			class ReturnInstance;
		}
		class Argument;
		namespace Arguments
		{
			class CopyInstance;
		}
		class Schema;
		class Algorithm;
		namespace Algorithms
		{
			class Brace;
		}
		class Instance;
		class Command;
		namespace Commands
		{
			class Argument;
			namespace Arguments
			{
				class CopyInstance;
			}
			class CreateInstance;
			class CallAlgorithm;
			class CallBraceAlgorithm;
		}


		class Executable
		{
		public:
			using Commands = Vector<Reference<Command>>;
		public:
			virtual ~Executable() = default;
		public:
			virtual Result GetResult() const = 0;
			virtual Commands GetCommands() const = 0;
		};
		class Result
		{
		public:
			virtual ~Result() = default;
		};
		namespace Results
		{
			class ReturnInstance:
				public Result
			{
			public:
				virtual ~ReturnInstance() = default;
			public:
				virtual Reference<Schema> GetSchema() const = 0;
			};
		}
		class Argument
		{
		public:
			virtual ~Argument() = default;
		};
		namespace Arguments
		{
			class CopyInstance:
				public Argument
			{
			public:
				virtual ~CopyInstance() = default;
			public:
				virtual Reference<Schema> GetSchema() const = 0;
			};
		}
		class Schema
		{
		public:
			using Algorithms = Vector<Reference<Algorithm>>;
		public:
			virtual ~Schema() = default;
		public:
			virtual Algorithms GetAlgorithms() const = 0;
		};
		class Algorithm:
			public Executable
		{
		public:
			virtual ~Algorithm() = default;
		public:
			virtual Link<Schema> GetSchema() const = 0;
		};
		namespace Algorithms
		{
			class Brace:
				public Algorithm
			{
			public:
				using BraceType = void;
				using Arguments = Vector<Reference<Argument>>;
			public:
				virtual ~Brace() = default;
			public:
				virtual BraceType GetOpening() const = 0;
				virtual BraceType GetClosing() const = 0;
				virtual Arguments GetArguments() const = 0;
			};
		}
		class Instance
		{
		public:
			virtual ~Instance() = default;
		public:
			virtual Reference<Schema> GetSchema() const = 0;
		};
		class Command
		{
		public:
			virtual ~Command() = default;
		};
		namespace Commands
		{
			class Argument:
				public Command
			{
			public:
				virtual ~Argument() = default;
			};
			namespace Arguments
			{
				class CopyInstance:
					public Argument
				{
				public:
					virtual ~CopyInstance() = default;
				public:
					virtual Reference<Instance> GetInstance() const = 0;
				};
			}
			class CreateInstance:
				public Command
			{
			public:
				virtual ~CreateInstance() = default;
			public:
				virtual Reference<Instance> GetInstance() const = 0;
			};
			class ReturnInstance:
				public Command
			{
			public:
				virtual ~ReturnInstance() = default;
			public:
				virtual Reference<Instance> GetResult() const = 0;
			};
			class CallAlgorithm:
				public ReturnInstance
			{
			public:
				virtual ~CallAlgorithm() = default;
			public:
				virtual Reference<Algorithm> GetAlgorithm() const = 0;
			};
			class CallBraceAlgorithm
			{
			public:
				using Arguments = Vector<Reference<Argument>>;
			public:
				virtual ~CallBraceAlgorithm() = default;
			public:
				virtual Arguments GetArguments() const = 0;
			};
		}
	}
}


#pragma region Nu

#pragma region Translator2

#pragma endregion

#pragma endregion

#pragma region
#pragma endregion




















