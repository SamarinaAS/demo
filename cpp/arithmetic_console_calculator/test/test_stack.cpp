#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack)
{
  ASSERT_NO_THROW(Stack<char>(20));
}

TEST(Stack, can_get_size)
{
  Stack<char> s(7);

  EXPECT_EQ(7, s.getStackSize());
}

TEST(Stack, can_push_element)
{
	Stack<char> s(7);
	ASSERT_NO_THROW(s.push('c'));
}

TEST(Stack, push_is_right)
{
	Stack<char> s(7);
	s.push('c');
	EXPECT_EQ('c', s.Peek());
}

TEST(Stack, pop_is_right)
{
	Stack<char> s(7);
	s.push('c');
	s.pop();
	EXPECT_EQ(-1, s.getTop());
}

TEST(Stack, GetTop_is_right)
{
	Stack<char> s(7);
	s.push('c');
	EXPECT_EQ(0, s.getTop());
}

TEST(Stack, Peek_is_right)
{
	Stack<char> s(7);
	s.push('c');
	EXPECT_EQ('c', s.Peek());
}

TEST(Stack, can_not_remove_elements_from_an_empty_stack)
{
	Stack<char> s(7);
	s.push('c');
	s.pop();
	ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, can_not_add_an_element_to_a_full_stack)
{
	Stack<char> s(2);
	s.push('c');
	s.push('v');
	ASSERT_ANY_THROW(s.push('b'));
}