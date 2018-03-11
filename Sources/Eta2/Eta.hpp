#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Eta2
	{
		class Entity
		{
		public:
			virtual ~Entity() = default;
		};
		
		class Type:
			public Entity
		{
		public:
			virtual ~Type() override = default;
		};
		class Algorithm:
			public Entity
		{
		public:
			class Result;
			class Argument;
			class Command;
		public:
			using Arguments = Vector<Reference<Argument>>;
			using Commands = Vector<Reference<Command>>;
		public:
			virtual ~Algorithm() override = default;
		public:
			virtual Reference<Result> GetResult() const = 0;
			virtual Arguments GetArguments() const = 0;
			virtual Commands GetCommands() const = 0;
		};
#pragma region Algorithm::Result
		class Algorithm::Result:
			public Entity
		{
		public:
			class Instance;
		public:
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Algorithm::Result::Instance
		class Algorithm::Result::Instance:
			public Algorithm::Result
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Type> GetType() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Argument
		class Algorithm::Argument:
			public Entity
		{
		public:
			class Instance;
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
			virtual Reference<Eta2::Instance> GetInstance() const = 0;
		};
#pragma endregion
		class Instance:
			public Entity
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Type> GetType() const = 0;
		};
#pragma region Algorithm::Command
		class Algorithm::Command:
			public Entity
		{
		public:
			class CreateInstance;
			class ReturnInstance;
			class CallAlgorithm;
		public:
			virtual ~Command() override = default;
		};
#pragma endregion
#pragma region Algorithm::Command::CreateInstance
		class Algorithm::Command::CreateInstance:
			public Command
		{
		public:
			virtual ~CreateInstance() override = default;
		public:
			virtual Reference<Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Command::ReturnInstance
		class Algorithm::Command::ReturnInstance:
			public Command
		{
		public:
			virtual ~ReturnInstance() override = default;
		public:
			virtual Reference<Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Command::CallAlgorithm
		class Algorithm::Command::CallAlgorithm:
			public Command
		{
		public:
			class Result;
			class Argument;
		public:
			using Arguments = Vector<Reference<Argument>>;
		public:
			virtual ~CallAlgorithm() override = default;
		public:
			virtual Reference<Algorithm> GetAlgorithm() const = 0;
			virtual Reference<Result> GetResult() const = 0;
			virtual Arguments GetArguments() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Command::CallAlgorithm::Result
		class Algorithm::Command::CallAlgorithm::Result:
			public Entity
		{
		public:
			class Instance;
		public:
			virtual ~Result() override = default;
		};
#pragma endregion
#pragma region Algorithm::Command::CallAlgorithm::Result::Instance
		class Algorithm::Command::CallAlgorithm::Result::Instance:
			public Entity
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta2::Instance> GetInstance() const = 0;
		};
#pragma endregion
#pragma region Algorithm::Command::CallAlgorithm::Argument
		class Algorithm::Command::CallAlgorithm::Argument:
			public Entity
		{
		public:
			class Instance;
		public:
			virtual ~Argument() override = default;
		};
#pragma endregion
#pragma region Algorithm::Command::CallAlgorithm::Argument::Instance
		class Algorithm::Command::CallAlgorithm::Argument::Instance:
			public Entity
		{
		public:
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta2::Instance> GetInstance() const = 0;
		};
#pragma endregion


		class Assembly:
			public Entity
		{
		public:
			using Types = Map<String, Reference<Type>>;
			using Algorithms = Map<String, Reference<Algorithm>>;
			using Instances = Map<String, Reference<Instance>>;
		public:
			virtual ~Assembly() override = default;
		public:
			virtual Types GetTypes() const = 0;
			virtual Algorithms GetAlgorithms() const = 0;
			virtual Instances GetInstances() const = 0;
		};

		class Parser:
			public Entity
		{
		protected:
			class InstanceWrapper;
			class Type;
			class Algorithm;
			class Instance;
		protected:
			class Assembly;
		protected:
			using It = String::iterator;
		public:
			virtual ~Parser() override = default;
		protected:
			inline It SkipDoubleQuotes(const String& source, It i) const;
			inline It SkipSingleQuotes(const String& source, It i) const;
			inline It SkipComment(const String& source, It i) const;
			inline It SkipWhitespaces(const String& source, It i) const;
			inline It SkipNumbers(const String& source, It i) const;
			inline String Clean(const String& input_) const;
		public:
			inline Reference<Assembly> Parse(const String& input_);
		};
#pragma region Parser::Type
		class Parser::Type:
			public Eta2::Type,
			public This<Type>
		{
		public:
			inline Type(const Reference<Type>& this_): This(this_)
			{
			}
			virtual ~Type() override = default;
		};
#pragma endregion
#pragma region Parser::Algorithm
		class Parser::Algorithm:
			public Eta2::Algorithm,
			public This<Algorithm>
		{
		public:
			class Result;
			class Argument;
			class Command;
		public:
			using Arguments = Vector<Reference<Argument>>;
			using Commands = Vector<Reference<Command>>;
		protected:
			const Reference<Result> result;
			const Arguments arguments;
			Commands commands;
		public:
			inline Algorithm(const Reference<Algorithm>& this_, const Reference<Result>& result_, const Arguments& arguments_): This(this_), result(result_), arguments(arguments_)
			{
			}
			virtual ~Algorithm() override = default;
		public:
			inline virtual Reference<Eta2::Algorithm::Result> GetResult() const override;
			inline virtual Eta2::Algorithm::Arguments GetArguments() const override;
			inline virtual Eta2::Algorithm::Commands GetCommands() const override;
			inline Reference<Result> GetResult2() const
			{
				return result;
			}
			inline Arguments GetArguments2() const
			{
				return arguments;
			}
			inline Commands GetCommands2() const
			{
				return commands;
			}
			inline void AppendCommand(const Reference<Command>& command_)
			{
				commands.push_back(command_);
			}
		};
#pragma endregion
#pragma region Parser::Instance
		class Parser::Instance:
			public Eta2::Instance,
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
			inline virtual Reference<Eta2::Type> GetType() const override
			{
				return type;
			}
			inline Reference<Type> GetType2() const
			{
				return type;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Result
		class Parser::Algorithm::Result:
			public Eta2::Algorithm::Result,
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
#pragma region Parser::Algorithm::Result::Instance
		class Parser::Algorithm::Result::Instance:
			public Result,
			public Eta2::Algorithm::Result::Instance
		{
		protected:
			const Reference<Type> type;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Type>& type_): Parser::Algorithm::Result(this_), type(type_)
			{
			}
			virtual ~Instance() override = default;
		public:
			virtual Reference<Eta2::Type> GetType() const override
			{
				return type;
			}
			Reference<Type> GetType2() const
			{
				return type;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Argument
		class Parser::Algorithm::Argument:
			public Eta2::Algorithm::Argument,
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
#pragma region Parser::Algorithm::Argument::Instance
		class Parser::Algorithm::Argument::Instance:
			public Eta2::Algorithm::Argument::Instance,
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
			virtual Reference<Eta2::Instance> GetInstance() const override
			{
				return instance;
			}
			Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command
		class Parser::Algorithm::Command:
			public Eta2::Algorithm::Command,
			public This<Command>
		{
		public:
			class CreateInstance;
			class ReturnInstance;
			class CallAlgorithm;
		public:
			inline Command(const Reference<Command>& this_):
				This(this_)
			{
			}
			virtual ~Command() override = default;
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CreateInstance
		class Parser::Algorithm::Command::CreateInstance:
			public Eta2::Algorithm::Command::CreateInstance,
			public Command
		{
		protected:
			const Reference<Instance> instance;
		public:
			inline CreateInstance(const Reference<CreateInstance>& this_, const Reference<Instance>& instance_): Command(this_), instance(instance_)
			{
			}
			virtual ~CreateInstance() override = default;
		public:
			virtual Reference<Eta2::Instance> GetInstance() const override
			{
				return instance;
			}
			virtual Reference<Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::ReturnInstance
		class Parser::Algorithm::Command::ReturnInstance:
			public Eta2::Algorithm::Command::ReturnInstance,
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
			virtual Reference<Eta2::Instance> GetInstance() const override
			{
				return instance;
			}
			virtual Reference<Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion
#pragma region Parser::Algorithm::Command::CallAlgorithm
		class Parser::Algorithm::Command::CallAlgorithm:
			public Eta2::Algorithm::Command::CallAlgorithm,
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
			inline virtual Reference<Eta2::Algorithm> GetAlgorithm() const override
			{
				return algorithm;
			}
			inline virtual Reference<Eta2::Algorithm::Command::CallAlgorithm::Result> GetResult() const override;
			inline virtual Eta2::Algorithm::Command::CallAlgorithm::Arguments GetArguments() const override;
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
			public Eta2::Algorithm::Command::CallAlgorithm::Result,
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
			public Eta2::Algorithm::Command::CallAlgorithm::Result::Instance,
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
			inline virtual Reference<Eta2::Instance> GetInstance() const override
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
			public Eta2::Algorithm::Command::CallAlgorithm::Argument,
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
			public Eta2::Algorithm::Command::CallAlgorithm::Argument::Instance,
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
			inline virtual Reference<Eta2::Instance> GetInstance() const override
			{
				return instance;
			}
			inline Reference<Parser::Instance> GetInstance2() const
			{
				return instance;
			}
		};
#pragma endregion

#pragma region Parser::Assembly
		class Parser::Assembly:
			public Eta2::Assembly,
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
			virtual Eta2::Assembly::Types GetTypes() const override
			{
				Eta2::Assembly::Types typesToReturn;

				for (auto &i : types)
				{
					typesToReturn[i.first] = i.second;
				}

				return Move(typesToReturn);
			}
			virtual Eta2::Assembly::Algorithms GetAlgorithms() const override
			{
				Eta2::Assembly::Algorithms algorithmsToReturn;

				for (auto &i : algorithms)
				{
					algorithmsToReturn[i.first] = i.second;
				}

				return Move(algorithmsToReturn);
			}
			virtual Eta2::Assembly::Instances GetInstances() const override
			{
				Eta2::Assembly::Instances instancesToReturn;

				for (auto &i : instances)
				{
					instancesToReturn[i.first] = i.second;
				}

				return Move(instancesToReturn);
			}
		};
#pragma endregion
	}
}


#pragma region Nu

#pragma region Eta2

#pragma region Parser

#pragma region Algorithm

#pragma region Command

#pragma region CallAlgorithm

Nu::Reference<Nu::Eta2::Algorithm::Command::CallAlgorithm::Result> Nu::Eta2::Parser::Algorithm::Command::CallAlgorithm::GetResult() const
{
	return result;
}
Nu::Eta2::Algorithm::Command::CallAlgorithm::Arguments Nu::Eta2::Parser::Algorithm::Command::CallAlgorithm::GetArguments() const
{
	Eta2::Algorithm::Command::CallAlgorithm::Arguments argumentsToReturn(arguments.size());

	for (Size i = 0; i < arguments.size(); ++i)
	{
		argumentsToReturn[i] = arguments[i];
	}

	return Move(argumentsToReturn);
}

#pragma endregion

#pragma endregion


Nu::Reference<Nu::Eta2::Algorithm::Result> Nu::Eta2::Parser::Algorithm::GetResult() const
{
	return result;
}
Nu::Eta2::Algorithm::Arguments Nu::Eta2::Parser::Algorithm::GetArguments() const
{
	Eta2::Algorithm::Arguments argumentsToReturn(arguments.size());

	for (Size i = 0; i < arguments.size(); ++i)
	{
		argumentsToReturn[i] = arguments[i];
	}

	return Move(argumentsToReturn);
}
Nu::Eta2::Algorithm::Commands Nu::Eta2::Parser::Algorithm::GetCommands() const
{
	Eta2::Algorithm::Commands commandsToReturn(commands.size());

	for (Size i = 0; i < commands.size(); ++i)
	{
		commandsToReturn[i] = commands[i];
	}

	return Move(commandsToReturn);
}

#pragma endregion


Nu::Eta2::Parser::It Nu::Eta2::Parser::SkipDoubleQuotes(const String& source, It i) const
{
	if (i != source.end() && *i == '"') // check and begin search
	{
		++i;
	}
	else
	{
		throw Exception();
	}

	while (true)
	{
		if (i != source.end())
		{
			auto v = *i;

			if (v == '\\') // skip screened double-quotes
			{
				auto j = i; ++j;

				if (j != source.end())
				{
					auto v2 = *j;

					if (v2 == '"') // skip screened double-quotes
					{
						i = j;
					}
				}
				else
				{
					throw Exception();
				}
			}
			else if (v == '"') // match found
			{
				++i;

				return i;
			}

			++i; // skip symbol
		}
		else
		{
			throw Exception();
		}
	}
}
Nu::Eta2::Parser::It Nu::Eta2::Parser::SkipSingleQuotes(const String& source, It i) const
{
	if (i != source.end() && *i == '\'') // check and begin search
	{
		++i;
	}
	else
	{
		throw Exception();
	}

	while (true)
	{
		if (i != source.end())
		{
			auto v = *i;

			if (v == '\\') // skip screened double-quotes
			{
				auto j = i; ++j;

				if (j != source.end())
				{
					auto v2 = *j;

					if (v2 == '\'') // skip screened double-quotes
					{
						i = j;
					}
				}
				else
				{
					throw Exception();
				}
			}
			else if (v == '\'') // match found
			{
				++i;

				return i;
			}

			++i; // skip symbol
		}
		else
		{
			throw Exception();
		}
	}
}
Nu::Eta2::Parser::It Nu::Eta2::Parser::SkipComment(const String& source, It i) const
{
	if (i != source.end() && *i == '#') // check and begin search
	{
		++i;
	}
	else
	{
		throw Exception();
	}

	while (true)
	{
		if (i != source.end())
		{
			auto v = *i;

			if (v == '\n')
			{
				++i;

				return i;
			}
			else
			{
				++i;
			}
		}
		else
		{
			return i;
		}
	}
}
Nu::Eta2::Parser::It Nu::Eta2::Parser::SkipWhitespaces(const String& source, It i) const
{
	while (i != source.end() && (*i == ' ' || *i == '\t' || *i == '\n' || *i == '\r'))
	{
		++i;
	}

	return i;
}
Nu::Eta2::Parser::It Nu::Eta2::Parser::SkipNumbers(const String& source, It i) const
{
	auto isNumber = [](const char& x)
	{
		return x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9';
	};

	while (i != source.end() && isNumber(*i))
	{
		++i;
	}

	return i;
}

Nu::String Nu::Eta2::Parser::Clean(const String& input_) const
{
	auto output = input_;

start:
	auto i = output.begin();

	while (i != output.end())
	{
		auto v = *i;

		if (v == '"')
		{
			i = SkipDoubleQuotes(output, i);
		}
		else if (v == '\'')
		{
			i = SkipSingleQuotes(output, i);
		}
		else if (v == '#')
		{
			auto j = SkipComment(output, i);

			output = String(output.begin(), i) + String(j, output.end());

			i = j;

			goto start;
		}
		else
		{
			++i;
		}
	}

	return output;
}

Nu::Reference<Nu::Eta2::Parser::Assembly> Nu::Eta2::Parser::Parse(const String& input_)
{
	auto match = [](const String& value, const String& source, It& i)
	{
		auto o = i;

		for (auto j = value.begin(); j != value.end(); ++j)
		{
			if (i != source.end())
			{
				if (*i != *j)
				{
					i = o;

					return false;
				}

				++i;
			}
			else
			{
				i = o;

				return false;
			}
		}

		return true;
	};

	Map<String, Reference<Type>> types;

	auto matchType = [&](const String& source, It& i) -> Reference<Type>
	{
		auto v = *i;

		if (v == '"')
		{
			auto j = SkipDoubleQuotes(source, i);
			auto name = String(i, j);
			auto it = types.find(name);

			if (it != types.end())
			{
				auto type = (*it).second;

				i = j;

				return type;
			}
			else
			{
				throw Exception();
			}
		}

		return nullptr;
	};

	Map<String, Reference<Algorithm>> algorithms;

	auto matchAlgorithm = [&](const String& source, It& i) -> Reference<Algorithm>
	{
		auto v = *i;

		if (v == '\'')
		{
			auto j = SkipSingleQuotes(source, i);
			auto name = String(i, j);
			auto it = algorithms.find(name);

			if (it != algorithms.end())
			{
				auto algorithms = (*it).second;

				i = j;

				return algorithms;
			}
			else
			{
				throw Exception();
			}
		}

		return nullptr;
	};

	Map<String, Reference<Instance>> instances;

	auto parseInstanceName = [&](const String& source, It& i) -> Reference<String>
	{
		if (i != source.end() && *i == '$')
		{
			auto o = i;

			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(o, j);

			i = j;
			
			return MakeReference<String>(name);
		}
		else
		{
			return nullptr;
		}
	};
	auto parseInstance = [&](const String& source, It& i, const Reference<Type>& type_) -> Reference<Instance>
	{
		if (i != source.end() && *i == '$')
		{
			auto o = i;

			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(o, j);
			auto instance = Make<Instance>(type_);

			instances[name] = instance;

			i = j;

			return instance;
		}
		else
		{
			return nullptr;
		}
	};
	auto parseExistedInstance = [&](const String& source, It& i) -> Reference<Instance>
	{
		if (i != source.end() && *i == '$')
		{
			auto o = i;

			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(o, j);
			auto it = instances.find(name);

			if (it != instances.end())
			{
				auto instance = (*it).second;

				i = j;

				return instance;
			}
			else
			{
				throw Exception();
			}
		}
		else
		{
			return nullptr;
		}
	};

	auto source = Clean(input_);
	auto i = source.begin();

	while (i != source.end())
	{
		i = SkipWhitespaces(source, i);
		
		if (i != source.end())
		{
			auto v = *i;

			if (match("schema", source, i))
			{
				i = SkipWhitespaces(source, i);

				if (i != source.end() && *i == '"')
				{
					auto j = i;
					
					i = SkipDoubleQuotes(source, i);

					auto typeName = String(j, i);

					i = SkipWhitespaces(source, i);
					
					if (i != source.end() && *i == ';')
					{
						++i;

						auto type = Make<Type>();

						if (types.find(typeName) != types.end())
						{
							throw Exception();
						}

						types[typeName] = type;
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
			else if (auto type = matchType(source, i))
			{
				i = SkipWhitespaces(source, i);

				if (i != source.end() && *i == ':')
				{
					++i;
					
					i = SkipWhitespaces(source, i);

					if (i != source.end() && *i == '{')
					{
						++i;
						
						i = SkipWhitespaces(source, i);

						if (i != source.end() && *i == '}')
						{
							++i;
							
							i = SkipWhitespaces(source, i);

							if (i != source.end() && *i == ';')
							{
								++i;

								// TODO: schema definition
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
			else if (match("algorithm", source, i))
			{
				i = SkipWhitespaces(source, i);

				if (auto resultType = matchType(source, i))
				{
					i = SkipWhitespaces(source, i);

					if (i != source.end() && *i == '\'')
					{
						auto j = i;

						i = SkipSingleQuotes(source, i);

						auto algorithmName = String(j, i);

						i = SkipWhitespaces(source, i);

						if (i != source.end() && *i == '(')
						{
							++i;

							Algorithm::Arguments arguments;
							
							while (true)
							{
								if (!arguments.empty())
								{
									i = SkipWhitespaces(source, i);

									if (i != source.end() && *i == ',')
									{
										++i; // do nothing
									}
									else
									{
										break; // no arguments expected
									}
								}
								
								i = SkipWhitespaces(source, i);

								if (auto type = matchType(source, i))
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
							
							i = SkipWhitespaces(source, i);

							if (i != source.end() && *i == ')')
							{
								++i;

								i = SkipWhitespaces(source, i);
								
								if (i != source.end() && *i == ';')
								{
									++i;

									auto result = Make<Algorithm::Result::Instance>(resultType);
									auto algorithm = Make<Algorithm>(Cast<Algorithm::Result>(result), arguments);

									if (algorithms.find(algorithmName) != algorithms.end())
									{
										throw Exception();
									}
									
									algorithms[algorithmName] = algorithm;
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
			else if (auto algorithm = matchAlgorithm(source, i))
			{
				i = SkipWhitespaces(source, i);

				if (i != source.end() && *i == ':')
				{
					++i;

					i = SkipWhitespaces(source, i);

					if (i != source.end() && *i == '(')
					{
						++i;

						auto &expectedArguments = algorithm->GetArguments2();
						
						bool isFirstArgument = true;

						for (auto &expectedArgument : expectedArguments)
						{
							if (!isFirstArgument)
							{
								i = SkipWhitespaces(source, i);

								if (i != source.end() && *i == ',')
								{
									++i; // do nothing
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

							i = SkipWhitespaces(source, i);

							if (auto argumentInstance = UpCast<Algorithm::Argument::Instance>(expectedArgument))
							{
								auto instance = argumentInstance->GetInstance2();

								if (auto instanceName = parseInstanceName(source, i))
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

						i = SkipWhitespaces(source, i);

						if (i != source.end() && *i == ')')
						{
							++i;

							i = SkipWhitespaces(source, i);
							
							if (i != source.end() && *i == '{')
							{
								++i;

								auto parseCreateCommand = [&](const String& source, It& i) -> Reference<Algorithm::Command::CreateInstance>
								{
									auto o = i;

									if (auto name = parseInstanceName(source, i))
									{
										i = SkipWhitespaces(source, i);
										
										if (i != source.end() && *i == ':')
										{
											++i;

											i = SkipWhitespaces(source, i);

											if (match("create", source, i))
											{
												i = SkipWhitespaces(source, i);

												if (auto type = matchType(source, i))
												{
													i = SkipWhitespaces(source, i);

													if (i != source.end() && *i == ';')
													{
														++i;

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

									i = o;
									return nullptr;
								};
								auto parseCallCommand = [&](const String& source, It& i) -> Reference<Algorithm::Command::CallAlgorithm>
								{
									auto o = i;

									if (auto name = parseInstanceName(source, i))
									{
										i = SkipWhitespaces(source, i);

										if (i != source.end() && *i == ':')
										{
											++i;

											i = SkipWhitespaces(source, i);

											if (match("call", source, i))
											{
												i = SkipWhitespaces(source, i);
												
												if (auto algorithm = matchAlgorithm(source, i))
												{
													if (i != source.end() && *i == '(')
													{
														++i;

														i = SkipWhitespaces(source, i);

														// parce arguments
														Algorithm::Command::CallAlgorithm::Arguments arguments;
														auto &expectedArguments = algorithm->GetArguments2();

														for (auto &expectedArgument : expectedArguments)
														{
															if (!arguments.empty())
															{
																i = SkipWhitespaces(source, i);

																if (i != source.end() && *i == ',')
																{
																	++i; // do nothing
																}
																else
																{
																	throw Exception();
																}
															}

															i = SkipWhitespaces(source, i);

															if (auto instance = parseExistedInstance(source, i))
															{
																auto argument = Make<Algorithm::Command::CallAlgorithm::Argument::Instance>(instance);

																arguments.push_back(argument);
															}
															else
															{
																throw Exception();
															}
														}

														if (i != source.end() && *i == ')')
														{
															++i;

															i = SkipWhitespaces(source, i);

															if (i != source.end() && *i == ';')
															{
																++i;

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

									i = o;
									return nullptr;
								};
								auto parseReturnCommand = [&](const String& source, It& i) -> Reference<Algorithm::Command::ReturnInstance>
								{
									auto o = i;
									
									if (match("return", source, i))
									{
										i = SkipWhitespaces(source, i);
										
										if (auto instance = parseExistedInstance(source, i))
										{

											if (i != source.end() && *i == ';')
											{
												++i;
												
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

									i = o;
									return nullptr;
								};

								while (true)
								{
									i = SkipWhitespaces(source, i);

									if (auto create = parseCreateCommand(source, i))
									{
										algorithm->AppendCommand(create);
									}
									else if (auto call = parseCallCommand(source, i))
									{
										algorithm->AppendCommand(call);
									}
									else if (auto ret = parseReturnCommand(source, i))
									{
										algorithm->AppendCommand(ret);
									}
									else
									{
										break;
									}
								}

								i = SkipWhitespaces(source, i);

								if (i != source.end() && *i == '}')
								{
									++i;

									i = SkipWhitespaces(source, i);

									if (i != source.end() && *i == ';')
									{
										++i;
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
			else
			{
				throw Exception();
			}
		}
	}

	auto assembly = Make<Assembly>(types, algorithms, instances);
	
	return Move(assembly);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















