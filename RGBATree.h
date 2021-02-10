#pragma once
#include <vector>
#include <map>
#include "PNG.h"

using namespace std;
using namespace PNGUtil;
namespace TilerUtils {
	class RGBATree
	{
	public: 
		/// <summary>
		/// Constructs an empty object. Do not use.
		/// </summary>
		RGBATree() {};

		/// <summary>
		/// Constructs a k-d tree with the given photos to use as the nodes.
		/// </summary>
		/// <param name="photos">Map of PNGs corresponding to an average colour.</param>
		RGBATree(const map<unsigned, PNG>& photos);

		~RGBATree() {  };

		/// <summary>
		/// Returns the pixel that 'query' is the closest to an element in the k-d tree.
		/// </summary>
		/// <param name="query">Pixel to be approximated.</param>
		/// <returns>A pixel that corresponds to an tile in the photo map.</returns>
		unsigned FindNearestNeighbor(const unsigned& query) const;

		/// <summary>
		/// Clears the tree and makes a new one based on the given map
		/// </summary>
		/// <param name="photos">Map of PNGs corresponding to an average colour.</param>
		void Rebuild(const map<unsigned, PNG>& photos);

	private:
		/// <summary>
		/// Arranges the tree by median in the given range in dimension d.
		/// </summary>
		/// <param name="start">Index of the beginning of the range.</param>
		/// <param name="end">Index of the end of the range.</param>
		/// <param name="d">The dimension to account for.</param>
		void constructTree(unsigned start, unsigned end, unsigned char d);

		unsigned traverseNearestNeighbor(const unsigned& query, int start, int end, unsigned char dimension) const;

		unsigned closestPoint(const unsigned& query, const unsigned& p1, const unsigned& p2) const;

		bool smallerByDim(const unsigned& first, const unsigned& second, unsigned char curDim) const;

		void quickSelect(unsigned start, unsigned end, unsigned k, unsigned char d);

		unsigned partition(unsigned lo, unsigned hi, unsigned char d);

		unsigned distToSplit(const unsigned& query, const unsigned& curr, unsigned char dimension) const;

		unsigned distToPoint(const unsigned& query, const unsigned& curr) const;
		
		/// <summary>
		/// Tree data. This is the actual k-d tree.
		/// </summary>
		vector<unsigned> tree;
	};
}

