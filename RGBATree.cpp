/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include "RGBATree.h"

using namespace std;
namespace TilerUtils {
    RGBATree::RGBATree(const map<unsigned, PNG>& photos)
    {
        tree.clear();
        tree.reserve(photos.size());
        for (pair<unsigned, PNG> pair : photos) {
            tree.push_back(pair.first);
        }

        // Then arrange the array so that it follows the tree structure
        constructTree(0, tree.size() - 1, 0);
    }

    void RGBATree::constructTree(int start, int end, unsigned char d) {
        // Sort tree by median, this is essentially quicksort.
        if (start < end) {
            d = d % 3;  // % 4 = also consider by alpha value
            int p = (start + end) / 2;
            quickSelect(start, end, p, d);
            d++;
            constructTree(start, p - 1, d);
            constructTree(p + 1, end, d);
        }
    }


    unsigned RGBATree::FindNearestNeighbor(const unsigned& query) const
    {
        /* your code here! */
        return traverseNearestNeighbor(query, 0, tree.size() - 1, 0);
    }

    unsigned RGBATree::traverseNearestNeighbor(const unsigned& query, int start, int end, unsigned char dimension) const {
        if (start < end) {
            dimension = dimension % 3;

            // Tree structure: root is the middle of the segment
            int p = (start + end) / 2;

            unsigned curr = tree[p];   // The root

            unsigned inMin;    // Best node in the same side as the query relative to the root 
            unsigned best;     // Best node to be returned

            // Signed distance between the query and the root.
            // distSplit > 0 
            unsigned distSplit = distToSplit(query, curr, dimension);

            // Get the nodes in the same side as the query relative to the root in the 'dimension' dimension
            inMin = traverseNearestNeighbor(query, start, p, dimension + 1);

            // Chooses what is closer, the best in the same-side node or the root?
            best = closestPoint(query, inMin, curr);

            // Gets the distance between the query and the best
            unsigned dist = distToPoint(query, best);

            // If the absolute distance between the query and the root is smaller than the best distance,
            if (distSplit < dist) {
                unsigned outMin;
                // Probe for the nodes that are at the other side of the root
                outMin = traverseNearestNeighbor(query, p + 1, end, dimension + 1);

                // Choose what is closer, the best node on the other side or the root/same-side
                best = closestPoint(query, outMin, best);
            }

            // Return the best node
            return best;
        }
        else return tree[end];
    }

    unsigned RGBATree::closestPoint(const unsigned& query, const unsigned& p1, const unsigned& p2) const {
        if (distToPoint(query, p1) > distToPoint(query, p2)) 
            return p2;
        return p1;
    }

    bool RGBATree::smallerByDim(const unsigned& first,
        const unsigned& second, unsigned char curDim) const
    {
        unsigned char a = IntToChar(first, curDim);
        unsigned char b = IntToChar(second, curDim);
        if (a != b) return a < b;
        return first < second;
    }

    /**
     * This function splits the trees[start..end] subarray at position start k
     */
    void RGBATree::quickSelect(int start, int end, int k, unsigned char d)
    {
        if (start < end) {
            int pivot = partition(start, end, d);
            if (k < pivot)
                quickSelect(start, pivot - 1, k, d);
            else if (k > pivot)
                quickSelect(pivot + 1, end, k, d);
        }
    }


    /**
     * This method does a partition around pivot and will be used
     * in quick select. It uses tree[lo] as the default pivot.
     * It returns the index of the pivot in the updated vector.
     * You will likely need to modify and complete this code.
     */
    unsigned RGBATree::partition(int lo, int hi, unsigned char d)
    {
        int p = lo;
        int pValue = IntToChar(tree[p], d);
        for (int i = lo + 1; i <= hi; i++) {
            if (IntToChar(tree[i], d) < pValue) {
                p++;
                std::swap(tree[p], tree[i]);
            }
        }
        std::swap(tree[lo], tree[p]);
        return p;
    }

    /**
     * Helper function to help determine if the nearest neighbor could
     * be on the other side of the KD tree.
     * 
     * To skip the needlessly complicated square root to get the proper distance,
     * we just use the squares because it's good enough.
     */
    unsigned RGBATree::distToSplit(const unsigned& query, const unsigned& curr, unsigned char dimension) const
    {
        // distance^2 = x^2 + y^2 + z^2 + a^2
        int d = IntToChar(curr, dimension) - IntToChar(query, dimension);
        return d * d;
    }

    unsigned RGBATree::distToPoint(const unsigned& query, const unsigned& curr) const
    {
        unsigned r = distToSplit(query, curr, 0);
        unsigned g = distToSplit(query, curr, 1);
        unsigned b = distToSplit(query, curr, 2);
        //unsigned a = distToSplit(query, curr, 3);
        return r + g + b;// + a;
    }
}