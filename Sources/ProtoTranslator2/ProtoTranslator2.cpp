#pragma once

#pragma region Include

#include "Translator.hpp"
#include <../Cleaner/Cleaner.hpp>
#include <../Lexer2/Lexer.hpp>
#include <../Parser4/Parser.hpp>
#include <../Eta/Eta.hpp>
#include <../Translator-C/Translator-C.hpp>

#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <clocale>
#include <Windows.h>

#pragma endregion


namespace Nu
{
	namespace ProtoTranslator2
	{
		class Entity;
		class Schema;
		namespace Algorithms
		{
			class Brace;
		}
		class Translator;


		class Entity:
			public Nu::Entity
		{
		public:
			inline Entity(const Reference<Entity>& this_): Nu::Entity(this_)
			{
			}
			inline virtual ~Entity() override = default;
		};
		class Schema:
			public Entity,
			public Nu::Translator2::Schema
		{
		public:
			inline Schema(const Reference<Schema>& this_): Entity(this_)
			{
			}
			inline virtual ~Schema() override = default;
		};
		class Instance:
			public Entity,
			public Nu::Translator2::Instance
		{
		protected:
			const Link<Schema> schema;
		public:
			inline Instance(const Reference<Instance>& this_, const Reference<Schema>& schema_): Entity(this_), schema(schema_)
			{
			}
			inline virtual ~Instance() override = default;
		public:
			inline virtual Link<Translator2::Schema> GetSchema() const override
			{
				return schema;
			}
		};
		namespace Results
		{
			class ReturnInstance:
				public Entity,
				public Translator2::Results::ReturnInstance
			{
			protected:
				const Reference<Schema> schema;
			public:
				inline ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Schema>& schema_): Entity(this_), schema(schema_)
				{
				}
				inline virtual ~ReturnInstance() override = default;
			public:
				inline virtual Reference<Translator2::Schema> GetSchema() const override
				{
					return schema;
				}
			};
		}
		namespace Arguments
		{
			class CopyInstance:
				public Entity,
				public Translator2::Arguments::CopyInstance
			{
			protected:
				const Reference<Instance> instance;
			public:
				inline CopyInstance(const Reference<CopyInstance>& this_, const Reference<Instance>& instance_): Entity(this_), instance(instance_)
				{
				}
				inline virtual ~CopyInstance() override = default;
			public:
				inline virtual Reference<Translator2::Instance> GetInstance() const override
				{
					return instance;
				}
			};
			class Instruction:
				public Entity,
				public Translator2::Arguments::Instruction
			{
			public:
				inline Instruction(const Reference<Instruction>& this_): Entity(this_)
				{
				}
				inline virtual ~Instruction() override = default;
			};
		}
		namespace Algorithms
		{
			class Brace:
				public Entity,
				public Translator2::Algorithms::Brace
			{
			protected:
				Commands commands;
				const Reference<Translator2::Result> result;
				const Arguments arguments;
				const BraceType opening;
				const BraceType closing;
			public:
				inline Brace(const Reference<Brace>& this_, const Reference<Translator2::Result>& result_, const Arguments& arguments_, const BraceType& opening_, const BraceType& closing_): Entity(this_), result(result_), arguments(arguments_), opening(opening_), closing(closing_)
				{
				}
				inline virtual ~Brace() override = default;
			public:
				inline void SetCommands(const Commands& commands_)
				{
					commands = commands_;
				}
			public:
				inline virtual Reference<Translator2::Result> GetResult() const override
				{
					return result;
				}
				inline virtual Commands GetCommands() const override
				{
					return commands;
				}
				inline virtual BraceType GetOpening() const override
				{
					return opening;
				}
				inline virtual BraceType GetClosing() const override
				{
					return closing;
				}
				inline virtual Arguments GetArguments() const override
				{
					return arguments;
				}
			};
		}
		namespace Commands
		{
			namespace Results
			{
				class ReturnInstance:
					public Entity,
					public Translator2::Commands::Results::ReturnInstance
				{
				protected:
					const Reference<Instance> instance;
				public:
					inline ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Instance>& instance_): Entity(this_), instance(instance_)
					{
					}
					inline virtual ~ReturnInstance() override = default;
				public:
					inline virtual Reference<Translator2::Instance> GetInstance() const override
					{
						return instance;
					}
				};
			}
			namespace Arguments
			{
				class CopyInstance:
					public Entity,
					public Translator2::Commands::Arguments::CopyInstance
				{
				protected:
					const Reference<Instance> instance;
				public:
					inline CopyInstance(const Reference<CopyInstance>& this_, const Reference<Instance>& instance_): Entity(this_), instance(instance_)
					{
					}
					inline virtual ~CopyInstance() = default;
				public:
					inline virtual Reference<Translator2::Instance> GetInstance() const override
					{
						return instance;
					}
				};
				class CopyResultInstance:
					public Entity,
					public Translator2::Commands::Arguments::CopyResultInstance
				{
				protected:
					const Reference<Translator2::Commands::CallAlgorithm> callAlgorithm;
					const Reference<Translator2::Instance> instance;
				public:
					inline CopyResultInstance(const Reference<CopyResultInstance>& this_, const Reference<Translator2::Commands::CallAlgorithm>& call_): Entity(this_), callAlgorithm(call_),
						instance(UpCast<Results::ReturnInstance>(callAlgorithm->GetResult())
							? UpCast<Results::ReturnInstance>(callAlgorithm->GetResult())->GetInstance()
							: throw Exception() // TODO
						)
					{
					}
					inline virtual ~CopyResultInstance() = default;
				public:
					inline virtual Reference<Translator2::Commands::CallAlgorithm> GetAlgorithmCall() const override
					{
						return callAlgorithm;
					}
					inline virtual Reference<Translator2::Instance> GetInstance() const override
					{
						return instance;
					}
				};
			}
			class CreateInstance:
				public Entity,
				public Translator2::Commands::CreateInstance
			{
			protected:
				const Reference<Instance> instance;
			public:
				inline CreateInstance(const Reference<CreateInstance>& this_, const Reference<Instance>& instance_): Entity(this_), instance(instance_)
				{
				}
				inline virtual ~CreateInstance() override = default;
			public:
				inline virtual Reference<Translator2::Instance> GetInstance() const override
				{
					return instance;
				}
			};
			class ReturnInstance:
				public Entity,
				public Translator2::Commands::ReturnInstance
			{
			protected:
				const Reference<Instance> instance;
			public:
				inline ReturnInstance(const Reference<ReturnInstance>& this_, const Reference<Instance>& instance_): Entity(this_), instance(instance_)
				{
				}
				inline virtual ~ReturnInstance() override = default;
			public:
				inline virtual Reference<Translator2::Instance> GetInstance() const override
				{
					return instance;
				}
			};
			class CallBraceAlgorithm:
				public Entity,
				public Translator2::Commands::CallBraceAlgorithm
			{
			protected:
				const Reference<Translator2::Commands::Result> result;
				const Reference<Translator2::Algorithms::Brace> algorithm;
				const Arguments arguments;
			public:
				inline CallBraceAlgorithm(const Reference<CallBraceAlgorithm>& this_, const Reference<Translator2::Commands::Result>& result_, const Reference<Translator2::Algorithms::Brace> algorithm_, const Arguments& arguments_): Entity(this_), result(result_), algorithm(algorithm_), arguments(arguments_)
				{
				}
				inline virtual ~CallBraceAlgorithm() = default;
			public:
				inline virtual Reference<Translator2::Commands::Result> GetResult() const override
				{
					return result;
				}
				inline virtual Reference<Translator2::Algorithms::Brace> GetAlgorithm() const override
				{
					return algorithm;
				}
				inline virtual Arguments GetArguments() const override
				{
					return arguments;
				}
			};
		}
		class Translator
		{
		public:
			class Assembly
			{
			public:
				Vector<Reference<Translator2::Schema>> schemas;
				Vector<Reference<Translator2::Instance>> instances;
				Vector<Reference<Translator2::Algorithm>> algorithms;
				Map<Reference<Entity>, String> names;
				inline Assembly(
					const Vector<Reference<Translator2::Schema>>& schemas_,
					const Vector<Reference<Translator2::Instance>>& instances_,
					const Vector<Reference<Translator2::Algorithm>>& algorithms_,
					const Map<Reference<Entity>, String>& names_
				): schemas(schemas_), instances(instances_), algorithms(algorithms_), names(names_)
				{
				}
			};
		public:
			inline Translator2::Algorithms::Brace::BraceType Convert(Parsing4::Markers::Group::BraceType s)
			{
				if (s == Parsing4::Markers::Group::BraceType::Round)
				{
					return Translator2::Algorithms::Brace::BraceType::Round;
				}
				else if (s == Parsing4::Markers::Group::BraceType::Figure)
				{
					return Translator2::Algorithms::Brace::BraceType::Figure;
				}
				else if (s == Parsing4::Markers::Group::BraceType::Square)
				{
					return Translator2::Algorithms::Brace::BraceType::Square;
				}
				else
				{
					throw Exception();
				}
			}
		protected:
			Reference<Parsing4::Context> context;
			Vector<Reference<Parsing4::Scopes::Schema>> rawSchemas;
			Vector<Reference<Parsing4::Algorithm>> rawAlgorithms;
			Vector<Reference<Parsing4::Scopes::Instance>> rawInstances;
			Map<Reference<Parsing4::Scopes::Schema>, Reference<Schema>> schemasLookup;
			Map<Reference<Parsing4::Scopes::Instance>, Reference<Instance>> instancesLookup;
			Map<Reference<Parsing4::Algorithm>, Reference<Translator2::Algorithm>> algorithmsLookup;
			Map<Reference<Entity>, String> names;
		protected:
			inline void Collect(const Reference<Parsing4::Commands::AlgorithmCall>& call_)
			{
				if (auto &braceCall = UpCast<Parsing4::Commands::BraceAlgorithmCall>(call_))
				{
					auto instance = braceCall->GetResult();
					
					rawInstances.push_back(instance);

					auto &arguments = braceCall->GetArguments();

					for (auto &argument : arguments)
					{
						if (auto copyResult = UpCast<Parsing4::Commands::Arguments::CopyResultInstance>(argument))
						{
							auto instance = copyResult->GetInstance();
							
							rawInstances.push_back(instance);

							auto result = copyResult->GetResult();

							if (auto call = UpCast<Parsing4::Commands::AlgorithmCall>(result))
							{
								Collect(call);
							}
						}
					}
				}
			}
			inline void Collect(const Reference<Parsing4::Scopes::Body>& body_)
			{
				for (auto &marker : body_->GetMarkers())
				{
					if (auto &create = UpCast<Parsing4::Commands::CreateInstance>(marker))
					{
						auto instance = create->GetInstance();

						rawInstances.push_back(instance);
					}
					else if (auto &call = UpCast<Parsing4::Commands::AlgorithmCall>(marker))
					{
						Collect(call);
					}
					// else if (auto &braceCall = UpCast<Parsing4::Commands::BraceAlgorithmCall>(marker))
					// {
					// 	auto instance = braceCall->GetResult();
					// 
					// 	rawInstances.push_back(instance);
					// }
				}
			}
			inline void Collect(const Reference<Parsing4::Algorithm>& algorithm_)
			{
				if (auto body = context->GetBody(algorithm_))
				{
					Collect(body);
				}

				for (auto &marker : algorithm_->GetMarkers())
				{
					if (auto copy = UpCast<Parsing4::Arguments::CopyInstance>(marker))
					{
						auto instance = copy->GetInstance();

						rawInstances.push_back(instance);
					}
				}

				if (auto rawBraceAlgorithm = UpCast<Parsing4::Algorithms::Brace>(algorithm_))
				{
					if (std::find(rawAlgorithms.begin(), rawAlgorithms.end(), rawBraceAlgorithm) == rawAlgorithms.end())
					{
						rawAlgorithms.push_back(rawBraceAlgorithm);
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
			inline void Collect(const Reference<Parsing4::Scopes::Schema>& schema)
			{
				if (std::find(rawSchemas.begin(), rawSchemas.end(), schema) == rawSchemas.end())
				{
					rawSchemas.push_back(schema);
				}
				else
				{
					throw Exception();
				}
			}
			inline void Collect(const Reference<Parsing4::Scopes::Space>& space)
			{
				for (auto &marker : space->GetMarkers())
				{
					if (auto spaceR = UpCast<Parsing4::Markers::SpaceDeclaration>(marker))
					{
						auto space = spaceR->GetSpace();

						Collect(space);
					}
					else if (auto schemaD = UpCast<Parsing4::Markers::SchemaDeclaration>(marker))
					{
						auto schema = schemaD->GetSchema();

						Collect(schema);
					}
					else if (auto algorithmR = UpCast<Parsing4::Markers::AlgorithmDeclaration>(marker))
					{
						auto algorithm = algorithmR->GetAlgorithm();

						Collect(algorithm);
					}
				}
			}
			inline void Collect(const Reference<Parsing4::Scopes::Root>& root)
			{
				for (auto &marker : root->GetMarkers())
				{
					if (auto spaceR = UpCast<Parsing4::Markers::SpaceDeclaration>(marker))
					{
						auto space = spaceR->GetSpace();

						Collect(space);
					}
					else if (auto schemaD = UpCast<Parsing4::Markers::SchemaDeclaration>(marker))
					{
						auto schema = schemaD->GetSchema();

						Collect(schema);
					}
				}
			}
		protected:
			inline Reference<Translator2::Commands::CallAlgorithm> Perform(const Reference<Parsing4::Commands::AlgorithmCall>& rawAlgorithmCall_)
			{
				if (auto rawBraceAlgorithmCall = UpCast<Parsing4::Commands::BraceAlgorithmCall>(rawAlgorithmCall_))
				{
					auto instance = instancesLookup[rawBraceAlgorithmCall->GetResult()];
					auto result = Make<Commands::Results::ReturnInstance>(instance);

					Commands::CallBraceAlgorithm::Arguments arguments;
					{
						for (auto &raw : rawBraceAlgorithmCall->GetArguments())
						{
							if (auto copyR = UpCast<Parsing4::Commands::Arguments::CopyResultInstance>(raw))
							{
								auto res = copyR->GetResult();

								auto call = UpCast<Parsing4::Commands::AlgorithmCall>(res)
									? Perform(UpCast<Parsing4::Commands::AlgorithmCall>(res))
									: throw Exception(); // TODO

								auto argument = Make<Commands::Arguments::CopyResultInstance>(call);

								arguments.push_back(argument);
							}
							else if (auto copy = UpCast<Parsing4::Commands::Arguments::CopyInstance>(raw))
							{
								auto instance = instancesLookup[copy->GetInstance()];
								auto argument = Make<Commands::Arguments::CopyInstance>(instance);

								arguments.push_back(argument);
							}
						}
					}

					auto rawAlgorithm = rawBraceAlgorithmCall->GetAlgorithm();
					auto algorithm = UpCast<Algorithms::Brace>(algorithmsLookup[rawAlgorithm]);

					auto call = Make<Commands::CallBraceAlgorithm>(result, algorithm, arguments);

					return call;
				}
				else
				{
					throw Exception();
				}
			}
		public:
			inline Reference<Assembly> Translate(const String& source_)
			{
				auto cleaner = Make<Cleaning::Cleaner>();
				auto text = cleaner->Parse(source_);

				// std::cout << "clean: " << text << std::endl;

				auto lexer = Make<Lexing2::Lexer>();
				auto tokens = lexer->Parse(text);
				
				auto parser = Make<Parsing4::Parser>();
				context = parser->Parse(tokens);

				// collect all items
				rawSchemas.push_back(context->GetNoneSchema());
				
				Collect(context->GetRoot());

				// std::cout << "raw schemas: " << rawSchemas.size() << std::endl;
				// std::cout << "raw instances: " << rawInstances.size() << std::endl;
				// std::cout << "raw algorithms: " << rawAlgorithms.size() << std::endl;

				// create new items
				auto names = Map<Reference<Entity>, String>();
				auto schemas = Vector<Reference<Translator2::Schema>>();
				{
					for (auto &raw : rawSchemas)
					{
						auto schema = Make<Schema>();

						if (context->HasName(raw))
						{
							names[schema] = "\"" + context->GetFullUnitName(raw) + "\"";
						}

						schemas.push_back(schema);

						schemasLookup[raw] = schema;
					}
				}
				auto instances = Vector<Reference<Translator2::Instance>>();
				{
					for (auto &raw : rawInstances)
					{
						auto rawS = context->GetSchema(raw);
						auto schema = schemasLookup[rawS]; // TODO: check != nullptr
						auto instance = Make<Instance>(schema);

						if (context->HasName(raw))
						{
							names[instance] = context->GetUnitName(raw);
						}

						instances.push_back(instance);

						instancesLookup[raw] = instance;
					}
				}
				auto algorithms = Vector<Reference<Translator2::Algorithm>>();
				{
					for (auto &raw : rawAlgorithms)
					{
						if (auto rawB = UpCast<Parsing4::Algorithms::Brace>(raw))
						{
							auto result = Make<Results::ReturnInstance>(schemasLookup[rawB->GetResult()]);
						
							Algorithms::Brace::Arguments arguments;
							{
								for (auto &arg : context->GetArguments(rawB))
								{
									if (auto copy = UpCast<Parsing4::Arguments::CopyInstance>(arg))
									{
										auto instance = instancesLookup[copy->GetInstance()];
										auto copyArgument = Make<Arguments::CopyInstance>(instance);

										arguments.push_back(copyArgument);
									}
									else if (auto instruction = UpCast<Parsing4::Arguments::Instruction>(arg))
									{
										// TODO
										auto instructionArgument = Make<Arguments::Instruction>();

										arguments.push_back(instructionArgument);
									}
									else
									{
										throw Exception(); // TODO
									}
								}
							}

							auto algorithm = Make<Algorithms::Brace>(result, arguments, Convert(rawB->GetOpening()), Convert(rawB->GetClosing()));

							if (context->HasName(raw))
							{
								names[algorithm] = "'" + context->GetFullUnitName(raw) + "'";
							}

							algorithms.push_back(algorithm);

							algorithmsLookup[rawB] = algorithm;
						}
					}
				}
				
				// bodies
				for (auto &raw : rawAlgorithms)
				{
					if (auto rawB = UpCast<Parsing4::Algorithms::Brace>(raw))
					{
						Algorithms::Brace::Commands commands;
						{
							if (auto body = context->GetBody(rawB))
							{
								for (auto &marker : body->GetMarkers())
								{
									if (auto create = UpCast<Parsing4::Commands::CreateInstance>(marker))
									{
										auto instance = instancesLookup[create->GetInstance()];
										auto createInstance = Make<Commands::CreateInstance>(instance);

										commands.push_back(createInstance);
									}
									else if (auto returnC = UpCast<Parsing4::Commands::ReturnInstance>(marker))
									{
										auto instance = instancesLookup[returnC->GetInstance()];
										auto returnInstance = Make<Commands::ReturnInstance>(instance);

										commands.push_back(returnInstance);
									}
									else if (auto rawCall = UpCast<Parsing4::Commands::AlgorithmCall>(marker))
									{
										auto call = Perform(rawCall);
										
										commands.push_back(call);
									}
								}
							}
						}

						auto algorithm = algorithmsLookup[rawB];

						if (auto brace = UpCast<Algorithms::Brace>(algorithm))
						{
							brace->SetCommands(commands);
						}
						else
						{
							throw Exception();
						}
					}
				}

				//

				// std::cout << "schemas: " << schemas.size() << std::endl;
				// std::cout << "instances: " << instances.size() << std::endl;
				// std::cout << "algorithms: " << algorithms.size() << std::endl;

				return MakeReference<Assembly>(schemas, instances, algorithms, names);
			}
		};
	}
}


#pragma region Nu

#pragma region ProtoTranslator2

#pragma endregion

#pragma endregion

#pragma region
#pragma endregion


using namespace Nu;

using SchemasNames = Map<Reference<Translator2::Schema>, String>;
using InstancesNames = Map<Reference<Translator2::Instance>, String>;
using AlgorithmsNames = Map<Reference<Translator2::Algorithm>, String>;

void StringifyCall(String& output, const Reference<Translator2::Commands::CallAlgorithm>& call, SchemasNames& schemasNames, InstancesNames& instancesNames, AlgorithmsNames& algorithmsNames)
{
	if (auto callBrace = UpCast<Translator2::Commands::CallBraceAlgorithm>(call))
	{
		auto result = callBrace->GetResult();

		if (auto returnInstance = UpCast<Translator2::Commands::Results::ReturnInstance>(result))
		{
			auto instance = returnInstance->GetInstance();
			auto algorithm = callBrace->GetAlgorithm();
			String argumentsNames;
			{
				auto arguments = callBrace->GetArguments();

				bool t = false;

				for (auto &argument : arguments)
				{
					if (t)
					{
						argumentsNames += ", ";
					}
					else
					{
						t = true;
					}

					if (auto copyResult = UpCast<Translator2::Commands::Arguments::CopyResultInstance>(argument))
					{
						auto call = copyResult->GetAlgorithmCall();
						auto instance = copyResult->GetInstance();

						StringifyCall(output, call, schemasNames, instancesNames, algorithmsNames);
						
						argumentsNames += instancesNames[instance];
					}
					else if (auto copyInstance = UpCast<Translator2::Commands::Arguments::CopyInstance>(argument))
					{
						auto instance = copyInstance->GetInstance();

						argumentsNames += instancesNames[instance];
					}
					else
					{
						throw Exception();
					}
				}
			}

			output += "\t" + instancesNames[instance] + ": call " + algorithmsNames[algorithm] + "(" + argumentsNames + ");\n";
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


Nu::String Stringify(const Nu::Reference<Nu::ProtoTranslator2::Translator::Assembly>& assembly_)
{
	auto &schemas = assembly_->schemas;
	auto &instances = assembly_->instances;
	auto &algorithms = assembly_->algorithms;
	auto &names = assembly_->names;
	
	SchemasNames schemasNames;
	{
		for (auto &schema : schemas)
		{
			auto x = UpCast<ProtoTranslator2::Entity>(schema);

			if (names.find(x) != names.end()) // TODO: remove UpCast
			{
				schemasNames[schema] = names[x];
			}
			else
			{
				schemasNames[schema] = "\"schema #" + std::to_string(schemasNames.size()) + "\"";
			}
		}
	}
	InstancesNames instancesNames;
	{
		for (auto &instance : instances)
		{
			instancesNames[instance] = "$" + std::to_string(instancesNames.size());
		}
	}
	AlgorithmsNames algorithmsNames;
	{
		for (auto &algorithm : algorithms)
		{
			auto x = UpCast<ProtoTranslator2::Entity>(algorithm);

			if (names.find(x) != names.end()) // TODO: remove UpCast
			{
				algorithmsNames[algorithm] = names[x];
			}
			else
			{
				algorithmsNames[algorithm] = "'algorithm #" + std::to_string(algorithmsNames.size()) + "'";
			}
		}
	}

	String output;

	output += "# schemas declarations\n";

	for (auto &schema : schemas)
	{
		auto &name = schemasNames[schema];

		output += "schema " + name + ";\n";
	}

	output += "\n";
	
	output += "# schemas definitions\n";

	for (auto &schema : schemas)
	{
		auto &name = schemasNames[schema];

		output += name + ": {};\n";
	}

	output += "\n";
	
	output += "# algorithms declarations\n";

	for (auto &algorithm : algorithms)
	{
		auto &name = algorithmsNames[algorithm];
		auto result = algorithm->GetResult();
		auto resultName = ([&]()
		{
			if (auto returnInstance = UpCast<Translator2::Results::ReturnInstance>(result))
			{
				auto schema = returnInstance->GetSchema();

				return schemasNames[schema];
			}
			else
			{
				throw Exception();
			}
		})();
		String argumentsNames;
		{
			if (auto braceAlgorithm = UpCast<Translator2::Algorithms::Brace>(algorithm))
			{
				auto arguments = braceAlgorithm->GetArguments();

				bool t = false;

				for (auto &argument : arguments)
				{
					if (t)
					{
						argumentsNames += ", ";
					}
					else
					{
						t = true;
					}

					if (auto copyInstance = UpCast<Translator2::Arguments::CopyInstance>(argument))
					{
						auto schema = MakeReference(copyInstance->GetInstance()->GetSchema());

						argumentsNames += schemasNames[schema];
					}
					else if (auto instruction = UpCast<Translator2::Arguments::Instruction>(argument))
					{
						argumentsNames += "%"; // TODO
					}
					else
					{
						throw Exception();
					}
				}
			}
			else
			{
				throw Exception();
			}
		}

		output += "algorithm " + resultName + " " + name + "(" + argumentsNames + ");\n";
	}

	output += "\n";

	output += "# algorithms definitions\n";

	for (auto &algorithm : algorithms)
	{
		auto &name = algorithmsNames[algorithm];

		String argumentsNames;
		{
			if (auto braceAlgorithm = UpCast<Translator2::Algorithms::Brace>(algorithm))
			{
				auto arguments = braceAlgorithm->GetArguments();

				bool t = false;

				for (auto &argument : arguments)
				{
					if (t)
					{
						argumentsNames += ", ";
					}
					else
					{
						t = true;
					}

					if (auto copyInstance = UpCast<Translator2::Arguments::CopyInstance>(argument))
					{
						auto instance = copyInstance->GetInstance();

						argumentsNames += instancesNames[instance];
					}
					else if (auto instruction = UpCast<Translator2::Arguments::Instruction>(argument))
					{
						argumentsNames += "%"; // TODO
					}
					else
					{
						throw Exception();
					}
				}
			}
			else
			{
				throw Exception();
			}
		}

		output += name + ": (" + argumentsNames + ") {\n";

		auto commands = algorithm->GetCommands();

		for (auto &command : commands)
		{
			if (auto create = UpCast<Translator2::Commands::CreateInstance>(command))
			{
				auto instance = create->GetInstance();

				output += "\t" + instancesNames[instance] + ": create " + schemasNames[MakeReference(instance->GetSchema())] + ";\n";
			}
			else if (auto ret = UpCast<Translator2::Commands::ReturnInstance>(command))
			{
				auto instance = ret->GetInstance();

				output += "\treturn " + instancesNames[instance] + ";\n";
			}
			else if (auto call = UpCast<Translator2::Commands::CallAlgorithm>(command))
			{
				StringifyCall(output, call, schemasNames, instancesNames, algorithmsNames);
			}
			/*else if (auto callBrace = UpCast<Translator2::Commands::CallBraceAlgorithm>(command))
			{
				auto result = callBrace->GetResult();

				if (auto returnInstance = UpCast<Translator2::Commands::Results::ReturnInstance>(result))
				{
					auto instance = returnInstance->GetInstance();
					auto algorithm = callBrace->GetAlgorithm();
					String argumentsNames;
					{
						auto arguments = callBrace->GetArguments();

						bool t = false;

						for (auto &argument : arguments)
						{
							if (t)
							{
								argumentsNames += ", ";
							}
							else
							{
								t = true;
							}

							if (auto copyInstance = UpCast<Translator2::Commands::Arguments::CopyInstance>(argument))
							{
								auto instance = copyInstance->GetInstance();

								argumentsNames += instancesNames[instance];
							}
							else if (auto copyResult = UpCast<Translator2::Commands::Arguments::CopyResultInstance>(argument))
							{
								PerformNestedCall(output, copyResult);
							}
							else
							{
								throw Exception();
							}
						}
					}
					
					output += "\t" + instancesNames[instance] + ": call " + algorithmsNames[algorithm] + "(" + argumentsNames + ");\n";
				}
				else
				{
					throw Exception();
				}
			}*/
			/*else
			{
				throw Exception();
			}*/
		}

		output += "};\n";
	}

	output += "\n";

	return Move(output);
}


void wmain(int argc, wchar_t* argv[])
{
	// try
	{
		_setmode(_fileno(stdout), _O_WTEXT);

		Nu::Size totalFilesCount = argc > 1
			? static_cast<Nu::Size>(argc)-1
			: 0;

		std::wcout << L"total files count: " << totalFilesCount << std::endl;

		Nu::Vector<Nu::WString> filenames(totalFilesCount);
		{
			for (std::size_t i = 0; i < totalFilesCount; ++i)
			{
				auto &filename = filenames[i];
				auto &rawFilename = argv[i + 1];

				filename = static_cast<Nu::WString>(rawFilename);
			}
		}

		Nu::Map<Nu::WString, Nu::Lexing2::Lexer::Input> inputs;
		{
			for (auto &filename : filenames)
			{
				auto &input = inputs[filename];

				// std::wcout << L"loading file \"" << filename << L"\"..." << std::endl;

				std::ifstream file(filename);

				std::getline(file, input, '\0');

				// std::cout << "content: " << std::endl << input << std::endl;

				file.close();
			}
		}

		Nu::Lexing2::Lexer::Input totalInput;
		{
			for (auto &inputIt : inputs)
			{
				auto &input = inputIt.second;

				totalInput += input;
			}
		}

		auto translator = Nu::MakeReference<Nu::ProtoTranslator2::Translator>();
		auto assembly = translator->Translate(totalInput);

		auto outputEta = Stringify(assembly);

		std::ofstream fileEta(L"output.η");
		{
			fileEta.write(outputEta.data(), outputEta.size());
			fileEta.close();
		}

		auto parserEta = Eta::Parser();
		auto assemblyEta = parserEta.Parse(outputEta);

		auto translatorC = Translator_C::Translator();
		auto outputC = translatorC.Translate(assemblyEta);

		std::ofstream fileC(L"output.c");
		{
			fileC.write(outputC.data(), outputC.size());
			fileC.close();
		}
	}
	// catch (...)
	// {
	// 	std::cout << "Error" << std::endl;
	// 	
	// 	std::system("pause");
	// }
}


void main2()
{
	while (true)
	{
		try
		{
			std::cout << "input: ";

			Nu::String input;

			std::getline(std::cin, input, '\n');
			
			std::cout << std::endl;

			auto translator = Nu::MakeReference<Nu::ProtoTranslator2::Translator>();
			auto assembly = translator->Translate(input);

			std::cout << Stringify(assembly) << std::endl;
			
			std::cout << "Ok!" << std::endl;
		}
		catch (...)
		{
			std::cout << "Error!" << std::endl;
		}
	}
}

















