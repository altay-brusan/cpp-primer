/*
 * Chapter 25 - Custom Container Building Block: the Node (basic directed_graph)
 *
 * Writing your own Standard Library-style container means breaking it into small pieces. This
 * header defines the per-node helper used by the basic directed_graph: each graph_node stores one
 * value plus an adjacency list. Crucially the adjacency list holds indices (std::set<std::size_t>)
 * into the graph's node vector rather than pointers, so the relationships survive the vector
 * reallocating. remove_node_index() shows the bookkeeping cost of that choice: when a node is
 * deleted every higher index must be decremented to stay valid.
 *
 * Key notes:
 *   - graph_node lives in a details namespace; it is an implementation detail, not public API.
 *   - std::set elements are immutable, so remove_node_index() rebuilds the set after shifting.
 */

#pragma once

#include <utility>
#include <cstddef>
#include <set>
#include <vector>
#include <algorithm>

namespace ProCpp
{

	// Forward declaration.
	template<typename T>
	class directed_graph;

	namespace details
	{

		template<typename T>
		class graph_node
		{
		public:
			// Constructs a graph_node for the given value.
			explicit graph_node(directed_graph<T>* graph, T t)
				: m_graph{ graph }
				, m_data(std::move(t))
			{
			}

			// Returns a reference to the stored value.
			[[nodiscard]] const T& value() const noexcept { return m_data; }

			// A type alias for the container type used to store the adjacency list.
			using adjacency_list_type = std::set<std::size_t>;

			// Returns a reference to the adjacency list.
			[[nodiscard]] auto& get_adjacent_nodes_indices() { return m_adjacentNodeIndices; }
			[[nodiscard]] const auto& get_adjacent_nodes_indices() const { return m_adjacentNodeIndices; }

			// Removes a given node index from the adjacency list and updates
			// the remaining indices to account for the shift in indices.
			void remove_node_index(std::size_t node_index);

		private:
			// A pointer to the graph this node is in.
			directed_graph<T>* m_graph;

			T m_data;
			adjacency_list_type m_adjacentNodeIndices;
		};

		template<typename T>
		void graph_node<T>::remove_node_index(std::size_t node_index)
		{
			// First, remove references to the to-be-deleted node.
			m_adjacentNodeIndices.erase(node_index);

			// Second, modify all adjacency indices to account for the removal of a node.
			// std::set doesn't let us modify its elements in place,
			// so we rebuild the set from scratch.
			std::vector<std::size_t> indices(std::begin(m_adjacentNodeIndices), std::end(m_adjacentNodeIndices));
			std::for_each(std::begin(indices), std::end(indices),
				[node_index](std::size_t& index) {
					if (index > node_index) {
						--index;
					}
				});
			m_adjacentNodeIndices.clear();
			m_adjacentNodeIndices.insert(std::begin(indices), std::end(indices));
		}
	}
}
