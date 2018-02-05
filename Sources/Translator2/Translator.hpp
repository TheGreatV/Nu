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
			class Result;
			namespace Results
			{
				class ReturnInstance;
			}
			class Argument;
			namespace Arguments
			{
				class CopyInstance;
				class CopyResultInstance;
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
			inline virtual Reference<Result> GetResult() const = 0;
			inline virtual Commands GetCommands() const = 0;
		};
		class Result
		{
		public:
			inline virtual ~Result() = default;
		};
		namespace Results
		{
			class ReturnInstance:
				public Result
			{
			public:
				inline virtual ~ReturnInstance() = default;
			public:
				inline virtual Reference<Schema> GetSchema() const = 0;
			};
		}
		class Argument
		{
		public:
			inline virtual ~Argument() = default;
		};
		namespace Arguments
		{
			class CopyInstance:
				public Argument
			{
			public:
				inline virtual ~CopyInstance() = default;
			public:
				inline virtual Reference<Instance> GetInstance() const = 0;
			};
		}
		class Schema
		{
		public:
			using Algorithms = Vector<Reference<Algorithm>>;
		public:
			virtual ~Schema() = default;
		};
		class Algorithm:
			public Executable
		{
		public:
			inline virtual ~Algorithm() = default;
		};
		namespace Algorithms
		{
			class Brace:
				public Algorithm
			{
			public:
				enum class BraceType
				{
					Round,
					Square,
					Figure,
				};
			public:
				using Arguments = Vector<Reference<Argument>>;
			public:
				inline virtual ~Brace() = default;
			public:
				inline virtual BraceType GetOpening() const = 0;
				inline virtual BraceType GetClosing() const = 0;
				inline virtual Arguments GetArguments() const = 0;
			};
		}
		class Instance
		{
		public:
			inline virtual ~Instance() = default;
		public:
			inline virtual Link<Schema> GetSchema() const = 0;
		};
		class Command
		{
		public:
			inline virtual ~Command() = default;
		};
		namespace Commands
		{
			class Result:
				public Command
			{
			public:
				inline virtual ~Result() = default;
			};
			namespace Results
			{
				class ReturnInstance:
					public Result
				{
				public:
					virtual ~ReturnInstance() = default;
				public:
					virtual Reference<Instance> GetInstance() const = 0;
				};
			}
			class Argument:
				public Command
			{
			public:
				inline virtual ~Argument() = default;
			};
			namespace Arguments
			{
				class CopyInstance:
					public Argument
				{
				public:
					inline virtual ~CopyInstance() = default;
				public:
					inline virtual Reference<Instance> GetInstance() const = 0;
				};
				class CopyResultInstance:
					public Argument
				{
				public:
					inline virtual ~CopyResultInstance() = default;
				public:
					inline virtual Reference<CallAlgorithm> GetAlgorithmCall() const = 0;
					inline virtual Reference<Instance> GetInstance() const = 0;
				};
			}
			class CreateInstance:
				public Command
			{
			public:
				inline virtual ~CreateInstance() = default;
			public:
				inline virtual Reference<Instance> GetInstance() const = 0;
			};
			class ReturnInstance:
				public Command
			{
			public:
				inline virtual ~ReturnInstance() = default;
			public:
				inline virtual Reference<Instance> GetInstance() const = 0;
			};
			class CallAlgorithm:
				public Command
			{
			public:
				inline virtual ~CallAlgorithm() = default;
			public:
				inline virtual Reference<Result> GetResult() const = 0;
			};
			class CallBraceAlgorithm:
				public CallAlgorithm
			{
			public:
				using Arguments = Vector<Reference<Argument>>;
			public:
				inline virtual ~CallBraceAlgorithm() = default;
			public:
				inline virtual Reference<Algorithms::Brace> GetAlgorithm() const = 0;
				inline virtual Arguments GetArguments() const = 0;
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




















