/*
 * Chapter 25 - Visualizing the Custom Container (to_dot, basic version)
 *
 * A free function template that serializes the basic directed_graph into Graphviz DOT format for
 * easy visualization. Because the basic graph has no iterators yet, it walks the nodes by index
 * via operator[] and size(), querying each node's neighbors with get_adjacent_nodes_values().
 * It demonstrates that useful free-function utilities can be layered on top of a custom container's
 * public interface.
 */

#pragma once

#include "directed_graph.h"
#include <string>
#include <string_view>
#include <sstream>
#include <print>
#include <ostream> // for the std::println(std::ostream&, ...) overloads on newest MSVC
#include <utility>

namespace ProCpp
{

	// Returns a given graph in DOT format.
	template <typename T>
	std::string to_dot(const directed_graph<T>& graph, std::string_view graph_name)
	{
		std::ostringstream output;

		std::println(output, "digraph {} {{", graph_name);
		for (std::size_t index{ 0 }; index < graph.size(); ++index)
		{
			const auto& node_value{ graph[index] };
			const auto adjacent_values{ graph.get_adjacent_nodes_values(node_value) };
			if (adjacent_values.empty())
			{
				std::println(output, "{}", node_value);
			}
			else
			{
				for (auto&& neighbor : adjacent_values)
				{
					std::println(output, "{} -> {}", node_value, neighbor);
				}
			}
		}
		std::println(output, "}}");

		return std::move(output).str();
	}

}
