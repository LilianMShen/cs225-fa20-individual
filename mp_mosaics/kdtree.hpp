/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] == second[curDim]) {
      return (first < second);
    }

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double euclidCurr, euclidPotential;
    euclidCurr = 0;
    euclidPotential = 0;

    for (int i = 0; i < Dim; i++) {
      euclidCurr += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      euclidPotential += (target[i] - potential[i]) * (target[i] - potential[i]);
    }

    if (euclidPotential < euclidCurr) {
      return true;
    } else if (euclidPotential == euclidCurr) {
      return (potential < currentBest);
    }

    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    // making a NON CONST copy
    vector<Point<Dim>> points;
    for (int i = 0; i < (int) newPoints.size(); i++) {
      points.push_back(newPoints[i]);
    }

    if (newPoints.size() == 0) {
      root = NULL;
      return;
    }

    size = 0;

    buildTree(points, 0, 0, points.size() - 1, root);
}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim, int left, int right, KDTreeNode*& curRoot) {
  if (left <= right) {
    int middle = (left + right) / 2;
    quickSelect(points, left, right, dim, middle);
    curRoot = new KDTreeNode(points[middle]);
    size++;
    
    buildTree(points, (dim + 1) % Dim, left, middle - 1, curRoot -> left);
    buildTree(points, (dim + 1) % Dim, middle + 1, right, curRoot -> right);
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, int left, int right, int dim, int k) {
  if (left == right) {
    return points[left];
  }

  int pivotIndex = (left + right) / 2;
  pivotIndex = partition(points, left, right, pivotIndex, dim);

  if (k == pivotIndex) {
    return points[k];
  } else if (k < pivotIndex) {
    return quickSelect(points, left, pivotIndex - 1, dim, k);
  } else {
    return quickSelect(points, pivotIndex + 1, right, dim, k);
  }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim) {
  Point<Dim> pivotValue = points[pivotIndex];

  //swap the pivot and the right (move to the end)
  std::swap(points[pivotIndex], points[right]);

  int storeIndex = left;

  for (int i = left; i < right; i++) {
    if (smallerDimVal(points[i], pivotValue, dim)) {
      std::swap(points[storeIndex], points[i]);
      storeIndex++;
    }
  }
  std::swap(points[storeIndex], points[right]);

  return storeIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  copy(root, rhs->root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>&query, int dim, const KDTreeNode* curr) const{
  if (curr -> left == NULL && curr -> right == NULL) {
    return curr -> point;
  }

  bool recursedLeft = false;
  Point<Dim> nearest;
  if (smallerDimVal(query, curr -> point, dim) && (curr -> left)) {
    recursedLeft = true;
    nearest = findNearestNeighbor(query, (dim + 1) % Dim, curr -> left);
  } else if (curr -> right) {
    nearest = findNearestNeighbor(query, (dim + 1) % Dim, curr -> right);
  }

  if (shouldReplace(query, nearest, curr -> point)) {
    nearest = curr -> point;
  }

  double radius = 0;
  for (int i = 0; i < Dim; i++) {
    radius += (query[i] - nearest[i]) * (query[i] - nearest[i]);
  }

  double splitDist = (curr -> point[dim] - query[dim]) * (curr -> point[dim] - query[dim]);

  Point<Dim> tempNearest;
  if (radius >= splitDist) {
    if (recursedLeft && curr -> right) {
      tempNearest = findNearestNeighbor(query, (dim + 1) % Dim, curr -> right);
    } else if (!recursedLeft && curr -> left) {
      tempNearest = findNearestNeighbor(query, (dim + 1) % Dim, curr -> left);
    }

    if (shouldReplace(query, nearest, tempNearest)) {
      nearest = tempNearest;
    }
  }

  return nearest;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subRoot) {
  if (subRoot == NULL) {
    return;
  }

  clear(subRoot->left);
  clear(subRoot->right);
  delete subRoot;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode*& curr, KDTreeNode* other) {
  if (other == NULL)
    return;

  // Copy this node and its children
  curr = new KDTreeNode(other->point);
  copy(curr -> left, other->left);
  copy(curr -> right, other->right);
}