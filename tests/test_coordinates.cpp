//
// Created by Rahul Shah on 4/20/2026.
//
extern "C" {
#include "coordinates.h"
#include <stdio.h>
}
#include "gtest/gtest.h"

constexpr int TEST_X_COORD = 3;
constexpr int TEST_Y_COORD = 4;
constexpr int TEST_Z_COORD = 2;

constexpr int TEST_X2_COORD = 4;
constexpr int TEST_Y2_COORD = 5;
constexpr int TEST_Z2_COORD = 6;

// Test creation of Coordinates
TEST(CoordinateTestSuite, test_coordinate_creation_initializes_with_correct_xyz_values)
{
    const Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);

    EXPECT_EQ(returned_coords->x, TEST_X_COORD);
    EXPECT_EQ(returned_coords->y, TEST_Y_COORD);
    EXPECT_EQ(returned_coords->z, TEST_Z_COORD);
}
// Test destruction of Coordinates
TEST(CoordinateTestSuite, test_coordinate_deletion_frees_the_memory)
{
    Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);

    EXPECT_TRUE(returned_coords != nullptr);

    Coordinates__destroy(returned_coords);

    EXPECT_TRUE(returned_coords == nullptr);
}

TEST(CoordinateTestSuite, test_null_coordinate_deletion_does_nothing)
{
    Coordinates* returned_coords = nullptr;
    Coordinates__destroy(returned_coords);

    EXPECT_TRUE(returned_coords == nullptr);
}

// Test creation of CoordinateNode
TEST(CoordinateTestSuite, test_coordinate_node_creation_creates_non_null_pointer_and_initializes_coordinate_struct)
{
    Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(returned_coords);
    EXPECT_EQ(node->next, nullptr);
    EXPECT_NE(node->c,nullptr);
    EXPECT_EQ(node->c->x, TEST_X_COORD);
    EXPECT_EQ(node->c->y, TEST_Y_COORD);
    EXPECT_EQ(node->c->z, TEST_Z_COORD);

}

TEST(CoordinateTestSuite, test_coordinate_node_creation_with_null_coordinate_creates_non_null_pointer_but_null_members)
{
    CoordinateNode* node = CoordinateNode__create(nullptr);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->next, nullptr);
    EXPECT_EQ(node->c,nullptr);

}

// Test destruction of CoordinateNode
TEST(CoordinateTestSuite, test_coordinate_node_deletion_frees_the_memory)
{
    // Arrange.
    Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(returned_coords);
    EXPECT_EQ(node->next, nullptr);
    EXPECT_NE(node->c,nullptr);
    EXPECT_EQ(node->c->x, TEST_X_COORD);
    EXPECT_EQ(node->c->y, TEST_Y_COORD);
    EXPECT_EQ(node->c->z, TEST_Z_COORD);

    // Act.
    CoordinateNode__destroy(node);

    // Assert.
    EXPECT_EQ(node, nullptr);
}

// Test creation of CoordinateList
TEST(CoordinateTestSuite, test_coordinatelist_creation_initializes_values_correctly)
{
    Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(returned_coords);
    const CoordinateList* list = CoordinateList__create(node);
    EXPECT_EQ(list->head->next, nullptr);
    EXPECT_EQ(list->head, node);
    EXPECT_NE(list->head->c,nullptr);
    EXPECT_EQ(list->head->c->x, TEST_X_COORD);
    EXPECT_EQ(list->head->c->y, TEST_Y_COORD);
    EXPECT_EQ(list->head->c->z, TEST_Z_COORD);

}
// Test destruction of CoordinateList
TEST(CoordinateTestSuite, test_coordinate_list_deletion_frees_the_memory)
{
    // Arrange.
    Coordinates* returned_coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(returned_coords);
    CoordinateList* list = CoordinateList__create(node);
    EXPECT_EQ(list->head->next, nullptr);
    EXPECT_NE(list->head->c,nullptr);
    EXPECT_EQ(list->head->c->x, TEST_X_COORD);
    EXPECT_EQ(list->head->c->y, TEST_Y_COORD);
    EXPECT_EQ(list->head->c->z, TEST_Z_COORD);

    // Act.
    CoordinateList__destroy(list);

    // Assert.
    EXPECT_EQ(list, nullptr);
}

// Test adding node to empty list
TEST(CoordinateTestSuite, test_adding_node_to_empty_coordinate_list_initializes_the_head)
{
    CoordinateList* list = CoordinateList__create(nullptr);
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);

    CoordinateList__add_node(list, node);

    EXPECT_EQ(list->head, node);
    EXPECT_EQ(list->len, 1);
    EXPECT_EQ(list->head->next, nullptr);
    EXPECT_NE(list->head->c,nullptr);
    EXPECT_EQ(list->head->c->x, TEST_X_COORD);
    EXPECT_EQ(list->head->c->y, TEST_Y_COORD);
    EXPECT_EQ(list->head->c->z, TEST_Z_COORD);

}
// Test adding node to list with one element
TEST(CoordinateTestSuite, test_adding_node_to_nonempty_coordinate_list_initializes_the_next_pointer)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* new_coords = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* new_node = CoordinateNode__create(new_coords);

    CoordinateList__add_node(list, new_node);

    const CoordinateNode* next_node = list->head->next;

    EXPECT_EQ(list->head, node);
    EXPECT_EQ(list->len, 2);
    EXPECT_NE(list->head->next, nullptr);
    EXPECT_NE(list->head->c,nullptr);
    EXPECT_EQ(list->head->c->x, TEST_X_COORD);
    EXPECT_EQ(list->head->c->y, TEST_Y_COORD);
    EXPECT_EQ(list->head->c->z, TEST_Z_COORD);
    EXPECT_EQ(next_node->c->x, TEST_X2_COORD);
    EXPECT_EQ(next_node->c->y, TEST_Y2_COORD);
    EXPECT_EQ(next_node->c->z, TEST_Z2_COORD);

}
// test deleting node with list of more than one element
TEST(CoordinateTestSuite, test_deleting_node_with_list_of_more_than_one_element_only_deletes_the_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* coords2 = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* node2 = CoordinateNode__create(coords2);

    Coordinates* coords3 = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node3 = CoordinateNode__create(coords3);

    CoordinateList__add_node(list, node2);
    CoordinateList__add_node(list, node3);

    CoordinateList__delete_node(list, node2);

    EXPECT_EQ(list->head, node);
    EXPECT_EQ(list->len, 2);
    EXPECT_NE(list->head->next, nullptr);
    EXPECT_EQ(list->head->next, node3);
    EXPECT_EQ(node2, nullptr);
}

TEST(CoordinateTestSuite, test_deleting_node_via_coordinates_with_list_of_more_than_one_element_only_deletes_the_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* coords2 = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* node2 = CoordinateNode__create(coords2);

    Coordinates* coords3 = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node3 = CoordinateNode__create(coords3);

    CoordinateList__add_node(list, node2);
    CoordinateList__add_node(list, node3);

    CoordinateList__delete_node_with_coordinate_value(list, coords2);

    EXPECT_EQ(list->head, node);
    EXPECT_EQ(list->len, 2);
    EXPECT_NE(list->head->next, nullptr);
    EXPECT_EQ(list->head->next, node3);
    EXPECT_EQ(node2, nullptr);
}

// test deleting node with list of one element
TEST(CoordinateTestSuite, test_deleting_node_with_list_of_one_element_only_deletes_the_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);


    CoordinateList__delete_node(list, node);

    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list->head, nullptr);
    EXPECT_EQ(list->len, 0);
    EXPECT_NE(list->head->next, nullptr);
}



// test accessing node with index i < len
TEST(CoordinateTestSuite, test_indexing_into_list_gets_the_right_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* coords2 = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* node2 = CoordinateNode__create(coords2);

    Coordinates* coords3 = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node3 = CoordinateNode__create(coords3);

    CoordinateList__add_node(list, node2);
    CoordinateList__add_node(list, node3);

    CoordinateNode* popped_node = CoordinateList__retrieve_node_from_index(list, 2);

    EXPECT_EQ(popped_node->c->x, TEST_X2_COORD);
    EXPECT_EQ(popped_node->c->y, TEST_Y2_COORD);
    EXPECT_EQ(popped_node->c->z, TEST_Z2_COORD);
}
// test accessing node with index i >= len
TEST(CoordinateTestSuite, test_indexing_out_of_bounds_into_list_gets_null)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* coords2 = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* node2 = CoordinateNode__create(coords2);

    Coordinates* coords3 = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node3 = CoordinateNode__create(coords3);

    CoordinateList__add_node(list, node2);
    CoordinateList__add_node(list, node3);

    CoordinateNode* accessed_node = CoordinateList__retrieve_node_from_index(list, 4);

    EXPECT_EQ(accessed_node, nullptr);

}

// test popping off node in list of more than one element
TEST(CoordinateTestSuite, test_popping_node_off_list_with_more_than_one_element_returns_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    Coordinates* coords2 = Coordinates__create(TEST_X2_COORD, TEST_Y2_COORD, TEST_Z2_COORD);
    CoordinateNode* node2 = CoordinateNode__create(coords2);

    Coordinates* coords3 = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node3 = CoordinateNode__create(coords3);

    CoordinateList__add_node(list, node2);
    CoordinateList__add_node(list, node3);

    CoordinateNode* popped_node = CoordinateList__pop_front(list);

    EXPECT_EQ(popped_node, node);
    EXPECT_EQ(popped_node->c, node->c);
    EXPECT_EQ(popped_node->next, nullptr);
    EXPECT_NE(list->head, node);
    EXPECT_EQ(list->head, node2);
    EXPECT_EQ(list->head->next, node3);
}
// test popping off node in list of one element
TEST(CoordinateTestSuite, test_popping_node_off_list_with_one_element_returns_node)
{
    Coordinates* coords = Coordinates__create(TEST_X_COORD, TEST_Y_COORD, TEST_Z_COORD);
    CoordinateNode* node = CoordinateNode__create(coords);
    CoordinateList* list = CoordinateList__create(node);

    CoordinateNode* popped_node = CoordinateList__pop_front(list);

    EXPECT_EQ(popped_node, node);
    EXPECT_EQ(popped_node->c, node->c);
    EXPECT_NE(list->head, node);
    EXPECT_EQ(list->head, nullptr);
}