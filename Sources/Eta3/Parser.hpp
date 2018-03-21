#pragma once

#pragma region Include

#include "Header.hpp"
#include "Interface.hpp"

#pragma endregion


namespace Nu
{
	namespace Eta3
	{
		class Parser:
			public Entity
		{
		public:
			class Type;
			class Instance;
			class Executable;
			class Instruction;
			class Algorithm;
			class Command;
		public:
#pragma region Type
			class Type:
				public Eta3::Type,
				public This<Type>
			{
			public:
				inline Type(const Reference<Type>& this_): This(this_)
				{
				}
				virtual ~Type() override = default;
			};
#pragma endregion
#pragma region Instance
			class Instance:
				public Eta3::Instance,
				public This<Instance>
			{
			protected:
				const Reference<Type> type;
			public:
				inline Instance(const Reference<Instance>& this_, const Reference<Type>& type_): This(this_), type(type_)
				{
				}
				virtual ~Instance() override = default;
			public:
				inline virtual Reference<Eta3::Type> GetType() const override
				{
					return type;
				}
				inline Reference<Type> GetType2() const
				{
					return type;
				}
			};
#pragma endregion
#pragma region Executable
			class Executable:
				public Eta3::Executable,
				public This<Executable>
			{
			public:
				class Result;
				class Body;
			protected:
				const Reference<Result> result;
			public:
				inline Executable(const Reference<Executable>& this_, const Reference<Result>& result_): This(this_), result(result_)
				{
				}
				virtual ~Executable() override = default;
			public:
				inline virtual Reference<Eta3::Executable::Result> GetResult() const override;
				inline Reference<Result> GetResult2() const
				{
					return result;
				}
				// inline virtual Commands GetCommands() const override
				// {
				// 	throw NotImplementedException();
				// }
				// inline Commands GetCommands2() const
				// {
				// 	return commands;
				// }
			};
#pragma endregion
#pragma region Executable::Result
			class Executable::Result:
				public Eta3::Executable::Result,
				public This<Result>
			{
			public:
				class None;
				class Instance;
			public:
				inline Result(const Reference<Result>& this_): This(this_)
				{
				}
				virtual ~Result() = default;
			};
#pragma endregion
#pragma region Executable::Result::None
			class Executable::Result::None:
				public Eta3::Executable::Result::None,
				public Result
			{
			public:
				inline None(const Reference<None>& this_): Parser::Executable::Result(this_)
				{
				}
				virtual ~None() override = default;
			};
#pragma endregion
#pragma region Executable::Result::Instance
			class Executable::Result::Instance:
				public Eta3::Executable::Result::Instance,
				public Result
			{
			protected:
				const Reference<Type> type;
			public:
				inline Instance(const Reference<Instance>& this_, const Reference<Type>& type_): Parser::Executable::Result(this_), type(type_)
				{
				}
				virtual ~Instance() override = default;
			public:
				inline virtual Reference<Eta3::Type> GetType() const override
				{
					return type;
				}
				inline Reference<Type> GetType2() const
				{
					return type;
				}
			};
#pragma endregion
#pragma region Executable::Body
			class Executable::Body:
				public Eta3::Executable::Body,
				public This<Body>
			{
			public:
				class Internal;
				class CommandList;
			public:
				inline Body(const Reference<Body>& this_): This(this_)
				{
				}
				virtual ~Body() = default;
			};
#pragma endregion
#pragma region Executable::Body::Internal
			class Executable::Body::Internal:
				public Eta3::Executable::Body::Internal,
				public Body
			{
			public:
				inline Internal(const Reference<Internal>& this_): Parser::Executable::Body(this_)
				{
				}
				virtual ~Internal() override = default;
			};
#pragma endregion
#pragma region Executable::Body::CommandList
			class Executable::Body::CommandList:
				public Eta3::Executable::Body::CommandList,
				public Body
			{
			public:
				using Commands = Vector<Reference<Command>>;
			protected:
				const Commands commands;
			public:
				inline CommandList(const Reference<CommandList>& this_, const Commands& commands_ = Commands()): Parser::Executable::Body(this_), commands(commands_)
				{
				}
				virtual ~CommandList() override = default;
			public:
				inline virtual Eta3::Executable::Body::CommandList::Commands GetCommands() const override;
				inline Commands GetCommands2() const
				{
					return commands;
				}
			};
#pragma endregion
#pragma region Instruction
			class Instruction:
				public Eta3::Instruction,
				public Executable
			{
			public:
				inline Instruction(const Reference<Instruction>& this_, const Reference<Parser::Executable::Result>& result_): Parser::Executable(this_, result_)
				{
				}
				virtual ~Instruction() override = default;
			public:
				inline virtual Reference<Eta3::Executable::Result> GetResult() const override
				{
					return Parser::Executable::GetResult();
				}
				// inline virtual Eta3::Executable::Commands GetCommands() const override
				// {
				// 	return Parser::Executable::GetCommands();
				// }
			};
#pragma endregion
#pragma region Algorithm
			class Algorithm:
				public Eta3::Algorithm,
				public Executable
			{
			public:
				class Argument;
			public:
				using Arguments = Vector<Reference<Argument>>;
				// using Commands = Vector<Reference<Command>>;
			protected:
				const Arguments arguments;
				// Commands commands;
			public:
				inline Algorithm(const Reference<Algorithm>& this_, const Reference<Parser::Executable::Result>& result_, const Arguments& arguments_): Parser::Executable(this_, result_), arguments(arguments_)
				{
				}
				virtual ~Algorithm() override = default;
			public:
				inline virtual Reference<Eta3::Executable::Result> GetResult() const override
				{
					return Parser::Executable::GetResult();
				}
				// inline virtual Eta3::Executable::Commands GetCommands() const override
				// {
				// 	return Parser::Executable::GetCommands();
				// }
				inline virtual Eta3::Algorithm::Arguments GetArguments() const override;
				// inline virtual Eta3::Algorithm::Commands GetCommands() const override;
				// inline Arguments GetArguments2() const
				// {
				// 	return arguments;
				// }
				// inline void AppendCommand(const Reference<Command>& command_)
				// {
				// 	commands.push_back(command_);
				// }
			};
#pragma endregion
#pragma region Algorithm::Argument
			class Algorithm::Argument:
				public Eta3::Algorithm::Argument,
				public This<Argument>
			{
			public:
				class Instance;
				class Instruction;
			public:
				inline Argument(const Reference<Argument>& this_): This(this_)
				{
				}
				virtual ~Argument() override = default;
			};
#pragma endregion
#pragma region Algorithm::Argument::Instance
			class Algorithm::Argument::Instance:
				public Eta3::Algorithm::Argument::Instance,
				public Argument
			{
			protected:
				const Reference<Parser::Instance> instance;
			public:
				inline Instance(const Reference<Instance>& this_, const Reference<Parser::Instance>& instance_): Parser::Algorithm::Argument(this_), instance(instance_)
				{
				}
				virtual ~Instance() override = default;
			public:
				virtual Reference<Eta3::Instance> GetInstance() const override
				{
					return instance;
				}
				inline Reference<Parser::Instance> GetInstance2() const
				{
					return instance;
				}
			};
#pragma endregion
#pragma region Algorithm::Argument::Instruction
			class Algorithm::Argument::Instruction:
				public Eta3::Algorithm::Argument::Instruction,
				public Argument
			{
			protected:
				const Reference<Parser::Instruction> instruction;
			public:
				inline Instruction(const Reference<Instruction>& this_, const Reference<Parser::Instruction>& instruction_): Parser::Algorithm::Argument(this_), instruction(instruction_)
				{
				}
				virtual ~Instruction() override = default;
			public:
				virtual Reference<Eta3::Instruction> GetInstruction() const override
				{
					return instruction;
				}
				inline Reference<Parser::Instruction> GetInstruction2() const
				{
					return instruction;
				}
			};
#pragma endregion
#pragma region Command
			class Command:
				public Eta3::Command,
				public This<Command>
			{
			public:
				class CreateInstance;
				class DeleteInstance;
				class Return;
				class Call;
			public:
				inline Command(const Reference<Command>& this_): This(this_)
				{
				}
				virtual ~Command() override = default;
			public:
			};
#pragma endregion
#pragma region Command::CreateInstance
			class Command::CreateInstance:
				public Eta3::Command::CreateInstance,
				public Command
			{
			protected:
				const Reference<Instance> instance;
			public:
				inline CreateInstance(const Reference<CreateInstance>& this_, const Reference<Instance>& instance_): Parser::Command(this_), instance(instance_)
				{
				}
				virtual ~CreateInstance() override = default;
			public:
				virtual Reference<Eta3::Instance> GetInstance() const override
				{
					return instance;
				}
				inline Reference<Instance> GetInstance2() const
				{
					return instance;
				}
			};
#pragma endregion
#pragma region Command::DeleteInstance
			class Command::DeleteInstance:
				public Eta3::Command::DeleteInstance,
				public Command
			{
			protected:
				const Reference<Instance> instance;
			public:
				inline DeleteInstance(const Reference<DeleteInstance>& this_, const Reference<Instance>& instance_): Parser::Command(this_), instance(instance_)
				{
				}
				virtual ~DeleteInstance() override = default;
			public:
				virtual Reference<Eta3::Instance> GetInstance() const override
				{
					return instance;
				}
				inline Reference<Instance> GetInstance2() const
				{
					return instance;
				}
			};
#pragma endregion
#pragma region Command::Return
		class Command::Return:
			public Eta3::Command::Return,
			public Command
		{
		public:
			class None;
			class Instance;
		protected:
			const Reference<Executable> executable;
		public:
			inline Return(const Reference<Return>& this_, const Reference<Executable>& executable_): Parser::Command(this_), executable(executable_)
			{
			}
			virtual ~Return() override = default;
		public:
			inline virtual Reference<Eta3::Executable> GetExecutable() const override
			{
				return executable;
			}
			inline Reference<Executable> GetExecutable2() const
			{
				return executable;
			}
		};
#pragma endregion
#pragma region Command::Return::None
		class Command::Return::None:
			public Eta3::Command::Return::None,
			public Return
		{
		public:
			inline None(const Reference<None>& this_, const Reference<Executable>& executable_): Parser::Command::Return(this_, executable_)
			{
			}
			virtual ~None() override = default;
		public:
			inline virtual Reference<Eta3::Executable> GetExecutable() const override
			{
				return Parser::Command::Return::GetExecutable();
			}
		};
#pragma endregion
#pragma region Command::Return::Instance
		class Command::Return::Instance:
			public Eta3::Command::Return::Instance,
			public Return
		{
		public:
			const Reference<Parser::Instance> instance;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Parser::Instance>& instance_, const Reference<Executable>& executable_): Parser::Command::Return(this_, executable_), instance(instance_)
			{
			}
			virtual ~Instance() override = default;
		public:
			inline virtual Reference<Eta3::Executable> GetExecutable() const override
			{
				return Parser::Command::Return::GetExecutable();
			}
			inline virtual Reference<Eta3::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Command::Call
		class Command::Call:
			public Eta3::Command::Call,
			public Command
		{
		public:
			class Executable;
			class Instruction;
		public:
			inline Call(const Reference<Call>& this_): Parser::Command(this_)
			{
			}
			virtual ~Call() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable
		class Command::Call::Executable:
			public Eta3::Command::Call::Executable,
			public Parser::Command::Call
		{
		public:
			class Result;
		protected:
			const Reference<Result> result;
		public:
			inline Executable(const Reference<Executable>& this_, const Reference<Result> result_): Parser::Command::Call(this_), result(result_)
			{
			}
			virtual ~Executable() override = default;
		public:
			inline virtual Reference<Eta3::Command::Call::Executable::Result> GetResult() const override;
			inline Reference<Result> GetResult2() const
			{
				return result;
			}
		};
#pragma endregion
#pragma region Command::Call::Executable::Result
		class Command::Call::Executable::Result:
			public Eta3::Command::Call::Executable::Result,
			public This<Result>
		{
		public:
			class None;
			class Instance;
		public:
			inline Result(const Reference<Result>& this_): This(this_)
			{
			}
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable::Result::None
		class Command::Call::Executable::Result::None:
			public Eta3::Command::Call::Executable::Result::None,
			public Parser::Command::Call::Executable::Result
		{
		public:
			inline None(const Reference<None>& this_): Parser::Command::Call::Executable::Result(this_)
			{
			}
			virtual ~None() override = default;
		};
#pragma endregion
#pragma region Command::Call::Executable::Result::Instance
		class Command::Call::Executable::Result::Instance:
			public Eta3::Command::Call::Executable::Result::Instance,
			public Parser::Command::Call::Executable::Result
		{
		protected:
			const Reference<Parser::Instance> instance;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Parser::Instance>& instance_): Parser::Command::Call::Executable::Result(this_), instance(instance_)
			{
			}
			virtual ~Instance() override = default;
		public:
			inline virtual Reference<Eta3::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Command::Call::Instruction
		class Command::Call::Instruction:
			public Eta3::Command::Call::Instruction,
			public Parser::Command::Call::Executable
		{
		protected:
			const Reference<Parser::Instruction> instruction;
		public:
			inline Instruction(const Reference<Instruction>& this_, const Reference<Parser::Instruction>& instruction_, const Reference<Parser::Command::Call::Executable::Result> result_): Parser::Command::Call::Executable(this_, result_), instruction(instruction_)
			{
			}
			virtual ~Instruction() override = default;
		public:
			inline virtual Reference<Eta3::Command::Call::Executable::Result> GetResult() const override
			{
				return Parser::Command::Call::Executable::GetResult();
			}
			inline virtual Reference<Eta3::Instruction> GetInstruction() const override
			{
				return instruction;
			}
			inline Reference<Parser::Instruction> GetInstruction2() const
			{
				return instruction;
			}
		};
#pragma endregion
		public:
			using Lookup = Map<String, Reference<Unit>>;
		protected:
			class Assembly;
		protected:
			using It = String::iterator;
		public:
			static inline bool IsMatch(const String& value_, const String& source_, It& it_);
			static inline void Match(const String& value_, const String& source_, It& it_);
			static inline Reference<String> IsMatchSingleQuotes(const String& source_, It& it_);
			static inline String MatchSingleQuotes(const String& source_, It& it_);
			static inline It SkipUntilDoubleQuotes(const String& source_, const It& it_);
			static inline It SkipUntilSingleQuotes(const String& source_, const It& it_);
			static inline It SkipUntilPageBreak(const String& source_, const It& it_);
			static inline bool IsWhitespace(const char& x_);
			static inline It SkipWhitespaces(const String& source_, const It& it_);
			static inline bool IsNumber(const char& x_);
			static inline It SkipNumbers(const String& source_, const It& it_);
		public:
			static inline String Clean(const String& input_);
		public:
			static inline Reference<Pair<String, Reference<Type>>> ParseTypeDeclaration(const String& source_, It& it_);
			static inline Reference<Type> ParseTypeDefinition(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Pair<String, Reference<Instance>>> ParseInstanceDeclaration(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Executable::Result> MatchExecutableResult(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Algorithm::Argument> ParseAlgorithmArgument(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Pair<String, Reference<Instruction>>> ParseInstructionDeclaration(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Pair<String, Reference<Algorithm>>> ParseAlgorithmDeclaration(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Executable::Body> MatchExecutableBody(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Pair<Reference<Instruction>, Reference<Executable::Body>>> ParseInstructionDefinition(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Pair<Reference<Algorithm>, Reference<Executable::Body>>> ParseAlgorithmDefinition(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::CreateInstance> ParseCreateInstanceCommand(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::DeleteInstance> ParseDeleteInstanceCommand(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::Return::None> ParseNoneReturnInstanceCommand(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::Return::Instance> ParseReturnInstanceCommand(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::Call::Instruction> ParseNoneInstructionCallCommand(const String& source_, It& it_, const Lookup& lookup_);
			static inline Reference<Command::Call::Instruction> ParseInstructionCallCommand(const String& source_, It& it_, const Lookup& lookup_);
		protected:
			Map<String, Reference<Type>> types;
			Map<String, Reference<Instruction>> instructions;
			Map<String, Reference<Algorithm>> algorithms;
			Map<String, Reference<Instance>> instances;
		public:
			virtual ~Parser() override = default;
		protected:
			/*inline bool Match(const String& value_, const String& source_, It& i_)
			{
				auto o = i_;

				for (auto j = value_.begin(); j != value_.end(); ++j)
				{
					if (i_ != source_.end())
					{
						if (*i_ != *j)
						{
							i_ = o;

							return false;
						}

						++i_;
					}
					else
					{
						i_ = o;

						return false;
					}
				}

				return true;
			}
			inline Reference<Type> MatchType(const String& source_, It& i_)
			{
				auto v = *i_;

				if (v == '"')
				{
					auto j = SkipDoubleQuotes(source_, i_);
					auto name = String(i_, j);
					auto it = types.find(name);

					if (it != types.end())
					{
						auto type = (*it).second;

						i_ = j;

						return type;
					}
					else
					{
						throw Exception();
					}
				}

				return nullptr;
			}
			inline Reference<Algorithm> MatchAlgorithm(const String& source_, It& i_)
			{
				if (i_ != source_.end())
				{
					auto v = *i_;

					if (v == '\'')
					{
						auto j = SkipSingleQuotes(source_, i_);
						auto name = String(i_, j);
						auto it = algorithms.find(name);

						if (it != algorithms.end())
						{
							auto algorithms = (*it).second;

							i_ = j;

							return algorithms;
						}
						else
						{
							throw Exception();
						}
					}
				}

				return nullptr;
			}
			inline Reference<Instance> ParseInstance(const String& source_, It& i_, const Reference<Type>& type_)
			{
				if (auto name = ParseInstanceName(source_, i_))
				{
					auto instance = Make<Instance>(type_);

					instances[*name] = instance;

					return instance;
				}

				return nullptr;
			}
			inline Reference<Instance> ParseExistedInstance(const String& source_, It& i_)
			{
				if (auto name = ParseInstanceName(source_, i_))
				{
					auto it = instances.find(*name);

					if (it != instances.end())
					{
						auto instance = (*it).second;

						return instance;
					}
					else
					{
						throw Exception();
					}
				}

				return nullptr;
			}
			inline Reference<String> ParseInstanceName(const String& source_, It& i_)
			{
				if (i_ != source_.end() && *i_ == '$')
				{
					auto o = i_;

					++i_;

					auto j = SkipNumbers(source_, i_);
					auto name = String(o, j);

					i_ = j;

					return MakeReference<String>(name);
				}
				else
				{
					return nullptr;
				}
			}
			inline Reference<String> ParseInstructionName(const String& source_, It& i_)
			{
				if (i_ != source_.end() && *i_ == '%')
				{
					auto o = i_;

					++i_;

					auto j = SkipNumbers(source_, i_);
					auto name = String(o, j);

					i_ = j;

					return MakeReference<String>(name);
				}
				else
				{
					return nullptr;
				}
			}
			inline bool ParseTypeDeclaration(const String& source_, It& i_)
			{
				if (Match("schema", source_, i_))
				{
					i_ = SkipWhitespaces(source_, i_);

					if (i_ != source_.end() && *i_ == '"')
					{
						auto j = i_;

						i_ = SkipDoubleQuotes(source_, i_);

						auto typeName = String(j, i_);

						i_ = SkipWhitespaces(source_, i_);

						if (i_ != source_.end() && *i_ == ';')
						{
							++i_;

							auto type = Make<Type>();

							if (types.find(typeName) != types.end())
							{
								throw Exception();
							}

							types[typeName] = type;

							return true;
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						throw Exception();
					}
				}

				return false;
			}
			inline Reference<Type> ParseTypeDefinition(const String& source_, It& i_)
			{
				if (auto type = MatchType(source_, i_))
				{
					i_ = SkipWhitespaces(source_, i_);

					if (i_ != source_.end() && *i_ == ':')
					{
						++i_;

						i_ = SkipWhitespaces(source_, i_);

						if (i_ != source_.end() && *i_ == '{')
						{
							++i_;

							i_ = SkipWhitespaces(source_, i_);

							if (i_ != source_.end() && *i_ == '}')
							{
								++i_;

								i_ = SkipWhitespaces(source_, i_);

								if (i_ != source_.end() && *i_ == ';')
								{
									++i_;

									// TODO: schema definition

									return type;
								}
								else
								{
									throw Exception();
								}
							}
							else
							{
								throw Exception();
							}
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						throw Exception();
					}
				}

				return nullptr;
			}
			inline bool ParseAlgorithmDeclaration(const String& source_, It& i_);
			inline Reference<Algorithm> ParseAlgorithmDefinition(const String& source_, It& i_);
			inline Reference<Eta3::Algorithm::Command::CreateInstance> ParseCreateInstanceCommand(const String& source_, It& i_);*/
		public:
			inline Reference<Assembly> Parse(const String& input_);
		};
/*#pragma region Parser::Algorithm::Command::ReturnInstance
		class Parser::Algorithm::Command::ReturnInstance:
			public Eta3::Algorithm::Command::ReturnInstance,
			public Command
		{
		protected:
			const Reference<Instance> instance;
		public:
			inline ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Instance>& instance_): Command(this_), instance(instance_)
			{
			}
			virtual ~ReturnInstance() override = default;
		public:
			virtual Reference<Eta3::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm
		class Parser::Algorithm::Command::CallAlgorithm:
			public Eta3::Algorithm::Command::CallAlgorithm,
			public Command
		{
		public:
			class Result;
			class Argument;
		public:
			using Arguments = Vector<Reference<Argument>>;
		protected:
			const Reference<Algorithm> algorithm;
			const Reference<Result> result;
			const Arguments arguments;
		public:
			inline CallAlgorithm(const Reference<CallAlgorithm>& this_, const Reference<Algorithm>& algorithm_, const Reference<Result>& result_, const Arguments& arguments_): Parser::Algorithm::Command(this_), algorithm(algorithm_), result(result_), arguments(arguments_)
			{
			}
			virtual ~CallAlgorithm() override = default;
		public:
			inline virtual Reference<Eta3::Algorithm> GetAlgorithm() const override
			{
				return algorithm;
			}
			inline virtual Reference<Eta3::Algorithm::Command::CallAlgorithm::Result> GetResult() const override;
			inline virtual Eta3::Algorithm::Command::CallAlgorithm::Arguments GetArguments() const override;
			inline Reference<Algorithm> GetAlgorithm2() const
			{
				return algorithm;
			}
			inline Reference<Result> GetResult2() const
			{
				return result;
			}
			inline Arguments GetArguments2() const
			{
				return arguments;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm::Result
		class Parser::Algorithm::Command::CallAlgorithm::Result:
			public Eta3::Algorithm::Command::CallAlgorithm::Result,
			public This<Result>
		{
		public:
			class Instance;
		public:
			inline Result(const Reference<Result>& this_): This(this_)
			{
			}
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm::Result::Instance
		class Parser::Algorithm::Command::CallAlgorithm::Result::Instance:
			public Eta3::Algorithm::Command::CallAlgorithm::Result::Instance,
			public Result
		{
		protected:
			const Reference<Parser::Instance> instance;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Parser::Instance>& instance_): Result(this_), instance(instance_)
			{
			}
			virtual ~Instance() override = default;
		public:
			inline virtual Reference<Eta3::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm::Argument
		class Parser::Algorithm::Command::CallAlgorithm::Argument:
			public Eta3::Algorithm::Command::CallAlgorithm::Argument,
			public This<Argument>
		{
		public:
			class Instance;
		public:
			inline Argument(const Reference<Argument>& this_): This(this_)
			{
			}
			virtual ~Argument() override = default;
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm::Argument::Instance
		class Parser::Algorithm::Command::CallAlgorithm::Argument::Instance:
			public Eta3::Algorithm::Command::CallAlgorithm::Argument::Instance,
			public Argument
		{
		protected:
			const Reference<Parser::Instance> instance;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Parser::Instance>& instance_): Argument(this_), instance(instance_)
			{
			}
			virtual ~Instance() override = default;
		public:
			inline virtual Reference<Eta3::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::Block
		class Parser::Algorithm::Command::Block:
			public Eta3::Algorithm::Command::Block,
			public Command
		{
		protected:
			Algorithm::Commands commands;
		public:
			inline Block(const Reference<Block>& this_, const Reference<Instance>& instance_): Algorithm::Command(this_)
			{
			}
			virtual ~Block() override = default;
		public:
			inline virtual Eta3::Algorithm::Commands GetCommands() const override
			{
				Eta3::Algorithm::Commands result(commands.size());

				for (Size i = 0; i < commands.size(); ++i)
				{
					result[i] = commands[i];
				}

				return Move(result);
			}
			inline Algorithm::Commands GetCommands2() const
			{
				return commands;
			}
		};
#pragma endregion

#pragma region Parser::Assembly
		class Parser::Assembly:
			public Eta3::Assembly,
			public This<Assembly>
		{
		public:
			using Types = Map<String, Reference<Type>>;
			using Algorithms = Map<String, Reference<Algorithm>>;
			using Instances = Map<String, Reference<Instance>>;
		protected:
			const Types types;
			const Algorithms algorithms;
			const Instances instances;
		public:
			inline Assembly(const Reference<Assembly>& this_, const Types& types_, const Algorithms& algorithms_, const Instances& instances_): This(this_), types(types_), algorithms(algorithms_), instances(instances_)
			{
			}
			virtual ~Assembly() override = default;
		public:
			virtual Eta3::Assembly::Types GetTypes() const override
			{
				Eta3::Assembly::Types typesToReturn;

				for (auto &i : types)
				{
					typesToReturn[i.first] = i.second;
				}

				return Move(typesToReturn);
			}
			virtual Eta3::Assembly::Algorithms GetAlgorithms() const override
			{
				Eta3::Assembly::Algorithms algorithmsToReturn;

				for (auto &i : algorithms)
				{
					algorithmsToReturn[i.first] = i.second;
				}

				return Move(algorithmsToReturn);
			}
			virtual Eta3::Assembly::Instances GetInstances() const override
			{
				Eta3::Assembly::Instances instancesToReturn;

				for (auto &i : instances)
				{
					instancesToReturn[i.first] = i.second;
				}

				return Move(instancesToReturn);
			}
		};
#pragma endregion*/
	}
}


#pragma region Nu

#pragma region Eta3

/*
#pragma region Parser

#pragma region Algorithm

#pragma region Command

#pragma region CallAlgorithm

Nu::Reference<Nu::Eta3::Algorithm::Command::CallAlgorithm::Result> Nu::Eta3::Parser::Algorithm::Command::CallAlgorithm::GetResult() const
{
	return result;
}
Nu::Eta3::Algorithm::Command::CallAlgorithm::Arguments Nu::Eta3::Parser::Algorithm::Command::CallAlgorithm::GetArguments() const
{
	Eta3::Algorithm::Command::CallAlgorithm::Arguments argumentsToReturn(arguments.size());

	for (Size i = 0; i < arguments.size(); ++i)
	{
		argumentsToReturn[i] = arguments[i];
	}

	return Move(argumentsToReturn);
}

#pragma endregion

#pragma endregion


Nu::Reference<Nu::Eta3::Algorithm::Result> Nu::Eta3::Parser::Algorithm::GetResult() const
{
	return result;
}
Nu::Eta3::Algorithm::Arguments Nu::Eta3::Parser::Algorithm::GetArguments() const
{
	Eta3::Algorithm::Arguments argumentsToReturn(arguments.size());

	for (Size i = 0; i < arguments.size(); ++i)
	{
		argumentsToReturn[i] = arguments[i];
	}

	return Move(argumentsToReturn);
}
Nu::Eta3::Algorithm::Commands Nu::Eta3::Parser::Algorithm::GetCommands() const
{
	Eta3::Algorithm::Commands commandsToReturn(commands.size());

	for (Size i = 0; i < commands.size(); ++i)
	{
		commandsToReturn[i] = commands[i];
	}

	return Move(commandsToReturn);
}

#pragma endregion

#pragma region Instruction

Nu::Reference<Nu::Eta3::Instruction::Result> Nu::Eta3::Parser::Instruction::GetResult() const
{
	return result;
}
Nu::Eta3::Instruction::Commands Nu::Eta3::Parser::Instruction::GetCommands() const
{
	Eta3::Instruction::Commands commandsToReturn(commands.size());

	for (Size i = 0; i < commands.size(); ++i)
	{
		commandsToReturn[i] = commands[i];
	}

	return Move(commandsToReturn);
}

#pragma endregion*/

#pragma region Parser

#pragma region Executable

#pragma region Body

#pragma region CommandList

Nu::Eta3::Executable::Body::CommandList::Commands Nu::Eta3::Parser::Executable::Body::CommandList::GetCommands() const
{
	Eta3::Executable::Body::CommandList::Commands commandsToReturn(commands.size());

	for (Size i = 0; i < commands.size(); ++i)
	{
		commandsToReturn[i] = commands[i];
	}

	return Move(commandsToReturn);
}

#pragma endregion

#pragma endregion


Nu::Reference<Nu::Eta3::Executable::Result> Nu::Eta3::Parser::Executable::GetResult() const
{
	return result;
}

#pragma endregion

#pragma region Algorithm

Nu::Eta3::Algorithm::Arguments Nu::Eta3::Parser::Algorithm::GetArguments() const
{
	Eta3::Algorithm::Arguments argumentsToReturn(arguments.size());

	for (Size i = 0; i < arguments.size(); ++i)
	{
		argumentsToReturn[i] = arguments[i];
	}

	return Move(argumentsToReturn);
}

#pragma endregion

#pragma region Command

#pragma region Call

#pragma region Executable

Nu::Reference<Nu::Eta3::Command::Call::Executable::Result> Nu::Eta3::Parser::Command::Call::Executable::GetResult() const
{
	return result;
}

#pragma endregion

#pragma endregion

#pragma endregion


bool Nu::Eta3::Parser::IsMatch(const String& value_, const String& source_, It& it_)
{
	auto o = it_;

	for (auto &j : value_)
	{
		if (it_ == source_.end() || *it_ != j)
		{
			it_ = o;

			return false;
		}

		++it_;
	}

	return true;
}
void Nu::Eta3::Parser::Match(const String& value_, const String& source_, It& it_)
{
	if (!IsMatch(value_, source_, it_))
	{
		throw Exception();
	}
}
Nu::Reference<Nu::String> Nu::Eta3::Parser::IsMatchSingleQuotes(const String& source_, It& it_)
{
	auto o = it_;

	if (IsMatch("'", source_, it_))
	{
		it_ = SkipUntilSingleQuotes(source_, it_);

		auto value = String(o, it_);

		return MakeReference<String>(value);
	}

	return nullptr;
}
Nu::String Nu::Eta3::Parser::MatchSingleQuotes(const String& source_, It& it_)
{
	if (auto value = IsMatchSingleQuotes(source_, it_))
	{
		return *value;
	}

	throw Exception();
}
Nu::Eta3::Parser::It Nu::Eta3::Parser::SkipUntilDoubleQuotes(const String& source_, const It& it_)
{
	auto it = it_;

	while (it != source_.end())
	{
		if (IsMatch("\\\"", source_, it)); // skip screened symbols
		else if (IsMatch("\"", source_, it))
		{
			return it;
		}

		++it;
	}

	throw Exception("Unexpected end of input");
}
Nu::Eta3::Parser::It Nu::Eta3::Parser::SkipUntilSingleQuotes(const String& source_, const It& it_)
{
	auto it = it_;

	while (it != source_.end())
	{
		if (IsMatch("\\'", source_, it)); // skip screened symbols
		else if (IsMatch("'", source_, it))
		{
			return it;
		}

		++it;
	}

	throw Exception("Unexpected end of input");
}
Nu::Eta3::Parser::It Nu::Eta3::Parser::SkipUntilPageBreak(const String& source_, const It& it_)
{
	auto it = it_;

	while (it != source_.end())
	{
		if (IsMatch("\n", source_, it))
		{
			return it;
		}
		else
		{
			++it;
		}
	}

	throw Exception("Unexpected end of input");
}
bool Nu::Eta3::Parser::IsWhitespace(const char& x_)
{
	return
		x_ == ' ' ||
		x_ == '\t' ||
		x_ == '\n' ||
		x_ == '\r';
}
Nu::Eta3::Parser::It Nu::Eta3::Parser::SkipWhitespaces(const String& source_, const It& it_)
{
	auto it = it_;

	while (it != source_.end() && IsWhitespace(*it))
	{
		++it;
	}

	return it;
}
bool Nu::Eta3::Parser::IsNumber(const char& x_)
{
	return
		x_ == '0' ||
		x_ == '1' ||
		x_ == '2' ||
		x_ == '3' ||
		x_ == '4' ||
		x_ == '5' ||
		x_ == '6' ||
		x_ == '7' ||
		x_ == '8' ||
		x_ == '9';
}
Nu::Eta3::Parser::It Nu::Eta3::Parser::SkipNumbers(const String& source_, const It& it_)
{
	auto it = it_;

	while (it != source_.end() && IsNumber(*it))
	{
		++it;
	}

	return it;
}

Nu::String Nu::Eta3::Parser::Clean(const String& input_)
{
	auto output = input_;

start:
	auto i = output.begin();

	while (i != output.end())
	{
		auto o = i;

		if (IsMatch("\"", output, i))
		{
			i = SkipUntilDoubleQuotes(output, i);
		}
		else if (IsMatch("'", output, i))
		{
			i = SkipUntilSingleQuotes(output, i);
		}
		else if (IsMatch("#", output, i))
		{
			auto j = SkipUntilPageBreak(output, i);
			
			output = String(output.begin(), o) + String(j, output.end());

			goto start;
		}
		else
		{
			++i;
		}
	}

	return output;
}

Nu::Reference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Type>>> Nu::Eta3::Parser::ParseTypeDeclaration(const String& source_, It& it_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("type", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);

		it = SkipWhitespaces(source_, it);

		Match(";", source_, it);

		it_ = it;

		auto type = Make<Type>();

		return MakeReference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Type>>>(name, type);
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Type> Nu::Eta3::Parser::ParseTypeDefinition(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (auto name = IsMatchSingleQuotes(source_, it))
	{
		auto unitIt = lookup_.find(*name);

		if (unitIt != lookup_.end())
		{
			auto unit = (*unitIt).second;
			
			if (auto type = UpCast<Type>(unit))
			{
				it = SkipWhitespaces(source_, it);
			
				Match(":", source_, it);
			
				it = SkipWhitespaces(source_, it);
			
				if (!IsMatch("internal", source_, it))
				{
					Match("{", source_, it);

					it = SkipWhitespaces(source_, it);

					Match("}", source_, it);
				}
			
				it = SkipWhitespaces(source_, it);

				Match(";", source_, it);

				it_ = it;

				return type;
			}
		}
	}

	return nullptr;
}
Nu::Reference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Instance>>> Nu::Eta3::Parser::ParseInstanceDeclaration(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("instance", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);

		if (lookup_.find(name) != lookup_.end())
		{
			throw Exception();
		}

		it = SkipWhitespaces(source_, it);

		auto typeName = MatchSingleQuotes(source_, it);
		auto unitIt = lookup_.find(typeName);

		if (unitIt == lookup_.end())
		{
			throw Exception();
		}
		
		auto unit = (*unitIt).second;
		auto type = UpCast<Type>(unit);

		if (type == nullptr)
		{
			throw Exception();
		}

		it = SkipWhitespaces(source_, it);
		
		Match(";", source_, it);

		it_ = it;

		auto instance = Make<Instance>(type);

		return MakeReference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Instance>>>(name, instance);
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Executable::Result> Nu::Eta3::Parser::MatchExecutableResult(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("none", source_, it))
	{
		auto result = Make<Executable::Result::None>();

		it_ = it;

		return result;
	}
	else
	{
		auto typeName = MatchSingleQuotes(source_, it);
		auto unitIt = lookup_.find(typeName);

		if (unitIt == lookup_.end())
		{
			throw Exception();
		}

		auto unit = (*unitIt).second;
		auto type = UpCast<Type>(unit);

		if (type == nullptr)
		{
			throw Exception();
		}

		auto result = Make<Executable::Result::Instance>(type);

		it_ = it;

		return result;
	}
}
Nu::Reference<Nu::Eta3::Parser::Algorithm::Argument> Nu::Eta3::Parser::ParseAlgorithmArgument(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = it_;

	if (auto name = IsMatchSingleQuotes(source_, it))
	{
		auto unitIt = lookup_.find(*name);

		if (unitIt == lookup_.end())
		{
			return nullptr; // TODO: throw exception?
		}

		auto unit = (*unitIt).second;

		if (auto instruction = UpCast<Instruction>(unit))
		{
			auto argument = Make<Algorithm::Argument::Instruction>(instruction);

			it_ = it;

			return argument;
		}

		auto instanceIt = lookup_.find(*name);

		if (auto instance = UpCast<Instance>(unit))
		{
			auto argument = Make<Algorithm::Argument::Instance>(instance);
			
			it_ = it;

			return argument;
		}
	}

	return nullptr;
}
Nu::Reference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Instruction>>> Nu::Eta3::Parser::ParseInstructionDeclaration(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("instruction", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);
		auto result = MatchExecutableResult(source_, it, lookup_);

		it = SkipWhitespaces(source_, it);
		
		Match(";", source_, it);

		it_ = it;

		auto instruction = Make<Instruction>(result);

		return MakeReference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Instruction>>>(name, instruction);
	}

	return nullptr;
}
Nu::Reference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Algorithm>>> Nu::Eta3::Parser::ParseAlgorithmDeclaration(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("algorithm", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);
		auto result = MatchExecutableResult(source_, it, lookup_);

		it = SkipWhitespaces(source_, it);

		Match("(", source_, it);

		Algorithm::Arguments arguments;

		while (true)
		{
			it = SkipWhitespaces(source_, it);
			
			if (!arguments.empty())
			{
				if (IsMatch(",", source_, it))
				{
					it = SkipWhitespaces(source_, it);
				}
				else
				{
					break;
				}
			}

			if (auto argument = ParseAlgorithmArgument(source_, it, lookup_))
			{
				arguments.push_back(argument);
			}
			else
			{
				break;
			}
		}
		// TODO: arguments

		it = SkipWhitespaces(source_, it);
		
		Match(")", source_, it);

		it = SkipWhitespaces(source_, it);
		
		Match(";", source_, it);

		it_ = it;

		auto algorithm = Make<Algorithm>(result, arguments);

		return MakeReference<Nu::Pair<Nu::String, Nu::Reference<Nu::Eta3::Parser::Algorithm>>>(name, algorithm);
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Executable::Body> Nu::Eta3::Parser::MatchExecutableBody(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("internal", source_, it))
	{
		auto body = Make<Executable::Body::Internal>();

		it_ = it;

		return body;
	}
	else
	{
		Match("{", source_, it);
		
		Executable::Body::CommandList::Commands commands;

		while (true)
		{
			if (auto command = ParseCreateInstanceCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else if (auto command = ParseDeleteInstanceCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else if (auto command = ParseNoneReturnInstanceCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else if (auto command = ParseReturnInstanceCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else if (auto command = ParseNoneInstructionCallCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else if (auto command = ParseInstructionCallCommand(source_, it, lookup_))
			{
				commands.push_back(command);
			}
			else
			{
				break;
			}
		}
		// TODO: content

		it = SkipWhitespaces(source_, it);

		Match("}", source_, it);
			
		auto body = Make<Executable::Body::CommandList>();

		it_ = it;

		return body;
	}

	return nullptr;
}
Nu::Reference<Nu::Pair<Nu::Reference<Nu::Eta3::Parser::Instruction>, Nu::Reference<Nu::Eta3::Parser::Executable::Body>>> Nu::Eta3::Parser::ParseInstructionDefinition(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (auto name = IsMatchSingleQuotes(source_, it))
	{
		auto unitIt = lookup_.find(*name);

		if (unitIt != lookup_.end())
		{
			auto unit = (*unitIt).second;

			if (auto instruction = UpCast<Instruction>(unit))
			{
				it = SkipWhitespaces(source_, it);

				Match(":", source_, it);

				auto body = MatchExecutableBody(source_, it, lookup_);

				it = SkipWhitespaces(source_, it);

				Match(";", source_, it);

				it_ = it;

				return MakeReference<Pair<Reference<Instruction>, Reference<Executable::Body>>>(instruction, body);
			}
		}
	}

	return nullptr;
}
Nu::Reference<Nu::Pair<Nu::Reference<Nu::Eta3::Parser::Algorithm>, Nu::Reference<Nu::Eta3::Parser::Executable::Body>>> Nu::Eta3::Parser::ParseAlgorithmDefinition(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (auto name = IsMatchSingleQuotes(source_, it))
	{
		auto unitIt = lookup_.find(*name);

		if (unitIt != lookup_.end())
		{
			auto unit = (*unitIt).second;

			if (auto algorithm = UpCast<Algorithm>(unit))
			{
				it = SkipWhitespaces(source_, it);

				Match(":", source_, it);

				auto body = MatchExecutableBody(source_, it, lookup_);

				it = SkipWhitespaces(source_, it);

				Match(";", source_, it);

				it_ = it;

				return MakeReference<Pair<Reference<Algorithm>, Reference<Executable::Body>>>(algorithm, body);
			}
		}
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Command::CreateInstance> Nu::Eta3::Parser::ParseCreateInstanceCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("create", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);
		auto unitIt = lookup_.find(name);

		if (unitIt == lookup_.end())
		{
			throw Exception();
		}

		auto unit = (*unitIt).second;
		auto instance = UpCast<Instance>(unit);

		if (instance == nullptr)
		{
			throw Exception();
		}

		it = SkipWhitespaces(source_, it);

		Match(";", source_, it);

		auto command = Make<Command::CreateInstance>(instance);

		it_ = it;

		return command;
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Command::DeleteInstance> Nu::Eta3::Parser::ParseDeleteInstanceCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("delete", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = MatchSingleQuotes(source_, it);
		auto unitIt = lookup_.find(name);

		if (unitIt == lookup_.end())
		{
			throw Exception();
		}

		auto unit = (*unitIt).second;
		auto instance = UpCast<Instance>(unit);

		if (instance == nullptr)
		{
			throw Exception();
		}

		it = SkipWhitespaces(source_, it);

		Match(";", source_, it);

		auto command = Make<Command::DeleteInstance>(instance);

		it_ = it;

		return command;
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Command::Return::None> Nu::Eta3::Parser::ParseNoneReturnInstanceCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("return", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		if (!IsMatch("from", source_, it))
		{
			return nullptr;
		}

		it = SkipWhitespaces(source_, it);
		
		auto name2 = MatchSingleQuotes(source_, it);
		auto unit2It = lookup_.find(name2);

		if (unit2It == lookup_.end())
		{
			throw Exception();
		}

		auto unit2 = (*unit2It).second;
		auto executable = UpCast<Executable>(unit2);

		if (executable == nullptr)
		{
			throw Exception();
		}

		auto expectedResult = UpCast<Executable::Result::None>(executable->GetResult2());

		if (!expectedResult)
		{
			throw Exception();
		}

		Match(";", source_, it);

		auto command = Make<Command::Return::None>(executable);

		it_ = it;

		return command;
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Command::Return::Instance> Nu::Eta3::Parser::ParseReturnInstanceCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);

	if (IsMatch("return", source_, it))
	{
		it = SkipWhitespaces(source_, it);

		auto name = IsMatchSingleQuotes(source_, it);

		if (!name)
		{
			return nullptr;
		}

		auto unitIt = lookup_.find(*name);

		if (unitIt == lookup_.end())
		{
			throw Exception();
		}

		auto unit = (*unitIt).second;
		auto instance = UpCast<Instance>(unit);

		if (instance == nullptr)
		{
			throw Exception();
		}

		it = SkipWhitespaces(source_, it);

		Match("from", source_, it);

		it = SkipWhitespaces(source_, it);
		
		auto name2 = MatchSingleQuotes(source_, it);
		auto unit2It = lookup_.find(name2);

		if (unit2It == lookup_.end())
		{
			throw Exception();
		}

		auto unit2 = (*unit2It).second;
		auto executable = UpCast<Executable>(unit2);

		if (executable == nullptr)
		{
			throw Exception();
		}

		auto expectedResult = UpCast<Executable::Result::Instance>(executable->GetResult2());

		if (!expectedResult)
		{
			throw Exception();
		}
		if (expectedResult->GetType2() != instance->GetType2())
		{
			throw Exception();
		}

		Match(";", source_, it);

		auto command = Make<Command::Return::Instance>(instance, executable);

		it_ = it;

		return command;
	}

	return nullptr;
}
Nu::Reference<Nu::Eta3::Parser::Command::Call::Instruction> Nu::Eta3::Parser::ParseNoneInstructionCallCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);
	
	if (!IsMatch("call", source_, it))
	{
		return nullptr;
	}

	it = SkipWhitespaces(source_, it);

	auto instructionName = IsMatchSingleQuotes(source_, it);

	if (!instructionName)
	{
		return nullptr;
	}

	auto instructionUnitIt = lookup_.find(*instructionName);

	if (instructionUnitIt == lookup_.end())
	{
		return nullptr;
	}

	auto instructionUnit = (*instructionUnitIt).second;
	auto instruction = UpCast<Instruction>(instructionUnit);

	if (!instruction)
	{
		return nullptr;
	}

	auto expectedResult = UpCast<Executable::Result::None>(instruction->GetResult2());

	if (!expectedResult)
	{
		throw Exception();
	}

	it = SkipWhitespaces(source_, it);

	Match(";", source_, it);

	auto result = Make<Command::Call::Executable::Result::None>();
	auto call = Make<Command::Call::Instruction>(instruction, result);

	it_ = it;

	return call;
}
Nu::Reference<Nu::Eta3::Parser::Command::Call::Instruction> Nu::Eta3::Parser::ParseInstructionCallCommand(const String& source_, It& it_, const Lookup& lookup_)
{
	auto it = SkipWhitespaces(source_, it_);
	
	auto instanceName = IsMatchSingleQuotes(source_, it);

	if (!instanceName)
	{
		return nullptr;
	}

	auto instanceUnitIt = lookup_.find(*instanceName);

	if (instanceUnitIt == lookup_.end())
	{
		return nullptr;
	}

	auto instanceUnit = (*instanceUnitIt).second;
	auto instance = UpCast<Instance>(instanceUnit);
	
	if (!instance)
	{
		return nullptr;
	}

	it = SkipWhitespaces(source_, it);
	
	if (!IsMatch(":", source_, it))
	{
		return nullptr;
	}
	
	it = SkipWhitespaces(source_, it);

	if (!IsMatch("call", source_, it))
	{
		return nullptr;
	}

	it = SkipWhitespaces(source_, it);

	auto instructionName = MatchSingleQuotes(source_, it);
	auto instructionUnitIt = lookup_.find(instructionName);

	if (instructionUnitIt == lookup_.end())
	{
		return nullptr;
	}

	auto instructionUnit = (*instructionUnitIt).second;
	auto instruction = UpCast<Instruction>(instructionUnit);

	if (!instruction)
	{
		return nullptr;
	}

	auto expectedResult = UpCast<Executable::Result::Instance>(instruction->GetResult2());

	if (!expectedResult)
	{
		throw Exception();
	}
	if (expectedResult->GetType2() != instance->GetType2())
	{
		throw Exception();
	}

	it = SkipWhitespaces(source_, it);

	Match(";", source_, it);

	auto result = Make<Command::Call::Executable::Result::Instance>(instance);
	auto call = Make<Command::Call::Instruction>(instruction, result);

	it_ = it;

	return call;
}

#pragma endregion

/*bool Nu::Eta3::Parser::ParseAlgorithmDeclaration(const String& source_, It& i_)
{
	if (Match("algorithm", source_, i_))
	{
		i_ = SkipWhitespaces(source_, i_);

		if (auto resultType = MatchType(source_, i_))
		{
			i_ = SkipWhitespaces(source_, i_);

			if (i_ != source_.end() && *i_ == '\'')
			{
				auto j = i_;

				i_ = SkipSingleQuotes(source_, i_);

				auto algorithmName = String(j, i_);

				i_ = SkipWhitespaces(source_, i_);

				if (i_ != source_.end() && *i_ == '(')
				{
					++i_;

					Algorithm::Arguments arguments;
							
					while (true)
					{
						if (!arguments.empty())
						{
							i_ = SkipWhitespaces(source_, i_);

							if (i_ != source_.end() && *i_ == ',')
							{
								++i_; // do nothing
							}
							else
							{
								break; // no arguments expected
							}
						}
								
						i_ = SkipWhitespaces(source_, i_);

						if (auto type = MatchType(source_, i_))
						{
							auto instance = Make<Instance>(type);
							auto argument = Make<Algorithm::Argument::Instance>(instance);

							arguments.push_back(argument);
						}
						else
						{
							break;
						}
					}
							
					i_ = SkipWhitespaces(source_, i_);

					if (i_ != source_.end() && *i_ == ')')
					{
						++i_;

						i_ = SkipWhitespaces(source_, i_);
								
						if (i_ != source_.end() && *i_ == ';')
						{
							++i_;

							auto result = Make<Algorithm::Result::Instance>(resultType);
							auto algorithm = Make<Algorithm>(Cast<Algorithm::Result>(result), arguments);

							if (algorithms.find(algorithmName) != algorithms.end())
							{
								throw Exception();
							}
									
							algorithms[algorithmName] = algorithm;

							return true;
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						throw Exception();
					}
				}
				else
				{
					throw Exception();
				}
			}
			else
			{
				throw Exception();
			}
		}
		else
		{
			throw Exception();
		}
	}

	return false;
}
Nu::Reference<Nu::Eta3::Parser::Algorithm> Nu::Eta3::Parser::ParseAlgorithmDefinition(const String& source_, It& i_)
{
	if (auto algorithm = MatchAlgorithm(source_, i_))
	{
		i_ = SkipWhitespaces(source_, i_);

		if (i_ != source_.end() && *i_ == ':')
		{
			++i_;

			i_ = SkipWhitespaces(source_, i_);

			if (i_ != source_.end() && *i_ == '(')
			{
				++i_;

				auto &expectedArguments = algorithm->GetArguments2();
						
				bool isFirstArgument = true;

				for (auto &expectedArgument : expectedArguments)
				{
					if (!isFirstArgument)
					{
						i_ = SkipWhitespaces(source_, i_);

						if (i_ != source_.end() && *i_ == ',')
						{
							++i_; // do nothing
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						isFirstArgument = false;
					}

					i_ = SkipWhitespaces(source_, i_);

					if (auto argumentInstance = UpCast<Algorithm::Argument::Instance>(expectedArgument))
					{
						auto instance = argumentInstance->GetInstance2();

						if (auto instanceName = ParseInstanceName(source_, i_))
						{
							auto name = *instanceName;

							if (instances.find(name) == instances.end())
							{
								instances[name] = instance;
							}
							else
							{
								throw Exception();
							}
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						throw Exception();
					}
				}

				// TODO: parse arguments

				i_ = SkipWhitespaces(source_, i_);

				if (i_ != source_.end() && *i_ == ')')
				{
					++i_;

					i_ = SkipWhitespaces(source_, i_);
							
					if (i_ != source_.end() && *i_ == '{')
					{
						++i_;

						auto parseCallCommand = [&](const String& source_, It& i_) -> Reference<Algorithm::Command::CallAlgorithm>
						{
							auto o = i_;

							if (auto name = ParseInstanceName(source_, i_))
							{
								i_ = SkipWhitespaces(source_, i_);

								if (i_ != source_.end() && *i_ == ':')
								{
									++i_;

									i_ = SkipWhitespaces(source_, i_);

									if (Match("call", source_, i_))
									{
										i_ = SkipWhitespaces(source_, i_);
												
										if (auto algorithm = MatchAlgorithm(source_, i_))
										{
											if (i_ != source_.end() && *i_ == '(')
											{
												++i_;

												i_ = SkipWhitespaces(source_, i_);

												// parce arguments
												Algorithm::Command::CallAlgorithm::Arguments arguments;
												auto &expectedArguments = algorithm->GetArguments2();

												for (auto &expectedArgument : expectedArguments)
												{
													if (!arguments.empty())
													{
														i_ = SkipWhitespaces(source_, i_);

														if (i_ != source_.end() && *i_ == ',')
														{
															++i_; // do nothing
														}
														else
														{
															throw Exception();
														}
													}

													i_ = SkipWhitespaces(source_, i_);

													if (auto instance = ParseExistedInstance(source_, i_))
													{
														auto argument = Make<Algorithm::Command::CallAlgorithm::Argument::Instance>(instance);

														arguments.push_back(argument);
													}
													else
													{
														throw Exception();
													}
												}

												if (i_ != source_.end() && *i_ == ')')
												{
													++i_;

													i_ = SkipWhitespaces(source_, i_);

													if (i_ != source_.end() && *i_ == ';')
													{
														++i_;

														if (auto instanceResult = UpCast<Algorithm::Result::Instance>(algorithm->GetResult2()))
														{
															auto instance = Make<Instance>(instanceResult->GetType2());
															auto result = Make<Algorithm::Command::CallAlgorithm::Result::Instance>(instance);
															auto call = Make<Algorithm::Command::CallAlgorithm>(algorithm, result, arguments);

															instances[*name] = instance;

															return call;
														}
														else
														{
															throw NotImplementedException();
														}
													}
													else
													{
														throw Exception();
													}
												}
												else
												{
													throw Exception();
												}
											}
											else
											{
												throw Exception();
											}
										}
										else
										{
											throw Exception();
										}
									}
								}
							}

							i_ = o;
							return nullptr;
						};
						auto parseReturnCommand = [&](const String& source_, It& i_) -> Reference<Algorithm::Command::ReturnInstance>
						{
							auto o = i_;
									
							if (Match("return", source_, i_))
							{
								i_ = SkipWhitespaces(source_, i_);
										
								if (auto instance = ParseExistedInstance(source_, i_))
								{

									if (i_ != source_.end() && *i_ == ';')
									{
										++i_;
												
										auto return_ = Make<Algorithm::Command::ReturnInstance>(instance);

										return return_;
									}
									else
									{
										throw Exception();
									}
								}
								else
								{
									throw Exception();
								}
							}

							i_ = o;
							return nullptr;
						};

						while (true)
						{
							i_ = SkipWhitespaces(source_, i_);

							if (auto create = UpCast<Algorithm::Command::CreateInstance>(ParseCreateInstanceCommand(source_, i_)))
							{
								algorithm->AppendCommand(create);
							}
							else if (auto call = parseCallCommand(source_, i_))
							{
								algorithm->AppendCommand(call);
							}
							else if (auto ret = parseReturnCommand(source_, i_))
							{
								algorithm->AppendCommand(ret);
							}
							else
							{
								break;
							}
						}

						i_ = SkipWhitespaces(source_, i_);

						if (i_ != source_.end() && *i_ == '}')
						{
							++i_;

							i_ = SkipWhitespaces(source_, i_);

							if (i_ != source_.end() && *i_ == ';')
							{
								++i_;

								return algorithm;
							}
							else
							{
								throw Exception();
							}
						}
						else
						{
							throw Exception();
						}
					}
					else
					{
						throw Exception();
					}
				}
				else
				{
					throw Exception();
				}
			}
			else
			{
				throw Exception();
			}
		}
		else
		{
			throw Exception();
		}
	}
				
	return nullptr;
}
Nu::Reference<Nu::Eta3::Algorithm::Command::CreateInstance> Nu::Eta3::Parser::ParseCreateInstanceCommand(const String& source_, It& i_)
{
	auto o = i_;

	if (auto name = ParseInstanceName(source_, i_))
	{
		i_ = SkipWhitespaces(source_, i_);

		if (i_ != source_.end() && *i_ == ':')
		{
			++i_;

			i_ = SkipWhitespaces(source_, i_);

			if (Match("create", source_, i_))
			{
				i_ = SkipWhitespaces(source_, i_);

				if (auto type = MatchType(source_, i_))
				{
					i_ = SkipWhitespaces(source_, i_);

					if (i_ != source_.end() && *i_ == ';')
					{
						++i_;

						auto instance = Make<Instance>(type);
						auto create = Make<Algorithm::Command::CreateInstance>(instance);

						instances[*name] = instance;

						return create;
					}
					else
					{
						throw Exception();
					}
				}
				else
				{
					throw Exception();
				}
			}
		}
	}

	i_ = o;
	return nullptr;
}


Nu::Reference<Nu::Eta3::Parser::Assembly> Nu::Eta3::Parser::Parse(const String& input_)
{
	auto source = Clean(input_);
	auto i = source.begin();

	while (i != source.end())
	{
		i = SkipWhitespaces(source, i);
		
		if (ParseTypeDeclaration(source, i));
		else if (auto type = ParseTypeDefinition(source, i));
		else if (ParseAlgorithmDeclaration(source, i));
		else if (auto algorithm = ParseAlgorithmDefinition(source, i));
		else
		{
			throw Exception();
		}
		
		i = SkipWhitespaces(source, i);
	}

	auto assembly = Make<Assembly>(types, algorithms, instances);
	
	return Move(assembly);
}*/

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















