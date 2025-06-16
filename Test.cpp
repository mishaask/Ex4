// mishaaskarov@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"

using namespace ariel;

// basic add/remove/size
TEST_CASE("Add and Size") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.addElement(1);
    c.addElement(2);
    CHECK(c.size() == 2);
}

TEST_CASE("Remove Elements") {
    MyContainer<int> c;
    c.addElement(1);
    c.addElement(2);
    c.addElement(2);
    c.removeElement(2);
    CHECK(c.size() == 1);
    CHECK_THROWS(c.removeElement(5));
}

// insertion‐order
TEST_CASE("Insertion Order") {
    MyContainer<int> c;
    c.addElement(7); c.addElement(15); c.addElement(6);
    c.addElement(1); c.addElement(2);
    std::vector<int> expected = {7,15,6,1,2};
    int i = 0;
    for (MyContainer<int>::OrderIterator it = c.begin_order();
         it != c.end_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// ascending
TEST_CASE("Ascending Order") {
    MyContainer<int> c;
    c.addElement(3); c.addElement(1); c.addElement(2);
    std::vector<int> expected = {1,2,3};
    int i = 0;
    for (MyContainer<int>::AscendingOrderIterator it = c.begin_ascending_order();
         it != c.end_ascending_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// descending
TEST_CASE("Descending Order") {
    MyContainer<int> c;
    c.addElement(3); c.addElement(1); c.addElement(2);
    std::vector<int> expected = {3,2,1};
    int i = 0;
    for (MyContainer<int>::DescendingOrderIterator it = c.begin_descending_order();
         it != c.end_descending_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// reverse
TEST_CASE("Reverse Order") {
    MyContainer<int> c;
    c.addElement(7); c.addElement(15); c.addElement(6);
    c.addElement(1); c.addElement(2);
    std::vector<int> expected = {2,1,6,15,7};
    int i = 0;
    for (MyContainer<int>::ReverseOrderIterator it = c.begin_reverse_order();
         it != c.end_reverse_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// side‐cross
TEST_CASE("SideCross Order") {
    MyContainer<int> c;
    c.addElement(1); c.addElement(2); c.addElement(6);
    c.addElement(7); c.addElement(15);
    std::vector<int> expected = {1,15,2,7,6};
    int i = 0;
    for (MyContainer<int>::SideCrossOrderIterator it = c.begin_side_cross_order();
         it != c.end_side_cross_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// middle‐out
TEST_CASE("Middle Out Order") {
    MyContainer<int> c;
    c.addElement(7); c.addElement(15); c.addElement(6);
    c.addElement(1); c.addElement(2);
    std::vector<int> expected = {6,15,1,7,2};
    int i = 0;
    for (MyContainer<int>::MiddleOutOrderIterator it = c.begin_middle_out_order();
         it != c.end_middle_out_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// duplicates removed
TEST_CASE("Remove All Duplicates") {
    MyContainer<int> c;
    c.addElement(1); c.addElement(1); c.addElement(1);
    CHECK(c.size() == 3);
    c.removeElement(1);
    CHECK(c.size() == 0);
}

// remove from empty
TEST_CASE("Remove from Empty") {
    MyContainer<int> c;
    CHECK_THROWS(c.removeElement(123));
}

// single‐element
TEST_CASE("One Element Iteration") {
    MyContainer<int> c;
    c.addElement(42);
    CHECK(*c.begin_order()            == 42);
    CHECK(*c.begin_ascending_order()  == 42);
    CHECK(*c.begin_descending_order() == 42);
    CHECK(*c.begin_side_cross_order() == 42);
    CHECK(*c.begin_middle_out_order() == 42);
    CHECK(*c.begin_reverse_order()    == 42);
}

// floating‐point
TEST_CASE("Floating Point") {
    MyContainer<double> c;
    c.addElement(1.1); c.addElement(3.3); c.addElement(2.2);
    std::vector<double> expected = {1.1,2.2,3.3};
    int i = 0;
    for (MyContainer<double>::AscendingOrderIterator it = c.begin_ascending_order();
         it != c.end_ascending_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// strings
TEST_CASE("String Elements") {
    MyContainer<std::string> c;
    c.addElement("zebra"); c.addElement("apple"); c.addElement("mango");
    std::vector<std::string> expected = {"apple","mango","zebra"};
    int i = 0;
    for (MyContainer<std::string>::AscendingOrderIterator it = c.begin_ascending_order();
         it != c.end_ascending_order();
         ++it)
    {
        CHECK(*it == expected[i++]);
    }
}

// operator<<
TEST_CASE("Output Check") {
    MyContainer<int> c;
    c.addElement(10); c.addElement(20);
    std::stringstream ss;
    ss << c;
    CHECK(ss.str() == "[10, 20]");
}
