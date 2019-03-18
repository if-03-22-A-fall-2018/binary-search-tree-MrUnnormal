/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: 2AHIF
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#define LENGTH 50
#include <stdlib.h>
#include "general.h"
#include "bst.h"

struct Node {
  int element;
  Bst left;
  Bst right;
};

Bst new_bst()
{
  Bst bst = (Bst) malloc(sizeof(Bst));
  bst = 0;
  return bst;
}

void delete_bst(Bst bst)
{
  if(bst != 0)
  {
      delete_bst(bst->left);
      delete_bst(bst->right);
      sfree(bst);
  }
}

/**
*** @return The depth of the BST
*/
int get_depth(Bst bst)
{
   if (bst == 0)
   {
     return 0;
   }
   else if(bst->right == 0 && bst->left == 0)
   {
     return 1;
   }
   else if(get_depth(right_subtree(bst)) > get_depth(left_subtree(bst)))
   {
     return 1 + get_depth(right_subtree(bst));
   }
   return 1 + get_depth(left_subtree(bst));
}

/**
*** Adds a value to the BST
*/
void add(Bst* bst, int value)
{
  Bst &bst_temp = *bst;
  if(bst_temp == 0)
  {
    bst_temp = (Bst)malloc(sizeof(struct Node));
    bst_temp -> element = value;
    bst_temp -> left = 0;
    bst_temp -> right = 0;
   }
   else if(value <= bst_temp -> element)
   { add(&bst_temp -> left, value); }
   else
   { add(&bst_temp -> right, value); }
}

/**
*** @return The value of the root element of the BST
*/
int root_value(Bst bst)
{
  if(bst == 0)
  { return 0; }
  else
  { return bst -> element; }
}

/**
*** @return The left subtree of the BST
*/
Bst left_subtree(Bst root)
{
  if(root == 0)
  { return 0; }
  else
  { return root -> left; }
}

/**
*** @return The right subtree of the BST
*/
Bst right_subtree(Bst root)
{
  if(root == 0)
  { return 0; }
  else
  { return root -> right; }
}

/**
*** Traverses the BST depth first by first returning the root, then traversing the left
*** subtree, then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_pre_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  { return 0; }
  int count = 0;
  elements[start] = bst -> element;
  count += traverse_pre_order(bst -> left, elements, start + 1);
  count += traverse_pre_order(bst -> right, elements, start + count + 1);
  return count + 1;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then adding the root,
*** then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_in_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  { return 0; }
  int count = 0;
  count += traverse_in_order(bst -> left, elements, start);
  elements[start + count] = bst -> element;
  count += traverse_in_order(bst -> right, elements, start + count + 1);
  return count + 1;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then traversing the right
*** subtree and finally adding the root.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_post_order(Bst bst, int *elements, int start)
{
  if(bst == 0)
  { return 0; }
  int count = 0;
  count += traverse_post_order(bst -> left, elements, start);
  count += traverse_post_order(bst -> right, elements, start + count);
  elements[start + count] = bst -> element;
  return count + 1;
}

/**
*** Checks whether two trees are equal
*** @param bst1 First bst
*** @param bst2 Second bst
*** @return true if bst1 and bst2 are equal, false otherwise
*/
bool are_equal(Bst bst1, Bst bst2)
{
  if(bst1 == bst2)
  { return true; }
  if(bst1 != 0 && bst2 != 0)
  {
    int array1[LENGTH];
    int length = traverse_pre_order(bst1, array1, 0);
    int array2[LENGTH];
    int length2 = traverse_pre_order(bst2, array2, 0);
    if(length == length2)
    {
      bool x = true;
      for (int i = 0; i < length; i++)
      {
        if(array1[i]!= array2[i])
        {x = false;}
      }
      return x;
    }
  }
  return false;
}

/**
*** Calculates the longest branch in the tree. If two branches are equally long
*** the left branch is taken.
*** @param bst Bst which longest branch should be found
*** @return A tree where each node has only one child equal to the longest
*** branch of bst
*/
void most_left_longest_branch(Bst bst, Bst* branch)
{
  if(bst == 0)
  { return; }
  add(branch, bst->element);
  if(get_depth(bst -> left) >= get_depth(bst -> right))
  { most_left_longest_branch(bst -> left, branch); }
  else
  { most_left_longest_branch(bst -> right, branch); }
}

/**
*** Gets the number of non-empty subtrees of a tree
*** @param bst The tree which number of subtrees to get
*** @return The number of non-empty subtrees
*/
int get_number_of_subtrees(Bst bst)
{
  if(bst == 0)
  { return -1;}
  return (get_number_of_subtrees(bst -> left) + 1) + (get_number_of_subtrees(bst -> right) + 1);
}
