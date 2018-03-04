#pragma once

#pragma region Include

#include "Header.hpp"

#pragma endregion


namespace Nu
{
	namespace Translator_C
	{
		class Entity:
			public Nu::Entity
		{
		public:
			inline Entity(const Reference<Entity>& this_);
			virtual ~Entity() override = default;
		};
		class Translator
		{
		public:
			inline String Translate(const Reference<Eta::Assembly>& assembly_);
		};
	}
}


#pragma region Nu

#pragma region Translator_C

#pragma region Entity

Nu::Translator_C::Entity::Entity(const Reference<Entity>& this_):
	Nu::Entity(this_)
{
}

#pragma endregion

#pragma region Translator

Nu::String Nu::Translator_C::Translator::Translate(const Reference<Eta::Assembly>& assembly_)
{
	String output;

	// Map<Reference<Eta::Schema>, String> schemasNames;

	auto getSchemaName = [&](const Reference<Eta::Schema>& schema_) -> String
	{
		auto it = assembly_->names.find(schema_);

		if (it != assembly_->names.end())
		{
			auto etaName = (*it).second;

			if (etaName == "\"root.int\"")
			{
				return "int";
			}
			else if (etaName == "\"none\"")
			{
				return "void";
			}
		}

		throw Exception();
	};
	auto getInstanceName = [&](const Reference<Eta::Instance>& instance_) -> String
	{
		auto it = assembly_->names.find(instance_);

		if (it != assembly_->names.end())
		{
			auto &name = (*it).second;

			return name;
		}
		else
		{
			throw Exception();
		}
	};

	Map<Reference<Eta::Algorithm>, String> algorithmsNames;

	auto getAlgorithm = [&](const Reference<Eta::AlgorithmDeclaration>& declaration_)
	{
		auto it = assembly_->algorithmDeclarationsLookup.find(declaration_);

		if (it != assembly_->algorithmDeclarationsLookup.end())
		{
			auto algorithm = (*it).second;

			return algorithm;
		}
		else
		{
			throw Exception();
		}
	};
	auto getAlgorithmName = [&](const Reference<Eta::Algorithm>& algorithm_) -> String
	{
		auto it = algorithmsNames.find(algorithm_);

		if (it == algorithmsNames.end())
		{
			auto name = [&]() -> String
			{
				auto it = assembly_->names.find(algorithm_);

				if (it != assembly_->names.end())
				{
					auto etaName = (*it).second;

					if (etaName == "'root.main.entry'")
					{
						return "main";
					}
					else if (etaName == "'root.add.int+int'")
					{
						return "int+int";
					}
					else if (etaName == "'root.sub.int-int'")
					{
						return "int-int";
					}
					else if (etaName == "'root.assign.int=int'")
					{
						return "int=int";
					}
				}

				return "f" + std::to_string(algorithmsNames.size());
			}();

			algorithmsNames.insert({algorithm_, name});

			return name;
		}
		else
		{
			auto &name = (*it).second;

			return name;
		}
	};

	Map<Reference<Eta::Algorithm>, String> functionsPrototypes;
	Map<Reference<Eta::Algorithm>, String> functionsBodies;

	for (auto &algorithm : assembly_->algorithms)
	{
		auto name = getAlgorithmName(algorithm);

		if (name != "int+int" && name != "int=int" && name != "int-int")
		{
			String arguments = "";

			for (auto &argument : algorithm->arguments)
			{
				if (!arguments.empty())
				{
					arguments += ", ";
				}

				arguments += getSchemaName(argument->schema) + " " + getInstanceName(argument);
			}

			String header = getSchemaName(algorithm->result) + " " + getAlgorithmName(algorithm) + "(" + arguments + ")";
			String prototype = header + ";";

			functionsPrototypes[algorithm] = prototype;

			String body = header + " {\n";

			for (auto &command : algorithm->commands)
			{
				if (auto create = UpCast<Eta::CreateCommand>(command))
				{
					body += "\t" + getSchemaName(create->instance->schema) + " " + getInstanceName(create->instance) + ";\n";
				}
				else if (auto call = UpCast<Eta::CallCommand>(command))
				{
					auto algorithm = getAlgorithm(call->algorithmDeclaration);
					auto name = getAlgorithmName(algorithm);

					if (name == "int+int")
					{
						body += "\tint " + getInstanceName(call->result) + " = " + getInstanceName(call->arguments[0]) + " + " + getInstanceName(call->arguments[1]) + ";\n";
					}
					else if (name == "int-int")
					{
						body += "\tint " + getInstanceName(call->result) + " = " + getInstanceName(call->arguments[0]) + " - " + getInstanceName(call->arguments[1]) + ";\n";
					}
					else if (name == "int=int")
					{
						body += "\t" + getInstanceName(call->arguments[0]) + " = " + getInstanceName(call->arguments[1]) + ";\n";
					}
					else
					{
						String arguments;
				
						for (auto &argument : call->arguments)
						{
							if (!arguments.empty())
							{
								arguments += ", ";
							}

							arguments += getInstanceName(argument);
						}

						body += "\t" + getSchemaName(call->result->schema) + " " + getInstanceName(call->result) + " = " + getAlgorithmName(algorithm) + "(" + arguments + ");\n";
					}
				}
				else if (auto ret = UpCast<Eta::ReturnCommand>(command))
				{
					body += "\treturn " + getInstanceName(ret->instance) + ";\n";
				}
				else
				{
					throw Exception();
				}
			}

			body += "}";

			functionsBodies[algorithm] = body;
		}
	}

	for (auto &i : functionsPrototypes)
	{
		auto &prototype = i.second;

		output += prototype + "\n";
	}
	for (auto &i : functionsBodies)
	{
		auto &body = i.second;

		output += body + "\n";
	}

	return Move(output);
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















