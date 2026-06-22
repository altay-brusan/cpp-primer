/*
 * Chapter 25 - Visualizing the Custom Container (to_dot, full version)
 *
 * Serializes the full directed_graph into Graphviz DOT format. Unlike the basic version, this one
 * takes advantage of the container's new iterator support: it walks the nodes with a range-based
 * for loop and walks each node's neighbors through the range returned by nodes_adjacent_to(),
 * illustrating how a properly iterator-enabled custom container reads just like a built-in one.
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
		for (auto&& node : graph)
		{
			auto adjacent_nodes{ graph.nodes_adjacent_to(node) };
			if (adjacent_nodes->begin() == adjacent_nodes->end())
			{
				std::println(output, "{}", node);
			}
			else
			{
				for (const auto& adjacent_node : *adjacent_nodes)
				{
					std::println(output, "{} -> {}", node, adjacent_node);
				}
			}
		}
		std::println(output, "}}");

		return std::move(output).str();
	}

}
