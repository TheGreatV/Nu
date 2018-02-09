#pragma once

#pragma region Include

#include "Header.hpp"

// #include <../Lexer2/Lexer.hpp>

#pragma endregion


namespace Nu
{
	namespace Eta
	{
		class Entity:
			public Nu::Entity
		{
		public:
			inline Entity(const Reference<Entity>& this_);
			virtual ~Entity() override = default;
		};
		class Schema
		{
		};
		class Instance
		{
		public:
			const Reference<Schema> schema;
		public:
			inline Instance(const Reference<Schema>& schema_):
				schema(schema_)
			{
			}
		};
		class Command
		{
		public:
			inline virtual ~Command() = default;
		};
		class CreateCommand: public Command
		{
		public:
			const Reference<Instance> instance;
		public:
			inline CreateCommand(const Reference<Instance>& instance_):
				instance(instance_)
			{
			}
		};
		class AlgorithmDeclaration
		{
		public:
			const Reference<Schema> result;
			const Vector<Reference<Schema>> arguments;
		public:
			inline AlgorithmDeclaration(const Reference<Schema>& result_, const Vector<Reference<Schema>>& arguments_):
				result(result_),
				arguments(arguments_)
			{
			}
		};
		class Algorithm
		{
		public:
			const Reference<Schema> result;
			const Vector<Reference<Instance>> arguments;
			const Vector<Reference<Command>> commands;
		public:
			inline Algorithm(const Reference<AlgorithmDeclaration>& algorithmDeclaration_, const Vector<Reference<Instance>>& arguments_, const Vector<Reference<Command>>& commands_):
				result(algorithmDeclaration_->result),
				arguments(arguments_),
				commands(commands_)
			{
			}
		};
		class CallCommand: public Command
		{
		public:
			const Reference<AlgorithmDeclaration> algorithmDeclaration;
			const Reference<Instance> result;
			const Vector<Reference<Instance>> arguments;
		public:
			inline CallCommand(const Reference<AlgorithmDeclaration>& algorithmDeclaration_, const Reference<Instance>& result_, const Vector<Reference<Instance>>& arguments_):
				algorithmDeclaration(algorithmDeclaration_),
				result(result_),
				arguments(arguments_)
			{
			}
		};
		class Parser
		{
		public:
			using It = String::iterator;
		public:
			static inline It SkipDoubleQuotes(const String& source, It i);
			static inline It SkipSingleQuotes(const String& source, It i);
			static inline It SkipComment(const String& source, It i);
			static inline It SkipWhitespaces(const String& source, It i);
			static inline It SkipNumbers(const String& source, It i);
		public:
			static inline String Clean(const String& input_);
		protected:
		public:
			inline void Parse(const String& input_);
		};
	}
}


#pragma region Nu

#pragma region Eta

#pragma region Entity

Nu::Eta::Entity::Entity(const Reference<Entity>& this_):
	Nu::Entity(this_)
{
}

#pragma endregion

#pragma region Eta

Nu::Eta::Parser::It Nu::Eta::Parser::SkipDoubleQuotes(const String& source, It i)
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
Nu::Eta::Parser::It Nu::Eta::Parser::SkipSingleQuotes(const String& source, It i)
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
Nu::Eta::Parser::It Nu::Eta::Parser::SkipComment(const String& source, It i)
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
			throw Exception();
		}
	}
}
Nu::Eta::Parser::It Nu::Eta::Parser::SkipWhitespaces(const String& source, It i)
{
	while (i != source.end() && (*i == ' ' || *i == '\t' || *i == '\n' || *i == '\r'))
	{
		++i;
	}

	return i;
}
Nu::Eta::Parser::It Nu::Eta::Parser::SkipNumbers(const String& source, It i)
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

Nu::String Nu::Eta::Parser::Clean(const String& input_)
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

			goto start;
		}
		else
		{
			++i;
		}
	}

	return output;
}

void Nu::Eta::Parser::Parse(const String& input_)
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

	Map<String, Reference<Schema>> schemas;

	auto matchSchema = [&](const String& source, It& i) -> Reference<Schema>
	{
		auto v = *i;

		if (v == '"')
		{
			auto j = SkipDoubleQuotes(source, i);
			auto name = String(i, j);
			auto it = schemas.find(name);
			
			if (it != schemas.end())
			{
				auto schema = (*it).second;

				i = j;

				return schema;
			}
			else
			{
				throw Exception();
			}
		}

		return nullptr;
	};

	Map<String, Reference<AlgorithmDeclaration>> algorithmsDeclarations;
	Map<Reference<AlgorithmDeclaration>, Reference<Algorithm>> algorithms;

	auto matchAlgorithmDeclaration = [&](const String& source, It& i) -> Reference<AlgorithmDeclaration>
	{
		auto v = *i;

		if (v == '\'')
		{
			auto j = SkipSingleQuotes(source, i);
			auto name = String(i, j);
			auto it = algorithmsDeclarations.find(name);

			if (it != algorithmsDeclarations.end())
			{
				auto algorithmDeclaration = (*it).second;

				i = j;

				return algorithmDeclaration;
			}
			else
			{
				throw Exception();
			}
		}

		return nullptr;
	};
	/*auto matchAlgorithm = [&](const String& source, It& i) -> Reference<Algorithm>
	{
		auto v = *i;

		if (v == '\'')
		{
			auto j = SkipSingleQuotes(source, i);
			auto name = String(i, j);
			auto it = algorithmsDeclarations.find(name);

			if (it != algorithmsDeclarations.end())
			{
				auto algorithmDeclaration = (*it).second;
				auto jt = algorithms.find(algorithmDeclaration);

				if (jt != algorithms.end())
				{
					auto algorithm = (*jt).second;

					i = j;

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

		return nullptr;
	};*/

	Map<String, Reference<Instance>> instances;

	auto parseInstanceName = [&](const String& source, It& i) -> Reference<String>
	{
		if (i != source.end() && *i == '$')
		{
			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(i, j);

			i = j;
			
			return MakeReference<String>(name);
		}
		else
		{
			return nullptr;
		}
	};
	auto parseInstance = [&](const String& source, It& i, const Reference<Schema>& schema_) -> Reference<Instance>
	{
		if (i != source.end() && *i == '$')
		{
			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(i, j);
			auto instance = MakeReference<Instance>(schema_);

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
			++i;

			auto j = SkipNumbers(source, i);
			auto name = String(i, j);
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

					auto schemaName = String(j, i);

					i = SkipWhitespaces(source, i);
					
					if (i != source.end() && *i == ';')
					{
						++i;

						auto schema = MakeReference<Schema>();

						if (schemas.find(schemaName) != schemas.end())
						{
							throw Exception();
						}

						schemas[schemaName] = schema;
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
			else if (auto schema = matchSchema(source, i))
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

				if (auto result = matchSchema(source, i))
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

							Vector<Reference<Schema>> arguments;
							
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

								if (auto schema = matchSchema(source, i))
								{
									arguments.push_back(schema);
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

									auto algorithm = MakeReference<AlgorithmDeclaration>(result, arguments);

									if (algorithmsDeclarations.find(algorithmName) != algorithmsDeclarations.end())
									{
										throw Exception();
									}
									
									algorithmsDeclarations[algorithmName] = algorithm;
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
			else if (auto algorithmDeclaration = matchAlgorithmDeclaration(source, i))
			{
				i = SkipWhitespaces(source, i);

				if (i != source.end() && *i == ':')
				{
					++i;

					i = SkipWhitespaces(source, i);

					if (i != source.end() && *i == '(')
					{
						++i;

						auto &schemas = algorithmDeclaration->arguments;
						
						Vector<Reference<Instance>> arguments;

						for (auto &schema : schemas)
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

							if (auto instance = parseInstance(source, i, schema))
							{
								arguments.push_back(instance);
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

								auto parseCreateCommand = [&](const String& source, It& i) -> Reference<CreateCommand>
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

												if (auto schema = matchSchema(source, i))
												{
													i = SkipWhitespaces(source, i);

													if (i != source.end() && *i == ';')
													{
														++i;

														auto instance = MakeReference<Instance>(schema);
														auto create = MakeReference<CreateCommand>(instance);

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
								auto parseCallCommand = [&](const String& source, It& i) -> Reference<CallCommand>
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
												
												if (auto algorithmDeclaration = matchAlgorithmDeclaration(source, i))
												{
													if (i != source.end() && *i == '(')
													{
														++i;

														i = SkipWhitespaces(source, i);

														// parce arguments
														Vector<Reference<Instance>> arguments;

														for (auto &argument : algorithmDeclaration->arguments)
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
																arguments.push_back(instance);
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

																auto result = MakeReference<Instance>(algorithmDeclaration->result);
																auto call = MakeReference<CallCommand>(algorithmDeclaration, result, arguments);

																return call;
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
												
												/*if (auto schema = matchSchema(source, i))
												{
													i = SkipWhitespaces(source, i);

													if (i != source.end() && *i == ';')
													{
														++i;

														auto instance = MakeReference<Instance>(schema);
														auto create = MakeReference<CreateCommand>(instance);

														return create;
													}
													else
													{
														throw Exception();
													}
												}
*/
											}
										}
									}

									i = o;
									return nullptr;
								};

								// parse commands
								Vector<Reference<Command>> commands;

								while (true)
								{
									i = SkipWhitespaces(source, i);

									if (auto create = parseCreateCommand(source, i))
									{
										commands.push_back(create);
									}
									else if (auto call = parseCallCommand(source, i))
									{
										commands.push_back(call);
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

										auto algorithm = MakeReference<Algorithm>(algorithmDeclaration, arguments, commands);

										if (algorithms.find(algorithmDeclaration) != algorithms.end())
										{
											throw Exception();
										}

										algorithms[algorithmDeclaration] = algorithm;
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
}

#pragma endregion

#pragma endregion

#pragma endregion


#pragma region
#pragma endregion




















